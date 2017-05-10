#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "EventManager.h"

class Window
{
public:
	Window();
	Window(std::string l_name, sf::Vector2u l_windowSize);
	~Window();

	void Update();
	void Clear();
	void Display();
	bool isOpen();

	sf::Vector2u GetWindowSize();
	sf::RenderWindow* GetRenderedWindow();
	EventManager* GetEventManger();

private:
	void Create(std::string l_name, sf::Vector2u l_windowSize);
	void Close(EventDetails* l_details);

	void ToggleFullScreen(EventDetails* l_details);

	bool isFullScreen();

	sf::Vector2u m_windowSize;
	std::string m_windowName;
	sf::RenderWindow m_window;
	EventManager m_eventManager;

	bool m_isOpen;
	bool m_isFullScreen;
};
