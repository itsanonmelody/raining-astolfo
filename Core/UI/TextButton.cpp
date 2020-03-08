#include "TextButton.h"

#include <SFML/Graphics.hpp>

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text);
}

void TextButton::HandleEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		if (!m_pressed)
		{
			if (IsMouseOnText())
			{
				OnHoverEnter();
			}

			else if (m_isHover)
			{
				OnHoverExit();
			}
		}

		break;

	case sf::Event::MouseButtonPressed:
		if (IsMouseOnText())
		{
			OnPressDown();
		}

		break;

	case sf::Event::MouseButtonReleased:
		if (m_pressed)
		{
			if (IsMouseOnText())
			{
				m_handler();
			}

			OnPressUp();
		}

		break;
	}
}

bool TextButton::IsMouseOnText()
{
	sf::Vector2i mouse(sf::Mouse::getPosition(m_window));

	if (m_text.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
	{
		return true;
	}

	return false;
}

void TextButton::OnPressDown()
{
	m_text.setFillColor(m_textColorDark);

	m_pressed = true;
}

void TextButton::OnPressUp()
{
	m_text.setFillColor(m_textColor);

	m_pressed = false;
}

void TextButton::OnHoverEnter()
{
	const auto& oldBounds = m_text.getLocalBounds();

	m_text.setCharacterSize(m_charSize + 4);
	const auto& newBounds = m_text.getLocalBounds();

	float dx = (newBounds.width - oldBounds.width) / 2.f;
	float dy = (newBounds.height - oldBounds.height) / 2.f;

	m_text.setPosition(m_text.getPosition() - sf::Vector2f(dx, dy));

	m_isHover = true;
}

void TextButton::OnHoverExit()
{
	const auto& oldBounds = m_text.getLocalBounds();

	m_text.setCharacterSize(m_charSize);
	const auto& newBounds = m_text.getLocalBounds();

	float dx = (newBounds.width - oldBounds.width) / 2.f;
	float dy = (newBounds.height - oldBounds.height) / 2.f;

	m_text.setPosition(m_text.getPosition() - sf::Vector2f(dx, dy));

	m_isHover = false;
}

TextButton::TextButton(sf::RenderWindow& window, const OnClickHandler& handler)
	: m_window(window)
{
	m_handler = handler;
	m_textColor = m_text.getFillColor();
	m_charSize = m_text.getCharacterSize();

	m_textColorDark = m_text.getFillColor();
	m_textColorDark.r = (m_textColorDark.r - 15 > 0 ? m_textColorDark.r - 15 : 0);
	m_textColorDark.g = (m_textColorDark.g - 15 > 0 ? m_textColorDark.r - 15 : 0);
	m_textColorDark.b = (m_textColorDark.b - 15 > 0 ? m_textColorDark.r - 15 : 0);
}
TextButton::TextButton(sf::RenderWindow& window, const sf::Text& text, const OnClickHandler& handler)
	: m_window(window)
{
	m_handler = handler;
	m_text = text;
	m_textColor = text.getFillColor();
	m_charSize = text.getCharacterSize();

	m_textColorDark = text.getFillColor();
	m_textColorDark.r = (m_textColorDark.r - 15 > 0 ? m_textColorDark.r - 15 : 0);
	m_textColorDark.g = (m_textColorDark.g - 15 > 0 ? m_textColorDark.r - 15 : 0);
	m_textColorDark.b = (m_textColorDark.b - 15 > 0 ? m_textColorDark.r - 15 : 0);
}

void TextButton::SetHandler(const OnClickHandler& handler)
{
	m_handler = handler;
}

void TextButton::SetText(const sf::Text& text)
{
	m_text = text;
	m_textColor = text.getFillColor();
	m_charSize = text.getCharacterSize();

	m_textColorDark = text.getFillColor();
	m_textColorDark.r = (m_textColorDark.r - 20 > 0 ? m_textColorDark.r - 20 : 0);
	m_textColorDark.g = (m_textColorDark.g - 20 > 0 ? m_textColorDark.r - 20 : 0);
	m_textColorDark.b = (m_textColorDark.b - 20 > 0 ? m_textColorDark.r - 20 : 0);
}

void TextButton::SetPosition(float x, float y)
{
	m_text.setPosition(x, y);
}

void TextButton::SetPosition(const sf::Vector2f& pos)
{
	m_text.setPosition(pos);
}