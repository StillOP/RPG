#include "Personnage.h"
#include <iostream>

Personnage::Personnage(int l_ID, float l_pv, float l_mana, float l_damage, std::string l_path)
	: m_pv(l_pv), m_mana(l_mana), m_damages(l_damage), m_ID(l_ID)
{
	m_personnageTexture.loadFromFile(l_path);
	m_personnage.setTexture(m_personnageTexture);
}

Personnage::~Personnage() {}

void Personnage::Attack(Personnage& l_personnage, sf::RectangleShape& l_pvShape)
{
	l_personnage.m_pv -= m_damages;
	float shapeDamages = m_damages / 5.0f;
	if (l_personnage.m_pv <= 0.0f) { l_pvShape.setSize(sf::Vector2f(l_pvShape.getSize().x - l_pvShape.getSize().x, l_pvShape.getSize().y)); return; }
	l_pvShape.setSize(sf::Vector2f(l_pvShape.getSize().x - shapeDamages, l_pvShape.getSize().y));
}

void Personnage::AttackSpecial(Personnage& l_personnage, sf::RectangleShape& l_pvShape, sf::RectangleShape& l_manaShape)
{
	float damages = m_damages + (rand() % 100);
	l_personnage.m_pv -= damages;
	float shapeDamages = damages / 5.0f;
	if (l_personnage.m_pv <= 0.0f) { l_pvShape.setSize(sf::Vector2f(l_pvShape.getSize().x - l_pvShape.getSize().x, l_pvShape.getSize().y)); return; }
	l_pvShape.setSize(sf::Vector2f(l_pvShape.getSize().x - shapeDamages, l_pvShape.getSize().y));

	m_mana -= 20.0f;
	if (m_mana <= 0.0f) { l_manaShape.setSize(sf::Vector2f(l_manaShape.getSize().x - l_manaShape.getSize().x, l_manaShape.getSize().y)); return; }
	l_manaShape.setSize(sf::Vector2f(l_manaShape.getSize().x - 40.0f, l_manaShape.getSize().y));
}

void Personnage::Heal(float l_amount, sf::RectangleShape& l_pvShape, sf::RectangleShape& l_manaShape)
{
	if (m_pv >= 1000) { return; }
	float pv = m_pv + l_amount;
	if (pv >= 1000.0f) { float shapeHeal = (1000.0f - m_pv) / 5.0f; l_pvShape.setSize(sf::Vector2f(l_pvShape.getSize().x + shapeHeal, l_pvShape.getSize().y)); return; }
	m_pv += l_amount;
	float shapeHeal = l_amount / 5.0f;
	l_pvShape.setSize(sf::Vector2f(l_pvShape.getSize().x + shapeHeal, l_pvShape.getSize().y));

	m_mana -= 20.0f;
	if (m_mana <= 0.0f) { l_manaShape.setSize(sf::Vector2f(l_manaShape.getSize().x - l_manaShape.getSize().x, l_manaShape.getSize().y)); return; }
	l_manaShape.setSize(sf::Vector2f(l_manaShape.getSize().x - 40.0f, l_manaShape.getSize().y));
}

bool Personnage::isAlive()
{
	if (m_pv <= 0.0f) { return false; }
	return true;
}

sf::Vector2f Personnage::GetPosition() { return m_personnage.getPosition(); }

void Personnage::SetPosition(float l_x, float l_y)
{
	m_personnage.setPosition(l_x, l_y);
}
 
void Personnage::Draw(sf::RenderWindow& l_window)
{
	l_window.draw(m_personnage);
}

void Personnage::ChangeTexture(std::string l_path)
{
	m_personnageTexture.loadFromFile(l_path);
	m_personnage.setTexture(m_personnageTexture);
}

int Personnage::GetID() { return m_ID; }

float Personnage::GetMana() { return m_mana; }