#pragma once

#include <SFML/Window/Event.hpp>

#include <memory>

class State
{
public:
	virtual void Init() { }
	virtual void CleanUp() { }

	virtual void HandleEvent(const sf::Event& event) { }
	virtual void HandleInput() { }

	virtual void Update(float dt) { }
	virtual void FixedUpdate(float dt) { }

	virtual void Draw() { }

	virtual void Pause() { }
	virtual void Resume() { }
};

using StateRef = std::unique_ptr<State>;
