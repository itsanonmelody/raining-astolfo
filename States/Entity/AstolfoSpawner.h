#include "Astolfo.h"

#include "../../Config.h"
#include "../../Core/ResourceManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <algorithm>
#include <iostream>

class AstolfoSpawner
{
private:
	std::vector<Astolfo> m_astolfos;

public:
	void Spawn(const sf::Vector2f& pos, float speed, float angleVelocity, const ResourceManager& resources)
	{
		m_astolfos.push_back(Astolfo(pos, speed, angleVelocity, resources));
	}

	void Update(float dt)
	{
		for (auto& a : m_astolfos)
		{
			a.Update(dt);
		}
	}

	void DrawAstolfos(sf::RenderWindow& window)
	{
		for (auto& a : m_astolfos)
		{
			window.draw(a);
		}
	}

	std::vector<Astolfo>& GetAstolfos()
	{
		return m_astolfos;
	}
};

