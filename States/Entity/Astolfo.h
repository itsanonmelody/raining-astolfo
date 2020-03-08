#pragma once

#include "../../Core/ResourceManager.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Astolfo : public sf::Drawable
{
private:
	static const char* SPRITE_TEXTURE;
	static long long nAstolfos;

	long long m_index;
	sf::Sprite m_sprite;
	float m_speed;
	float m_angleVelocity;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Astolfo(const sf::Vector2f& pos, float speed, float angleVelocity, const ResourceManager& resources);
	~Astolfo() { }

	Astolfo(Astolfo& other) noexcept;
	Astolfo(Astolfo&& other) noexcept;

	Astolfo& operator=(Astolfo& other) noexcept;
	Astolfo& operator=(Astolfo&& other) noexcept;

	bool operator==(const Astolfo& other);

	void Update(float dt);

	bool Intercepts(const sf::FloatRect& bounds);

	bool IsOutOfScreen(float width, float height);
};
