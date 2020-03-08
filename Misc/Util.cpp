#include "Util.h"

float Util::GetVectorMagnitude(const sf::Vector2f& vector)
{
	return std::sqrt(std::pow(vector.x, 2.f) + std::pow(vector.y, 2.f));
}

bool Util::IsOutOfScreen(const sf::Shape& shape, float screenWidth, float screenHeight)
{
	const sf::Vector2f& origin = shape.getOrigin();
	const sf::Vector2f& pos = shape.getPosition();

	if (pos.x < -origin.x)
	{
		return true;
	}

	else if (pos.x > (screenWidth + origin.x))
	{
		return true;
	}

	else if (pos.y < -origin.y)
	{
		return true;
	}

	else if (pos.y > (screenHeight + origin.y))
	{
		return true;
	}

	return false;
}

bool Util::IsOutOfScreen(const sf::Sprite& shape, float screenWidth, float screenHeight)
{
	const sf::Vector2f& origin = shape.getOrigin();
	const sf::Vector2f& pos = shape.getPosition();

	if (pos.x < -origin.x)
	{
		return true;
	}

	else if (pos.x > (screenWidth + origin.x))
	{
		return true;
	}

	else if (pos.y < -origin.y)
	{
		return true;
	}

	else if (pos.y > (screenHeight + origin.y))
	{
		return true;
	}

	return false;
}

std::vector<std::string> Util::SplitString(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;

	size_t current, previous = 0;
	current = str.find_first_of(delim);
	while (current != std::string::npos) {
		std::string temp = str.substr(previous, current - previous);
		if (!temp.empty())
		{
			tokens.push_back(temp);
		}

		previous = current + 1;
		current = str.find_first_of(delim, previous);
	}

	return tokens;
}
