#include "PlayState.h"

#include "../Config.h"
#include "../Misc/Util.h"
#include "MainMenuState.h"

#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>
#include <algorithm>

PlayState::PlayState(AppDataRef& appData)
	: m_appData(appData), m_gen((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count())
{
	m_gameOver = false;
	m_timeSinceGameOver = 0;
	m_timeSinceLastAstolfo = 0;
	m_timeSinceLastBullet = 0;
}

void PlayState::Init()
{
	m_appData->resources.LoadTexture("astolfo", Config::AstolfoImage);
	m_appData->resources.LoadTexture("hah_gay", Config::HahGayAstolfoImage);
	m_appData->resources.LoadTexture("heart", Config::HeartImage);
	m_appData->resources.LoadTexture("empty_heart", Config::EmptyHeartImage);

	m_player.setSize(sf::Vector2f(16.f, 24.f));
	m_player.setFillColor(sf::Color::Red);
	
	sf::FloatRect bounds = m_player.getLocalBounds();
	m_player.setOrigin(
		bounds.width / 2.f,
		bounds.height
	);

	m_player.setPosition(
		Config::ScreenWidth / 2.f,
		Config::ScreenHeight
	);

	m_heartSprite.setTexture(m_appData->resources.GetTexture("heart"));
	m_heartSprite.setScale(HEART_SIZE / m_heartSprite.getLocalBounds().width, HEART_SIZE / m_heartSprite.getLocalBounds().height);

	m_emptyHeartSprite.setTexture(m_appData->resources.GetTexture("empty_heart"));
	m_emptyHeartSprite.setScale(HEART_SIZE / m_emptyHeartSprite.getLocalBounds().width, HEART_SIZE / m_emptyHeartSprite.getLocalBounds().height);

	m_spGay.setTexture(m_appData->resources.GetTexture("hah_gay"));

	bounds = m_spGay.getGlobalBounds();
	m_spGay.setPosition(
		Config::ScreenWidth / 2.f - bounds.width / 2.f,
		Config::ScreenHeight / 2.f - bounds.height / 2.f
	);

	m_gmOver.setFont(m_appData->resources.GetFont("chewy"));
	m_gmOver.setString("GAME OVER");
	m_gmOver.setCharacterSize(72);
	m_gmOver.setOutlineThickness(2);
	m_gmOver.setOutlineColor(sf::Color::Black);

	bounds = m_gmOver.getGlobalBounds();
	m_gmOver.setPosition(
		Config::ScreenWidth / 2.f - bounds.width / 2.f,
		Config::ScreenHeight / 4.f - bounds.height / 2.f
	);

	m_pressToContinue.setFont(m_appData->resources.GetFont("chewy"));
	m_pressToContinue.setString("Press any key to continue...");
	m_pressToContinue.setCharacterSize(32);
	m_pressToContinue.setOutlineThickness(2);
	m_pressToContinue.setOutlineColor(sf::Color::Black);

	bounds = m_pressToContinue.getGlobalBounds();
	m_pressToContinue.setPosition(
		Config::ScreenWidth / 2.f - bounds.width / 2.f,
		Config::ScreenHeight - bounds.height - 10.f
	);

	m_blackPane = sf::RectangleShape(sf::Vector2f(Config::ScreenWidth, Config::ScreenHeight));
	m_blackPane.setFillColor(sf::Color(0, 0, 0, 192));
}

void PlayState::CleanUp()
{
	m_appData->resources.UnloadTexture("astolfo");
	m_appData->resources.UnloadTexture("hah_gay");
	m_appData->resources.UnloadTexture("heart");
	m_appData->resources.UnloadTexture("empty_heart");
}

void PlayState::HandleEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (m_gameOver && m_timeSinceGameOver >= TIME_UNTIL_CONTINUE)
		{
			m_appData->stateManager.AddState(StateRef(new MainMenuState(m_appData)));
		}

		break;
	}
}

void PlayState::HandleInput()
{
	if (m_gameOver)
		return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (m_timeSinceLastBullet >= BULLET_SPAWN_RATE)
		{
			SpawnBullet();
		}
	}
}

void PlayState::SpawnBullet()
{
	m_bulletSpawner.Spawn(
		m_player.getPosition(),
		m_player.getRotation() - (2 * m_dist(m_gen) * BULLET_RECOIL - BULLET_RECOIL),
		BULLET_SPEED
	);

	m_timeSinceLastBullet = 0.f;
}

void PlayState::SpawnAstolfo()
{
	if (m_timeSinceLastAstolfo < ASTOLFO_SPAWN_RATE)
	{
		return;
	}

	m_astolfoSpawner.Spawn(
		sf::Vector2f(m_dist(m_gen) * (Config::ScreenWidth - 100.f) + 50.f, Config::ScreenHeight / -5.f),
		m_dist(m_gen) * ASTOLFO_FALL_SPEED_RATE + ASTOLFO_BASE_FALL_SPEED,
		2 * m_dist(m_gen) * ASTOLFO_ANGLULAR_VELOCITY - ASTOLFO_ANGLULAR_VELOCITY,
		m_appData->resources
	);

	m_timeSinceLastAstolfo = 0;
}

void PlayState::CheckAstolfos()
{
	auto& astolfos = m_astolfoSpawner.GetAstolfos();
	auto& bullets = m_bulletSpawner.GetBullets();

	for (auto& as : astolfos)
	{
		if (as.IsOutOfScreen(Config::ScreenWidth, Config::ScreenHeight))
		{
			if (m_playerHealth > 0)
			{
				m_playerHealth--;
			}

			astolfos.erase(std::remove(astolfos.begin(), astolfos.end(), as));
			continue;
		}

		for (auto& b : bullets)
		{
			if (as.Intercepts(b.getGlobalBounds()))
			{
				astolfos.erase(std::remove(astolfos.begin(), astolfos.end(), as));
				bullets.erase(std::remove(bullets.begin(), bullets.end(), b));
			}
		}
	}
}

void PlayState::Update(float dt)
{
	if (m_gameOver)
	{
		if (m_timeSinceGameOver < TIME_UNTIL_CONTINUE)
		{
			m_timeSinceGameOver += dt;
		}

		return;
	}

	if (m_timeSinceLastBullet < BULLET_SPAWN_RATE)
	{
		m_timeSinceLastBullet += dt;
	}

	if (m_timeSinceLastAstolfo < ASTOLFO_SPAWN_RATE)
	{
		m_timeSinceLastAstolfo += dt;
	}

	SpawnAstolfo();
	CheckAstolfos();

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_appData->window);
	const sf::Vector2f& pPos = m_player.getPosition();

	sf::Vector2f dPos = sf::Vector2f(mousePos.x - pPos.x, pPos.y - mousePos.y);

	float newRotation = std::asin(dPos.x / Util::GetVectorMagnitude(dPos)) * 180.f / PI;
	if (newRotation > PLAYER_MAX_ROTATION)
	{
		newRotation = PLAYER_MAX_ROTATION;
	}

	else if (newRotation < -PLAYER_MAX_ROTATION)
	{
		newRotation = -PLAYER_MAX_ROTATION;
	}

	m_player.setRotation(newRotation);
}

void PlayState::FixedUpdate(float dt)
{
	if (m_gameOver)
		return;

	if (m_playerHealth <= 0)
	{
		m_gameOver = true;
	}

	m_bulletSpawner.Update(dt);
	m_astolfoSpawner.Update(dt);
}

void PlayState::DrawHearts()
{
	float offsetX = (HEART_SIZE + SPACE_BETWEEN_HEARTS) * PLAYER_MAX_HEALTH / 2.f;
	int i = 0;

	for (int j = 0; j < (PLAYER_MAX_HEALTH - m_playerHealth); j++)
	{
		m_emptyHeartSprite.setPosition(
			(Config::ScreenWidth / 2.f - offsetX) + i++ * (HEART_SIZE + SPACE_BETWEEN_HEARTS),
			0.f
		);

		m_appData->window.draw(m_emptyHeartSprite);
	}

	for (int j = 0; j < m_playerHealth; j++)
	{
		m_heartSprite.setPosition(
			(Config::ScreenWidth / 2.f - offsetX) + i++ * (HEART_SIZE + SPACE_BETWEEN_HEARTS),
			0.f
		);

		m_appData->window.draw(m_heartSprite);
	}
}

void PlayState::Draw()
{
	static sf::RenderWindow& window = m_appData->window;

	window.clear(sf::Color::White);

	m_bulletSpawner.DrawBullets(window);
	m_astolfoSpawner.DrawAstolfos(window);

	window.draw(m_player);

	DrawHearts();

	if (m_gameOver)
	{
		m_appData->window.draw(m_blackPane);
		m_appData->window.draw(m_spGay);
		m_appData->window.draw(m_gmOver);

		if (m_timeSinceGameOver >= TIME_UNTIL_CONTINUE)
		{
			m_appData->window.draw(m_pressToContinue);
		}
	}

	window.display();
}

void PlayState::Pause()
{
	m_appData->window.draw(m_blackPane);
	m_appData->window.display();
}

void PlayState::Resume()
{

}
