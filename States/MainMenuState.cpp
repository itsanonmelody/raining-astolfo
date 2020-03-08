#include "MainMenuState.h"

#include "../Config.h"
#include "PlayState.h"

#include <iostream>

MainMenuState::MainMenuState(AppDataRef& appData)
	: m_appData(appData), m_exitButton(m_appData->window), m_playButton(m_appData->window) { }

void MainMenuState::Init()
{
	m_appData->resources.LoadTexture("astolfo", Config::AstolfoImage);

	m_titleText.setFont(m_appData->resources.GetFont("chewy"));
	m_titleText.setString(Config::AppTitle);
	m_titleText.setCharacterSize(80);
	m_titleText.setFillColor(m_textColor);
	m_titleText.setOutlineColor(m_textOutlineColor);
	m_titleText.setOutlineThickness(3);

	sf::FloatRect bounds = m_titleText.getLocalBounds();
	m_titleText.setPosition(
		(Config::ScreenWidth / 2) - (bounds.width / 2),
		2 * (Config::ScreenHeight / 5) - (bounds.height / 2)
	);

	m_titleImage.setTexture(m_appData->resources.GetTexture("astolfo"));
	m_titleImage.setScale(0.75f, 0.75f);
	m_titleImage.rotate(30.f);

	bounds = m_titleImage.getLocalBounds();
	m_titleImage.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	m_titleImage.setPosition(
		(Config::ScreenWidth / 2),
		2 * (Config::ScreenHeight / 5) - 20.f
	);

	sf::Text playText;
	playText.setFont(m_appData->resources.GetFont("chewy"));
	playText.setString("Play");
	playText.setCharacterSize(32);
	playText.setFillColor(m_textColor);
	playText.setOutlineColor(m_textOutlineColor);
	playText.setOutlineThickness(3);

	m_playButton.SetText(playText);

	bounds = m_playButton.GetLocalBounds();
	m_playButton.SetPosition(
		(Config::ScreenWidth / 2) - (bounds.width / 2),
		11 * (Config::ScreenHeight / 16) - (bounds.height / 2)
	);

	m_playButton.SetHandler([this] {
		m_appData->stateManager.AddState(StateRef(new PlayState(m_appData)));
	});

	sf::Text exitText;
	exitText.setFont(m_appData->resources.GetFont("chewy"));
	exitText.setString("Exit");
	exitText.setCharacterSize(32);
	exitText.setFillColor(m_textColor);
	exitText.setOutlineColor(m_textOutlineColor);
	exitText.setOutlineThickness(3);

	m_exitButton.SetText(exitText);

	bounds = m_exitButton.GetLocalBounds();
	m_exitButton.SetPosition(
		(Config::ScreenWidth / 2) - (bounds.width / 2),
		12 * (Config::ScreenHeight / 16) - (bounds.height / 2)
	);

	m_exitButton.SetHandler([this] {
		m_appData->app.Exit();
	});
}

void MainMenuState::CleanUp()
{
	m_appData->resources.UnloadTexture("astolfo");
}

void MainMenuState::HandleEvent(const sf::Event& event)
{
	m_playButton.HandleEvent(event);
	m_exitButton.HandleEvent(event);
}

void MainMenuState::Draw()
{
	static sf::RenderWindow& window = m_appData->window;

	window.clear(m_bgColor);

	window.draw(m_titleImage);
	window.draw(m_titleText);
	window.draw(m_playButton);
	window.draw(m_exitButton);

	window.display();
}