#pragma once

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <cmath>
#include <string>
#include <vector>

namespace Util
{
	template <typename _Ty>
	double GetVectorMagnitude(const sf::Vector2<_Ty>& vector)
	{
		return std::sqrt(std::pow((double)vector.x, 2.0) + std::pow((double)vector.y, 2.0));
	}

	float GetVectorMagnitude(const sf::Vector2f& vector);

	bool IsOutOfScreen(const sf::Shape& shape, float screenWidth, float screenHeight);
	bool IsOutOfScreen(const sf::Sprite& shape, float screenWidth, float screenHeight);

	std::vector<std::string> SplitString(const std::string& str, const std::string& delim = " ");
}
