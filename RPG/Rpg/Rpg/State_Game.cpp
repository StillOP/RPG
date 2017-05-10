#include "State_Game.h"
#include "StateManager.h"
#include <iostream>

State_Game::State_Game(StateManager* l_stateManager) : BaseState(l_stateManager), m_battleManager(l_stateManager->GetShared())
{
	this->Create();
}

State_Game::~State_Game()
{
	m_stateManager->GetShared()->m_eventManger->RemoveCallback("PlayerAttack");
	m_stateManager->GetShared()->m_eventManger->RemoveCallback("PlayerAttackSpecial");
	m_stateManager->GetShared()->m_eventManger->RemoveCallback("PlayerHeal");

}

void State_Game::Create()
{
	m_area.loadFromFile("image/arena.jpg");
	m_areaSprite.setTexture(m_area);

	m_stateManager->GetShared()->m_eventManger->AddCallback("Pause", &State_Game::Pause, this);
	m_stateManager->GetShared()->m_eventManger->AddCallback("PlayerAttack", &State_Game::PlayerAttack, this);
	m_stateManager->GetShared()->m_eventManger->AddCallback("PlayerAttackSpecial", &State_Game::PlayerAttackSpecial, this);
	m_stateManager->GetShared()->m_eventManger->AddCallback("PlayerHeal", &State_Game::PlayerHeal, this);
}

void State_Game::Destroy() {}

void State_Game::Update(const sf::Time& l_time) 
{
	m_battleManager.Update();
}

void State_Game::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetShared()->m_window->GetRenderedWindow();
	window->draw(m_areaSprite);
	m_battleManager.Draw();
}

void State_Game::Pause(EventDetails* l_details)
{
	//m_stateManager->SwitchTo<State_Pause>();
}

void State_Game::PlayerAttack(EventDetails* l_details)
{
	m_battleManager.GetPlayer()->Attack(*m_battleManager.GetOpponent());
	m_battleManager.GetOpponent()->SetCanAttack(true);
	m_battleManager.GetPlayer()->SetPosition(sf::Vector2f(0, 0));
}

void State_Game::PlayerAttackSpecial(EventDetails* l_details)
{
	m_battleManager.GetPlayer()->AttackSpecial(*m_battleManager.GetOpponent());
	m_battleManager.GetOpponent()->SetCanAttack(true);
}

void State_Game::PlayerHeal(EventDetails* l_details)
{
	m_battleManager.GetPlayer()->Heal(rand() % 50);
	m_battleManager.GetOpponent()->SetCanAttack(true);
}