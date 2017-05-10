#pragma once
#include "BaseState.h"
#include "BattleManager.h"

class State_Game : public BaseState
{
public:
	State_Game(StateManager* l_stateManager);
	~State_Game();

	void Create();
	void Destroy();

	void Update(const sf::Time& l_time);
	void Draw();

	void Pause(EventDetails* l_details);

	void PlayerAttack(EventDetails* l_details);
	void PlayerAttackSpecial(EventDetails* l_details);
	void PlayerHeal(EventDetails* l_details);

private:
	sf::Texture m_area;
	sf::Sprite m_areaSprite;

	BattleManager m_battleManager;
};

