#include "EventManager.h"
#include <iostream>

EventManager::EventManager()
{
	AddBindings();
}

EventManager::~EventManager() {}

void EventManager::HandleEvents(sf::Event l_event)
{
	for (auto &b_itr : m_bindings)
	{
		if (l_event.type == sf::Event::KeyPressed)
		{
			if (b_itr.second.second == l_event.key.code)
			{
				++b_itr.second.first.m_count;
			}
		}
		else if(b_itr.second.first.m_eventType == l_event.type && b_itr.second.second == l_event.key.code)
		{
			++b_itr.second.first.m_count;
		}
	}

	for (auto &b_itr : m_bindings)
	{
		for (auto &c_itr : m_callbacks)
		{
			if (b_itr.second.first.m_count > 0 && b_itr.first == c_itr.first)
			{
				c_itr.second(&b_itr.second.first);
			}
		}
	}

	for (auto &b_itr : m_bindings)
	{
		b_itr.second.first.Clear();
	}
}

void EventManager::AddBindings()
{
	m_bindings.emplace("Close", std::make_pair(EventDetails(sf::Event::Closed, 0), 0));
	m_bindings.emplace("ToogleFullscreen", std::make_pair(EventDetails(sf::Event::KeyPressed, 0), 89));
	m_bindings.emplace("Continue", std::make_pair(EventDetails(sf::Event::KeyPressed, 0), 57));
	m_bindings.emplace("SelectContinue", std::make_pair(EventDetails(sf::Event::KeyPressed, 0), 2));
	m_bindings.emplace("Pause", std::make_pair(EventDetails(sf::Event::KeyPressed, 0), 15));

	/*m_bindings.emplace("PlayerAttack", std::make_pair(EventDetails(sf::Event::KeyPressed, 0), 22));
	m_bindings.emplace("PlayerAttackSpecial", std::make_pair(EventDetails(sf::Event::KeyPressed, 0), 23));
	m_bindings.emplace("PlayerHeal", std::make_pair(EventDetails(sf::Event::KeyPressed, 0), 7));*/
}

sf::Vector2i EventManager::GetMousePosition(sf::RenderWindow *l_window)
{
	return (l_window? sf::Mouse::getPosition(*l_window) : sf::Mouse::getPosition());
}