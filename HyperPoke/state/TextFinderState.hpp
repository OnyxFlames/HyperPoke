#pragma once

#include "State.hpp"

#include "TGUI/TGUI.hpp"

class TextFinderState : public State
{
public:
	TextFinderState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	sf::RectangleShape mBackground;
private:
	tgui::Gui mGUI;
	void buildGUI();
	void checkButtonAvailablity();

};

