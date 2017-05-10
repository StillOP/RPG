#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class Personnage
{
public:
	Personnage(float l_pv, float l_damage, bool l_canAttack, std::string l_path);
	~Personnage();

	bool canAttack();
	bool isAlive();

	void Attack(Personnage& l_personnage);
	void AttackSpecial(Personnage& l_personnage);
	void Heal(float l_amount);

	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f l_position);
	void SetCanAttack(bool l_canAttack);

private:
	sf::Texture m_personnageTexture;
	sf::Sprite m_personnage;

	float m_pv;
	float m_damages;
	bool m_canAttack;
};
