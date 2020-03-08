#include "App.h"

#include "Config.h"
#include "States/MainMenuState.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <numeric>
#include <chrono>

App::App()
	: m_appData(new AppData(*this))
{
	m_outOfFocus = false;

	m_settings.antialiasingLevel = 8;

	m_appData->window.create(
		sf::VideoMode(Config::ScreenWidth, Config::ScreenHeight),
		Config::AppTitle,
		Config::WindowStyle
	);

	m_appData->stateManager.AddState(StateRef(new MainMenuState(m_appData)));
}

void App::ProcessArguments(const std::vector<std::string>& args)
{
	
}

void App::Init()
{
	m_appData->resources.LoadFont("chewy", Config::ChewyFont);
}

void App::Exit()
{
	m_appData->window.close();
}

void App::HandleEvents()
{
	static sf::Event event;
	while (m_appData->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::GainedFocus:
			m_outOfFocus = false;
			m_appData->stateManager.GetCurrentState()->Resume();
			break;

		case sf::Event::LostFocus:
			m_outOfFocus = true;
			m_appData->stateManager.GetCurrentState()->Pause();
			break;

		case sf::Event::Closed:
			Exit();
			break;
		}

		m_appData->stateManager.GetCurrentState()->HandleEvent(event);
	}
}

int App::Run()
{
	using std::chrono::steady_clock;

	const float FPS = 1.f / Config::FRAME_RATE;

	auto prev = steady_clock::now();

	while (m_appData->window.isOpen())
	{
		auto now = steady_clock::now();
		std::chrono::duration<float> deltaTime = now - prev;

		if (deltaTime.count() < FPS)
		{
			continue;
		}

		prev = now;

		m_appData->stateManager.Update();
		
		HandleEvents();
		
		if (!m_outOfFocus)
		{
			m_appData->stateManager.GetCurrentState()->HandleInput();

			m_appData->stateManager.GetCurrentState()->FixedUpdate(FPS);
			m_appData->stateManager.GetCurrentState()->Update(deltaTime.count());

			m_appData->stateManager.GetCurrentState()->Draw();
		}
	}

	return 0;
}