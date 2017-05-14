#pragma once
#include "BaseState.h"
#include "Personnage.h"
#include <vector>

enum class Action { Attack = 0, Special, Heal };

class State_Game : public BaseState
{
public:
	State_Game(StateManager* l_stateManager);
	~State_Game();

	void Create();
	void Destroy();

	void Update(const sf::Time& l_time);
	void Draw();

private:
	void Attack(Personnage& l_personnage, const sf::Time& l_time);
	void AttackSpecial(Personnage& l_personnage, const sf::Time& l_time);
	void Heal(Personnage& l_personnage);
	void Reset(const sf::Time& l_time);
	void OpponentManagement(const sf::Time& l_time);

	sf::Texture m_area;
	sf::Sprite m_areaSprite;

	sf::RectangleShape m_pvContainer[2];
	sf::RectangleShape m_pvShape[2];

	sf::RectangleShape m_manaShape[2];

	Personnage m_player;
	Personnage m_opponent;
	std::string m_path;
	int m_IdO;
	std::string m_Opath;

	sf::Font m_font;
	sf::Text m_endText;
	sf::Text m_instruction;
	sf::Text m_text2;

	bool canAttack;
	bool m_gameContinue;
	bool change;
	float m_time;
	float m_time2;
};

