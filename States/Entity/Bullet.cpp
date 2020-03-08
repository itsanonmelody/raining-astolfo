#include "Bullet.h"

#include "../../Misc/Util.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <cmath>

unsigned long long Bullet::nBullets = 0;

static const float PI = 3.14159265359f;

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_bullet);
}

Bullet::Bullet(const sf::Vector2f& start, float angle, float speed)
	: m_angle(angle * PI / 180.f), m_speed(speed), m_index(nBullets++)
{
	m_bullet.setSize(sf::Vector2f(8.f, 12.f));
	m_bullet.setFillColor(sf::Color::Yellow);
	m_bullet.setPosition(start);
	m_bullet.setRotation(angle);

	sf::FloatRect bounds = m_bullet.getLocalBounds();
	m_bullet.setOrigin(
		bounds.width / 2.f,
		bounds.height
	);
}

Bullet::Bullet(Bullet& other) noexcept
{
	m_index = nBullets++;
	m_angle = other.m_angle;
	m_speed = other.m_speed;
	m_bullet = other.m_bullet;
}

Bullet::Bullet(Bullet&& other) noexcept
{
	m_index = other.m_index;
	m_angle = other.m_angle;
	m_speed = other.m_speed;
	m_bullet = std::move(other.m_bullet);
}

Bullet& Bullet::operator=(Bullet& other)noexcept
{
	m_index = nBullets++;
	m_angle = other.m_angle;
	m_speed = other.m_speed;
	m_bullet = other.m_bullet;

	return *this;
}

Bullet& Bullet::operator=(Bullet&& other) noexcept
{
	m_index = other.m_index;
	m_angle = other.m_angle;
	m_speed = other.m_speed;
	m_bullet = std::move(other.m_bullet);

	return *this;
}

bool Bullet::operator==(const Bullet& other)
{
	return m_index == other.m_index;
}

void Bullet::Update(float dt)
{
	float dx = m_speed * std::sin(m_angle) * dt;
	float dy = m_speed * std::cos(m_angle) * dt;

	m_bullet.move(dx, -dy);
}

bool Bullet::IsOutOfScreen(float width, float height) const
{
	return Util::IsOutOfScreen(m_bullet, width, height);
}

sf::FloatRect Bullet::getLocalBounds() const
{
	return m_bullet.getLocalBounds();
}

sf::FloatRect Bullet::getGlobalBounds() const
{
	return m_bullet.getGlobalBounds();
}
