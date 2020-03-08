#pragma once

#include "State.h"

#include <stack>

class StateManager
{
private:
	std::stack<StateRef> m_states;

	StateRef m_newState;
	bool m_add, m_remove, m_replace;

public:
	StateManager();
	~StateManager() { }

	void AddState(StateRef&& state, bool replace = true);
	void RemoveState();
	void Update();

	const StateRef& GetCurrentState() const;
};
