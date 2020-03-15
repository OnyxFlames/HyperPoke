#pragma once

#include "State.hpp"

#include "TGUI/TGUI.hpp"

#include <functional>

class StarterEditorState : public State
{
private:
	std::function<void()> WriteStarterData;
public:
	StarterEditorState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	sf::RectangleShape mBackground;
private:
	tgui::Gui mGUI;
	void buildGUI();
	void initFunctions();
	void checkButtonAvailablity();

	tgui::ListBox::Ptr mFirstMonster, mSecondMonster, mThirdMonster, mOpponent;

};

