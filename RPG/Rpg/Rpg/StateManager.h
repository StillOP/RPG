#pragma once
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include "Shared.h"
#include "BaseState.h"
#include "State_Intro.h"
#include "State_Select.h"
#include "State_Pause.h"
#include "State_Game.h"


using StateContainer = std::vector<BaseState*>;

class StateManager
{
public:
	StateManager(Shared* l_shared);
	~StateManager();

	template<class T>
	void SwitchTo()
	{
		bool hasState = HasState<T>();
		if (hasState)
		{
			for (auto itr = m_states.begin(); itr != m_states.end(); itr++)
			{
				if (itr == std::find(m_states.begin(), m_states.end(), new T(this)))
				{
					BaseState* newState = (*itr);
					m_states.erase(itr);
					m_states.push_back(newState);
				}
			}
		}
		else
		{
			CreateState<T>();
		}
	}

	void Update(const sf::Time& l_time);
	void Draw();

	Shared* GetShared();

private:
	template<class T>
	void CreateState()
	{
		T* state = new T(this);
		m_states.push_back(state);
	}

	template<class T>	
	bool HasState()
	{
		auto state = std::find(m_states.begin(), m_states.end(), new T(this));
		if (state != m_states.end())
		{
			return true;
		}
		return false;
	}

	Shared* m_shared;
	StateContainer m_states;
};