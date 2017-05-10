#include "State_Intro.h"
#include "StateManager.h"
#include <iostream>

State_Intro::State_Intro(StateManager* l_stateManager) : BaseState(l_stateManager) 
{
	this->Create();
}

State_Intro::~State_Intro() 
{
	m_stateManager->GetShared()->m_eventManger->RemoveCallback("Continue");
}

void State_Intro::Create()
{
	m_time = 0.0f;

	m_backgroundTexture.loadFromFile("image/background.jpg");
	m_background.setTexture(m_backgroundTexture);

	int ix = 1;
	for (int i = 0; i < 2; i++)
	{
		m_texture[i].loadFromFile("image/p" + std::to_string(ix) + ".png");
		m_sprite[i].setTexture(m_texture[i]);
		ix++;
	}
	m_sprite[0].setPosition(sf::Vector2f(-401, 100));
	m_sprite[1].setPosition(sf::Vector2f(800, 150));

	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(20);
	m_text.setPosition(290, 550);
	m_text.setStyle(sf::Text::Bold);
	m_text.setString("Press SPACE to continue");

	m_stateManager->GetShared()->m_eventManger->AddCallback("Continue", &State_Intro::Continue, this);
}

void State_Intro::Destroy() {}

void State_Intro::Update(const sf::Time& l_time) 
{
	m_time += l_time.asSeconds();
	if (m_time <= 5.0f)
	{
		m_sprite[0].setPosition(m_sprite[0].getPosition().x + (80 * l_time.asSeconds()), 100);
		m_sprite[1].setPosition(m_sprite[1].getPosition().x - (80 * l_time.asSeconds()), 150);
	}
}

void State_Intro::Draw() 
{
	sf::RenderWindow* window = m_stateManager->GetShared()->m_window->GetRenderedWindow();
	window->draw(m_background);
	for (int i = 0; i < 2; i++)
	{
		window->draw(m_sprite[i]);
	}
	if (m_time >= 5.0f)
	{
		window->draw(m_text);
	}
}

void State_Intro::Continue(EventDetails* l_details)
{
	m_stateManager->SwitchTo<State_Select>();
}