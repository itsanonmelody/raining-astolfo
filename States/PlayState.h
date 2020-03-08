#pragma once

#include "../App.h"

#include "Entity/Bullet.h"
#include "Entity/BulletSpawner.h"
#include "Entity/AstolfoSpawner.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>
#include <random>
#include <chrono>

class PlayState : public State
{
private:
	AppDataRef m_appData;

	const float PI = 3.14159265359f;
	const float HEART_SIZE = 30.f;
	const float SPACE_BETWEEN_HEARTS = 10.f;
	const float TIME_UNTIL_CONTINUE = 3.f;

	bool m_gameOver;
	float m_timeSinceGameOver;

	sf::Sprite m_spGay;
	sf::Text m_gmOver;
	sf::Text m_pressToContinue;
	sf::RectangleShape m_blackPane;

	sf::RectangleShape m_player;
	int m_playerHealth = 3;
	const int PLAYER_MAX_HEALTH = 3;
	const float PLAYER_MAX_ROTATION = 60.f;

	sf::Sprite m_heartSprite;
	sf::Sprite m_emptyHeartSprite;

	BulletSpawner m_bulletSpawner;
	float m_timeSinceLastBullet = 0.f;
	const float BULLET_SPEED = 1080.f;
	const float BULLET_RECOIL = 5.f;
	const float BULLET_SPAWN_RATE = 0.3f; // in seconds.

	AstolfoSpawner m_astolfoSpawner;
	float m_timeSinceLastAstolfo = 0.f;
	const float ASTOLFO_BASE_FALL_SPEED = 50.f;
	const float ASTOLFO_FALL_SPEED_RATE = 150.f;
	const float ASTOLFO_ANGLULAR_VELOCITY = 50.f;
	const float ASTOLFO_SPAWN_RATE = 0.35f; // in seconds.

	// Randomizer
	std::mt19937 m_gen;
	std::uniform_real_distribution<float> m_dist;

	void SpawnBullet();

	void SpawnAstolfo();
	void CheckAstolfos();

	void DrawHearts();
	
public:
	PlayState(AppDataRef& appData);
	~PlayState() { }

	void Init() override;
	void CleanUp() override;

	void HandleEvent(const sf::Event& event) override;
	void HandleInput() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw() override;

	void Pause() override;
	void Resume() override;
};
