#pragma once

#include <SFML/Window/WindowStyle.hpp>

namespace Config
{
	// Application Data
	constexpr const char* AppTitle = "Raining Astolfo";
	constexpr int ScreenWidth = 800;
	constexpr int ScreenHeight = 600;
	constexpr int WindowStyle = sf::Style::Close | sf::Style::Titlebar;
	constexpr int FullScreenWindowStyle = sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen;
	constexpr float FRAME_RATE = 60.f;

	// Resources
	constexpr const char* AstolfoImage = "Resources/Images/astolfo.png";
	constexpr const char* HahGayAstolfoImage = "Resources/Images/hah-gay.png";
	constexpr const char* HeartImage = "Resources/Images/Heart.png";
	constexpr const char* EmptyHeartImage = "Resources/Images/Heartless.png";
	constexpr const char* ChewyFont = "Resources/Fonts/Chewy-Regular.ttf";
}
