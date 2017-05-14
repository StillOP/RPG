#include "State_Game.h"
#include "StateManager.h"
#include <iostream>
#include <random>

State_Game::State_Game(StateManager* l_stateManager) : BaseState(l_stateManager), 
m_player(0, 1000.0f, 100.0f, 100.0f, "image/img/r" + std::to_string(m_stateManager->GetShared()->m_id + 1) + ".png"),
m_opponent(1, 1000.0f, 100.0f, 100.0f, "image/img/l" + std::to_string(m_IdO = (rand() % 3) + 1) + ".png")
{
	this->Create();
	m_path = std::to_string(m_stateManager->GetShared()->m_id + 1);
	m_Opath = std::to_string(m_IdO);
}

State_Game::~State_Game()
{
}

void State_Game::Create()
{
	for (int i = 0; i < 2; i++)
	{
		m_pvContainer[i].setSize(sf::Vector2f(210, 20));
		m_pvContainer[i].setFillColor(sf::Color::Black);

		m_pvShape[i].setSize(sf::Vector2f(200, 10));
		m_pvShape[i].setFillColor(sf::Color::Green);

		m_manaShape[i].setSize(sf::Vector2f(200, 5));
		m_manaShape[i].setFillColor(sf::Color(15, 157, 232, 190));
	}

	m_pvContainer[1].setOrigin(210, 0);
	m_pvShape[1].setOrigin(200, 0);

	m_pvContainer[0].setPosition(sf::Vector2f(20, 50));
	m_pvShape[0].setPosition(sf::Vector2f(25, 55));

	m_pvContainer[1].setPosition(sf::Vector2f(780, 50));
	m_pvShape[1].setPosition(sf::Vector2f(775, 55));

	m_manaShape[1].setOrigin(200, 0);

	m_manaShape[0].setPosition(sf::Vector2f(25, 75));
	m_manaShape[1].setPosition(sf::Vector2f(775, 75));


	m_time = 0.0f;
	m_time2 = 0.0f;
	m_gameContinue = true;
	canAttack = true;
	change = false;

	m_area.loadFromFile("image/arena.jpg");
	m_areaSprite.setTexture(m_area);

	m_player.SetPosition(0, 300);
	m_opponent.SetPosition(500, 300);	

	m_font.loadFromFile("arial.ttf");
	m_instruction.setFont(m_font);
	m_instruction.setString(sf::String(" W : Attack \n X : Special Attack \n H : Heal"));
	m_instruction.setCharacterSize(18);
	m_instruction.setStyle(sf::Text::Bold);
	m_instruction.setFillColor(sf::Color::Black);
	m_instruction.setPosition(sf::Vector2f(330.0f, 20.0f));

	m_endText.setFont(m_font);
	m_endText.setCharacterSize(30);
	m_endText.setFillColor(sf::Color(187, 11, 11));
	m_endText.setPosition(sf::Vector2f(330.0f, 300.0f));

	m_text2.setFont(m_font);
	m_text2.setFillColor(sf::Color::Black);
	m_text2.setCharacterSize(20);
	m_text2.setPosition(130, 550);
	m_text2.setStyle(sf::Text::Bold);
}

void State_Game::Destroy() {}

void State_Game::Attack(Personnage& l_personnage, const sf::Time& l_time)
{
	if (l_personnage.GetID() == 0)
	{ 
		l_personnage.SetPosition(l_personnage.GetPosition().x + (35000 * l_time.asSeconds()), l_personnage.GetPosition().y); 
		l_personnage.Attack(m_opponent, m_pvShape[1]);
	}
	else if(l_personnage.GetID()== 1)
	{
		l_personnage.SetPosition(l_personnage.GetPosition().x - (35000 * l_time.asSeconds()), l_personnage.GetPosition().y);
		l_personnage.Attack(m_player, m_pvShape[0]);
	}
}

void State_Game::AttackSpecial(Personnage& l_personnage, const sf::Time& l_time)
{
	if (l_personnage.GetID() == 0)
	{
		l_personnage.ChangeTexture("image/img/ratk" + m_path + ".png");
		l_personnage.SetPosition(l_personnage.GetPosition().x + (35000 * l_time.asSeconds()), l_personnage.GetPosition().y);
		l_personnage.AttackSpecial(m_opponent, m_pvShape[1], m_manaShape[0]);
		change = true;
	}
	else if(l_personnage.GetID() == 1)
	{
		l_personnage.ChangeTexture("image/img/latk" + m_Opath + ".png");
		l_personnage.SetPosition(l_personnage.GetPosition().x - (35000 * l_time.asSeconds()), l_personnage.GetPosition().y);
		l_personnage.AttackSpecial(m_player, m_pvShape[0], m_manaShape[1]);
		change = true;
	}
}

void State_Game::Heal(Personnage& l_personnage)
{
	if (l_personnage.GetID() == 0)
	{
		l_personnage.ChangeTexture("image/img/rheal" + m_path + ".png");
		l_personnage.Heal(rand() % 100, m_pvShape[0], m_manaShape[0]);
		change = true;
	}
	else if (l_personnage.GetID() == 1)
	{
		l_personnage.ChangeTexture("image/img/lheal" + m_Opath+ ".png");
		l_personnage.Heal(rand() % 100, m_pvShape[1], m_manaShape[1]);
		change = true;
	}

}
void State_Game::Reset(const sf::Time& l_time)
{
	if (!canAttack && m_player.GetPosition().x > 0.0f) { m_player.SetPosition(m_player.GetPosition().x - (80 * l_time.asSeconds()), m_player.GetPosition().y); }
	if (canAttack && m_opponent.GetPosition().x < 500.0f) { m_opponent.SetPosition(m_opponent.GetPosition().x + (80 * l_time.asSeconds()), m_opponent.GetPosition().y); }
	if (change)
	{
		m_time += l_time.asSeconds();
		if (m_time >= 1.0f)
		{
			m_player.ChangeTexture("image/img/r" + m_path + ".png");
			m_opponent.ChangeTexture("image/img/l" + m_Opath+ ".png");
			m_time = 0.0f;
			change = false;
		}
	}
	if (m_time2 >= 1.0f) { m_time2 = 0.0f; }
}

void State_Game::OpponentManagement(const sf::Time& l_time)
{
	if (!canAttack)
	{
		m_time2 += l_time.asSeconds();
		if (m_time2 >= 1.0f)
		{
			int a = rand() % 4;
			Action action = (Action)a;
			switch (action)
			{
			case Action::Attack: {Attack(m_opponent, l_time); canAttack = true; break; }

			case Action::Special: {if (m_opponent.GetMana() != 0) { AttackSpecial(m_opponent, l_time); }
								  else { Attack(m_opponent, l_time); }
								  canAttack = true; break; }

			case::Action::Heal: {if (m_opponent.GetMana() != 0) { Heal(m_opponent); }
								else { Attack(m_opponent, l_time); }
								canAttack = true; break; }
			}
		}
	}
}

void State_Game::Update(const sf::Time& l_time)
{
	if (!m_player.isAlive() || !m_opponent.isAlive()) 
	{ 
		m_gameContinue = false; 
		if (!m_player.isAlive()) { m_endText.setString("YOU LOSE"); }
		else if (!m_opponent.isAlive()) { m_endText.setString("YOU WIN"); }
		m_text2.setString("Press C to replay or SPACE to change your character");
	}
	if (m_gameContinue)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && canAttack)
		{
			Attack(m_player, l_time);
			canAttack = false;
		}
		if (m_player.GetMana() != 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && canAttack)
			{
				AttackSpecial(m_player, l_time);
				canAttack = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && canAttack)
			{
				Heal(m_player);
				canAttack = false;
			}
		}
		OpponentManagement(l_time);
		Reset(l_time);
	}
}

void State_Game::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetShared()->m_window->GetRenderedWindow();
	window->draw(m_areaSprite);
	m_player.Draw(*window);
	m_opponent.Draw(*window);
	for (int i = 0; i < 2; i++)
	{
		window->draw(m_pvContainer[i]);
		window->draw(m_pvShape[i]);
		window->draw(m_manaShape[i]);
		window->draw(m_instruction);
		window->draw(m_endText);
		window->draw(m_text2);
	}
}

