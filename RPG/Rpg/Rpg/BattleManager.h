#pragma once
#include "Personnage.h"
#include "Shared.h"
#include <random>

enum class Action { Attack = 0, AttackSpecial, Heal, };

class BattleManager
{
public:
	BattleManager(Shared* l_shared);
	~BattleManager();

	void Update();
	void Draw();

	Personnage* GetPlayer();
	Personnage* GetOpponent();

private:
	Personnage* m_player;
	Personnage* m_opponent;

	Shared* m_shared;
	float m_time;
};
