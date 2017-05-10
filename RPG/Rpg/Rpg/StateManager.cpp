#include "StateManager.h"

StateManager::StateManager(Shared* l_shared) : m_shared(l_shared) {}

StateManager::~StateManager()
{
	for (auto &itr : m_states)
	{
		delete itr;
	}
}

void StateManager::Update(const sf::Time& l_time)
{
	m_states.back()->Update(l_time);
}

void StateManager::Draw()
{
	if (m_states.back()->IsTransparent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!(*itr)->IsTransparent())
				{
					break;
				}
			}
			--itr;
		}
		for (; itr != m_states.end(); itr++)
		{
			(*itr)->Draw();
		}
	}
	else
	{
		m_states.back()->Draw();
	}
}

Shared* StateManager::GetShared() { return m_shared; }