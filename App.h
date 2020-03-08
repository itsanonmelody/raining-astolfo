#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include "Core/StateManager.h"
#include "Core/ResourceManager.h"

#include <memory>
#include <vector>
#include <string>

class App;
struct AppData
{
	App& app;
	sf::RenderWindow window;
	StateManager stateManager;
	ResourceManager resources;

	AppData(App& app)
		: app(app) { }
};

using AppDataRef = std::shared_ptr<AppData>;

class App
{
private:
	AppDataRef m_appData;
	sf::ContextSettings m_settings;

	bool m_outOfFocus;

public:
	App();
	~App() { }

	void ProcessArguments(const std::vector<std::string>& args);
	void Init();

	int Run();
	void HandleEvents();
	void Exit();
};
