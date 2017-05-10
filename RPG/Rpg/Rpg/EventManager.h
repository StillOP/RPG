#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <functional>
#include <unordered_map>
#include <utility>
#include <memory>

struct EventDetails
{
	EventDetails(sf::Event::EventType l_eventType, int l_count): m_eventType(l_eventType), m_count(l_count) {}

	void Clear() { m_eventType = (sf::Event::EventType)0;  m_count = 0; }

	sf::Event::EventType m_eventType;
	int m_count;
};

using Bindings = std::unordered_map<std::string, std::pair<EventDetails, int>>;
using CallbacksContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	template<class T>
	bool AddCallback(std::string l_name, void(T::*l_func)(EventDetails*), T* l_instance)
	{
		auto func = std::bind(l_func, l_instance, std::placeholders::_1);
		return m_callbacks.emplace(l_name, func).second;
	}

	bool RemoveCallback(std::string l_name)
	{
		auto itr = m_callbacks.find(l_name);
		if (itr == m_callbacks.end()) { return false; }

		m_callbacks.erase(l_name);
		return true;
	}

	void HandleEvents(sf::Event l_event);

	sf::Vector2i GetMousePosition(sf::RenderWindow* l_window = nullptr);

private:
	void AddBindings();

	Bindings m_bindings;
	CallbacksContainer m_callbacks;
};