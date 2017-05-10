#pragma once
#include "BaseState.h"

class State_Intro : public BaseState
{
public:
	State_Intro(StateManager* l_stateManager);
	~State_Intro();

	void Create();
	void Destroy();

	void Update(const sf::Time& l_time);
	void Draw();

	void Continue(EventDetails* l_details);

private:
	sf::Texture m_backgroundTexture;
	sf::Sprite m_background;
	sf::Texture m_texture[2];
	sf::Sprite m_sprite[2];

	sf::Font m_font;
	sf::Text m_text;

	float m_time;
};
