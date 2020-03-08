#pragma once

#include "../App.h"
#include "../Core/UI/TextButton.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MainMenuState : public State
{
private:
	AppDataRef m_appData;

	sf::Text m_titleText;
	sf::Sprite m_titleImage;

	TextButton m_playButton, m_exitButton;
	sf::Color m_bgColor = sf::Color(252, 220, 221);
	sf::Color m_textColor = sf::Color(214, 155, 147);
	sf::Color m_textOutlineColor = sf::Color(254, 216, 203);

public:
	MainMenuState(AppDataRef& appData);
	~MainMenuState() { }

	void Init() override;
	void CleanUp() override;

	void HandleEvent(const sf::Event& event) override;
	
	void Draw() override;
};
