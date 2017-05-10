#include "Personnage.h"
#include <iostream>

Personnage::Personnage(float l_pv, float l_damage, bool l_canAttack, std::string l_path)
	: m_pv(l_pv), m_damages(l_damage), m_canAttack(l_canAttack) 
{
	m_personnageTexture.loadFromFile(l_path);
	m_personnage.setTexture(m_personnageTexture);
}

Personnage::~Personnage() {}

void Personnage::Attack(Personnage& l_personnage)
{
	l_personnage.m_pv -= m_damages;
}

void Personnage::AttackSpecial(Personnage& l_personnage)
{
	float damages = m_damages + (rand() % 100);
	l_personnage.m_pv -= damages;
}

void Personnage::Heal(float l_amount)
{
	m_pv += l_amount;
}

bool Personnage::canAttack() { return m_canAttack; }

bool Personnage::isAlive()
{
	if (m_pv) { return true; }
	return false;
}

sf::Vector2f Personnage::GetPosition() { return m_personnage.getPosition(); }

void Personnage::SetPosition(sf::Vector2f l_position)
{
	m_personnage.setPosition(l_position.x, l_position.y);
	std::cout << "Ok" << std::endl;
}

sf::Sprite Personnage::GetSprite() { return m_personnage; }

void Personnage::SetCanAttack(bool l_canAttack) { m_canAttack = l_canAttack; }