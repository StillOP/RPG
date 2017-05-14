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
				break;
			}
		}
		else if(b_itr.second.first.m_eventType == l_event.type && b_itr.second.second == l_event.key.code)
		{
			++b_itr.second.first.m_count;
			break;
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
}

sf::Vector2i EventManager::GetMousePosition(sf::RenderWindow *l_window)
{
	return (l_window? sf::Mouse::getPosition(*l_window) : sf::Mouse::getPosition());
}