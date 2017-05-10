#pragma once
#include "Window.h"
#include "EventManager.h"

struct Shared
{
	Shared(): m_window(nullptr), m_eventManger(nullptr) {}

	Window* m_window;
	EventManager* m_eventManger;
};
