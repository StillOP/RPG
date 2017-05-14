#include "State_Select.h"
#include "StateManager.h"
#include <iostream>

State_Select::State_Select(StateManager* l_stateManager) : BaseState(l_stateManager) 
{
	this->Create();
}

State_Select::~State_Select()
{
	m_stateManager->GetShared()->m_eventManger->RemoveCallback("SelectContinue");
}

void State_Select::Create()
{
	m_time = 0.0f;
	//m_index = 0
	m_stateManager->GetShared()->m_id = 0;

	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setPosition(265, 50);
	m_text.setString("Choose your character");
	m_text.setFillColor(sf::Color::Black);

	m_text2.setFont(m_font);
	m_text2.setFillColor(sf::Color::Black);
	m_text2.setCharacterSize(20);
	m_text2.setPosition(290, 550);
	m_text2.setStyle(sf::Text::Bold);
	m_text2.setString("Press C to continue");

	m_backgroundTexture.loadFromFile("image/select_background.jpg");
	m_background.setTexture(m_backgroundTexture);

	for (int i = 0; i < 2; i++)
	{
		m_arrow[i].setPointCount(3);
		m_arrow[i].setRadius(10);
		m_arrow[i].setFillColor(sf::Color(167, 103, 38));
	}

	m_arrow[0].setRotation(-90.0f);
	m_arrow[0].setPosition(sf::Vector2f(205, 335));

	m_arrow[1].setRotation(90.0f);
	m_arrow[1].setPosition(sf::Vector2f(570, 320));

	int ix = 1;
	for (int i = 0; i < 4; i++)
	{
		m_texture[i].loadFromFile("image/img/r" + std::to_string(ix) + ".png");
		ix++;
	}

	m_sprite.setTexture(m_texture[0]);
	m_sprite.setOrigin(150, 120);
	m_sprite.setPosition(400, 320);

	m_stateManager->GetShared()->m_eventManger->AddCallback("SelectContinue", &State_Select::SelectContinue, this);
}

void State_Select::Destroy() {}

void State_Select::Update(const sf::Time& l_time) 
{
	if (m_stateManager->GetShared()->m_id >= 0 && m_stateManager->GetShared()->m_id <= 3)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_time += l_time.asSeconds();
			if (m_time >= 0.1f)
			{
				m_stateManager->GetShared()->m_id--;
				if (m_stateManager->GetShared()->m_id < 0)
				{
					m_sprite.setTexture(m_texture[3]);
					m_stateManager->GetShared()->m_id = 3;
				}
				m_sprite.setTexture(m_texture[m_stateManager->GetShared()->m_id]);
				m_time = 0.0f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_time += l_time.asSeconds();
			if (m_time >= 0.1f)
			{
				m_stateManager->GetShared()->m_id++;
				if (m_stateManager->GetShared()->m_id > 3)
				{
					m_sprite.setTexture(m_texture[0]);
					m_stateManager->GetShared()->m_id = 0;
				}
				m_sprite.setTexture(m_texture[m_stateManager->GetShared()->m_id]);
				m_time = 0.0f;
			}
		}
	}
}

void State_Select::Draw()
{
	m_stateManager->GetShared()->m_window->GetRenderedWindow()->draw(m_background);
	m_stateManager->GetShared()->m_window->GetRenderedWindow()->draw(m_text);
	m_stateManager->GetShared()->m_window->GetRenderedWindow()->draw(m_text2);
	m_stateManager->GetShared()->m_window->GetRenderedWindow()->draw(m_sprite);
	for (int i = 0; i < 2; i++)
	{
		m_stateManager->GetShared()->m_window->GetRenderedWindow()->draw(m_arrow[i]);
	}
}

void State_Select::SelectContinue(EventDetails* l_details)
{
	m_stateManager->SwitchTo<State_Game>();
}

int State_Select::GetIndex() { return m_index; }
