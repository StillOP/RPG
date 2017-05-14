#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class Personnage
{
public:
	Personnage(int l_ID, float l_pv, float l_mana, float l_damage, std::string l_path);
	~Personnage();

	bool isAlive();
	float GetMana();

	void Attack(Personnage& l_personnage, sf::RectangleShape& l_shape);
	void AttackSpecial(Personnage& l_personnage, sf::RectangleShape& l_pvShape, sf::RectangleShape& l_manaShape);
	void Heal(float l_amount, sf::RectangleShape& l_pvShape, sf::RectangleShape& l_manaShape);

	void Draw(sf::RenderWindow& l_window);

	sf::Vector2f GetPosition();
	void SetPosition(float l_x, float l_y);
	void ChangeTexture(std::string l_path);
	int GetID();

private:
	sf::Texture m_personnageTexture;
	sf::Sprite m_personnage;

	float m_pv;
	float m_mana;
	float m_damages;
	int m_ID;
};
