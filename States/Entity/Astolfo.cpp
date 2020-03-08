#include "Astolfo.h"

#include <SFML/Graphics/RenderTarget.hpp>

const char* Astolfo::SPRITE_TEXTURE = "astolfo";
long long Astolfo::nAstolfos;

void Astolfo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

Astolfo::Astolfo(const sf::Vector2f& pos, float speed, float angleVelocity, const ResourceManager& resources)
	: m_speed(speed), m_angleVelocity(angleVelocity), m_index(nAstolfos++)
{
	m_sprite.setTexture(resources.GetTexture(SPRITE_TEXTURE));
	m_sprite.setPosition(pos);
	m_sprite.setScale(0.2f, 0.2f);

	const sf::FloatRect& bounds = m_sprite.getGlobalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

Astolfo::Astolfo(Astolfo& other) noexcept
{
	m_index = nAstolfos++;
	m_angleVelocity = other.m_angleVelocity;
	m_speed = other.m_speed;
	m_sprite = other.m_sprite;
}

Astolfo::Astolfo(Astolfo&& other) noexcept
{
	m_index = other.m_index;
	m_angleVelocity = other.m_angleVelocity;
	m_speed = other.m_speed;
	m_sprite = std::move(other.m_sprite);
}

Astolfo& Astolfo::operator=(Astolfo& other)noexcept
{
	m_index = nAstolfos++;
	m_angleVelocity = other.m_angleVelocity;
	m_speed = other.m_speed;
	m_sprite = other.m_sprite;

	return *this;
}

Astolfo& Astolfo::operator=(Astolfo&& other) noexcept
{
	m_index = other.m_index;
	m_angleVelocity = other.m_angleVelocity;
	m_speed = other.m_speed;
	m_sprite = std::move(other.m_sprite);

	return *this;
}

bool Astolfo::operator==(const Astolfo& other)
{
	return m_index == other.m_index;
}

void Astolfo::Update(float dt)
{
	m_sprite.move(0, m_speed * dt);
	m_sprite.rotate(m_angleVelocity * dt);
}

bool Astolfo::Intercepts(const sf::FloatRect& bounds)
{
	return m_sprite.getGlobalBounds().intersects(bounds);
}

bool Astolfo::IsOutOfScreen(float width, float height)
{
	if (m_sprite.getPosition().y > (height + m_sprite.getOrigin().y))
	{
		return true;
	}

	return false;
}
