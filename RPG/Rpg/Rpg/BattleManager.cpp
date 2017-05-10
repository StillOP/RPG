#include "BattleManager.h"

BattleManager::BattleManager(Shared* l_shared) : m_shared(l_shared)
{
	m_player = new Personnage(1000, 50, true, "image/r2.png");
	m_opponent = new Personnage(1000, 50, false, "image/l3.png");

	m_player->SetPosition(sf::Vector2f(0, 300));
	m_opponent->SetPosition(sf::Vector2f(500, 300));
}

BattleManager::~BattleManager()
{
	delete m_player;
	delete m_opponent;
}

void BattleManager::Update()
{
	if (m_opponent->canAttack())
	{
		int a = rand() % 4;
		Action action = (Action)a;
		switch (action)
		{
		case Action::Attack: { m_opponent->Attack(*m_player); break; }
		case Action::AttackSpecial: { m_opponent->AttackSpecial(*m_player); break; }
		case Action::Heal: {m_opponent->Heal(rand() % 50); break; }
		};
	}
}

void BattleManager::Draw()
{
	m_shared->m_window->GetRenderedWindow()->draw(m_player->GetSprite());
	m_shared->m_window->GetRenderedWindow()->draw(m_opponent->GetSprite());
}

Personnage* BattleManager::GetPlayer() { return m_player; }

Personnage* BattleManager::GetOpponent() { return m_opponent; }