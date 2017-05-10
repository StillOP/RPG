#pragma once
#include "Window.h"
#include "EventManager.h"

class StateManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* l_stateManager): m_stateManager(l_stateManager), m_isTransparent(false) {}
	virtual ~BaseState() {}

	virtual void Create() = 0;
	virtual void Destroy() = 0;

	virtual void Update(const sf::Time& l_time) = 0;
	virtual void Draw() = 0;

	void SetTransparent(bool l_isTransparent) { m_isTransparent = l_isTransparent; }

	bool IsTransparent() { return m_isTransparent; }

protected:
	StateManager* m_stateManager;
	bool m_isTransparent;
};
