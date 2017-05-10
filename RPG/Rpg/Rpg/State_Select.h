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

	void SelectContinue(EventDetails* l_details);

private:
	sf::RectangleShape m_shape;
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_text2;

	float m_time;

};
