#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Bullet : public sf::Drawable
{
private:
	static unsigned long long nBullets;

	unsigned long long m_index;
	float m_angle;
	float m_speed;

	sf::RectangleShape m_bullet;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Bullet(const sf::Vector2f& start, float angle, float speed);
	~Bullet() { }

	Bullet(Bullet& other) noexcept;
	Bullet(Bullet&& other) noexcept;

	Bullet& operator=(Bullet& other) noexcept;
	Bullet& operator=(Bullet&& other) noexcept;

	bool operator==(const Bullet& other);

	void Update(float dt);

	bool IsOutOfScreen(float width, float height) const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
};
