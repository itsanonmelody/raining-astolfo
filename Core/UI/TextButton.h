#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <functional>

class TextButton : public sf::Drawable
{
private:
	using OnClickHandler = std::function<void()>;

	sf::RenderWindow& m_window;
	sf::Text m_text;
	sf::Color m_textColor, m_textColorDark;
	int m_charSize;
	OnClickHandler m_handler;

	bool m_pressed = false;
	bool m_isHover = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool IsMouseOnText();

	void OnPressDown();
	void OnPressUp();

	void OnHoverEnter();
	void OnHoverExit();

public:
	TextButton(sf::RenderWindow& window, const OnClickHandler& handler = []{ });
	TextButton(sf::RenderWindow& window, const sf::Text& text, const OnClickHandler& handler = []{ });

	void HandleEvent(const sf::Event& event);

	void SetHandler(const OnClickHandler& handler);

	void SetText(const sf::Text& text);
	const sf::Text& GetText() const
	{
		return m_text;
	}

	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f& pos);
	const sf::Vector2f& GetPosition()
	{
		return m_text.getPosition();
	}

	const sf::FloatRect GetLocalBounds() const
	{
		return m_text.getLocalBounds();
	}
};
