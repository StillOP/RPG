#pragma once
#include "BaseState.h"

class State_Select : public BaseState
{
public:
	State_Select(StateManager* l_stateManager);
	~State_Select();

	void Create();
	void Destroy();

	void Update(const sf::Time& l_time);
	void Draw();

	int GetIndex();

	void SelectContinue(EventDetails* l_details);
	
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture[4];
	sf::CircleShape m_arrow[2];

	sf::Sprite m_background;
	sf::Texture m_backgroundTexture;

	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_text2;
	int m_index;

	float m_time;

};
