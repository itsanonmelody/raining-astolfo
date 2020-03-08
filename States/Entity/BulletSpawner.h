#pragma once

#include "Bullet.h"

#include "../../Config.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <algorithm>
#include <iostream>

class BulletSpawner
{
private:
	std::vector<Bullet> m_bullets;

public:
	void Spawn(const sf::Vector2f& start, float angle, float speed)
	{
		m_bullets.push_back(Bullet(start, angle, speed));
	}

	void Update(float dt)
	{
		for (auto& b : m_bullets)
		{
			if (b.IsOutOfScreen(Config::ScreenWidth, Config::ScreenHeight))
			{
				m_bullets.erase(std::remove(m_bullets.begin(), m_bullets.end(), b));
				continue;
			}

			b.Update(dt);
		}
	}

	void DrawBullets(sf::RenderWindow& window)
	{
		for (auto& b : m_bullets)
		{
			window.draw(b);
		}
	}

	std::vector<Bullet>& GetBullets()
	{
		return m_bullets;
	}
};
