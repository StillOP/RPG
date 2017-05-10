#include "Game.h"

Game::Game() : m_window("RPG", sf::Vector2u(800, 640)), m_stateManager(&m_shared)
{
	srand((int)time(nullptr));
	m_clock.restart();
	m_shared.m_window = &m_window;
	m_shared.m_eventManger = m_window.GetEventManger();
	m_stateManager.SwitchTo<State_Intro>();
}

Game::~Game() {}

void Game::Update()
{
	m_window.Update();
	m_stateManager.Update(m_time);
}

void Game::Render()
{
	m_window.Clear();
	m_stateManager.Draw();
	m_window.Display();
}


Window* Game::GetWindow() { return &m_window; }

void Game::RestartClock() { m_time = m_clock.restart(); }
