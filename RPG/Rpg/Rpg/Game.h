#pragma once
#include "Window.h"
#include "StateManager.h"
#include <random>

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();

	Window* GetWindow();

	void Game::RestartClock();

private:
	
	StateManager m_stateManager;
	Shared m_shared;
	Window m_window;

	sf::Clock m_clock;
	sf::Time m_time;
};
