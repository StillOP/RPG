#include "Window.h"

Window::Window()
{
	m_isOpen = true;
	m_isFullScreen = false;
	Create("RPG", sf::Vector2u(800, 640));
}

Window::Window(std::string l_name, sf::Vector2u l_windowSize)
{
	m_isOpen = true;
	m_isFullScreen = false;
	Create(l_name, l_windowSize);
}

Window::~Window() { EventDetails* l_details;  Close(l_details); }

void Window::Create(std::string l_name, sf::Vector2u l_windowSize)
{
	m_eventManager.AddCallback("Close", &Window::Close, this);
	m_eventManager.AddCallback("ToogleFullscreen", &Window::ToggleFullScreen, this);

	m_windowName = l_name;
	m_windowSize = l_windowSize;
	auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowName, style);
}

void Window::Close(EventDetails* l_details) { m_window.close(); }

void Window::ToggleFullScreen(EventDetails* l_details)
{
	m_window.close();
	m_isFullScreen = !m_isFullScreen;
	Create(m_windowName, m_windowSize);
}

bool Window::isOpen() { return m_isOpen; }

bool Window::isFullScreen() { return m_isFullScreen; }

sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

sf::RenderWindow* Window::GetRenderedWindow() { return &m_window; }

void Window::Update()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		m_eventManager.HandleEvents(event);
	}
}

EventManager* Window::GetEventManger() { return &m_eventManager; }

void Window::Clear() { m_window.clear(sf::Color::White); }

void Window::Display() { m_window.display(); }
