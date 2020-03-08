#include "ResourceManager.h"

void ResourceManager::LoadFont(const std::string& name, const std::string& fontFile)
{
	sf::Font font;
	if (!font.loadFromFile(fontFile))
	{
		throw "Failed to load font: " + fontFile;
	}

	m_fonts[name] = std::move(font);
}

void ResourceManager::UnloadFont(const std::string& name)
{
	std::map<std::string, sf::Font>::iterator item;
	if ((item = m_fonts.find(name)) != m_fonts.end())
	{
		m_fonts.erase(item);
	}
}

void ResourceManager::LoadTexture(const std::string& name, const std::string& textureFile)
{
	sf::Texture texture;
	if (!texture.loadFromFile(textureFile))
	{
		throw "Failed to load texture: " + textureFile;
	}

	m_textures[name] = std::move(texture);
}

void ResourceManager::UnloadTexture(const std::string& name)
{
	std::map<std::string, sf::Texture>::iterator item;
	if ((item = m_textures.find(name)) != m_textures.end())
	{
		m_textures.erase(item);
	}
}

const sf::Font& ResourceManager::GetFont(const std::string& name) const
{
	return m_fonts.at(name);
}

const sf::Texture& ResourceManager::GetTexture(const std::string& name) const
{
	return m_textures.at(name);
}
