#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <map>
#include <string>

class ResourceManager
{
private:
	std::map <std::string, sf::Font> m_fonts;
	std::map <std::string, sf::Texture> m_textures;

public:
	void LoadFont(const std::string& name, const std::string& fontFile);
	void UnloadFont(const std::string& name);

	void LoadTexture(const std::string& name, const std::string& textureFile);
	void UnloadTexture(const std::string& name);

	const sf::Font& GetFont(const std::string& name) const;
	const sf::Texture& GetTexture(const std::string& name) const;
};
