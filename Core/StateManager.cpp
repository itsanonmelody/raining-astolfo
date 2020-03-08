#include "StateManager.h"

StateManager::StateManager()
{
	m_add = false;
	m_remove = false;
	m_replace = true;
}

void StateManager::AddState(StateRef&& state, bool replace)
{
	m_add = true;
	m_replace = replace;
	m_newState = std::move(state);
}

void StateManager::RemoveState()
{
	m_remove = true;
}

void StateManager::Update()
{
	if (m_add)
	{
		if (m_replace)
		{
			if (!m_states.empty())
			{
				m_states.pop();
			}
		}

		else
		{
			if (!m_states.empty())
			{
				m_states.top()->Pause();
			}
		}

		m_newState->Init();
		m_states.push(std::move(m_newState));

		m_add = false;
	}

	if (m_remove)
	{
		if (!m_states.empty())
		{
			m_states.pop();

			if (!m_states.empty())
			{
				m_states.top()->Resume();
			}
		}

		m_remove = false;
	}
}

const StateRef& StateManager::GetCurrentState() const
{
	return m_states.top();
}