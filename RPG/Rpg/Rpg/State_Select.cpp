#include "State_Select.h"
#include "StateManager.h"

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

	m_shape.setFillColor(sf::Color::Black);
	m_shape.setSize((sf::Vector2f(m_stateManager->GetShared()->m_window->GetWindowSize().x, m_stateManager->GetShared()->m_window->GetWindowSize().y)));
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setPosition(270, 250);
	m_text.setString("Get ready to FIGHT");

	m_text2.setFont(m_font);
	m_text2.setCharacterSize(15);
	m_text2.setPosition(330, 500);
	m_text2.setString("Press C to continue");

	m_stateManager->GetShared()->m_eventManger->AddCallback("SelectContinue", &State_Select::SelectContinue, this);
}

void State_Select::Destroy() {}

void State_Select::Update(const sf::Time& l_time) 
{
	m_time += l_time.asSeconds();
}

void State_Select::Draw()
{
	m_stateManager->GetShared()->m_window->GetRenderedWindow()->draw(m_shape);
	if (m_time >= 2.0f)
	{
		m_stateManager->GetShared()->m_window->GetRenderedWindow()->draw(m_text);
		m_stateManager->GetShared()->m_window->GetRenderedWindow()->draw(m_text2);
	}
}

void State_Select::SelectContinue(EventDetails* l_details)
{
	m_stateManager->SwitchTo<State_Game>();
}