#pragma once

#include "State.hpp"

#include "TGUI/TGUI.hpp"

class TextConverterState : public State
{
public:
	TextConverterState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	sf::RectangleShape mBackground;
private:
	tgui::Gui mGUI;
	void buildGUI();
	void checkButtonAvailablity();

	tgui::Button::Ptr mConvertButton;
	tgui::TextBox::Ptr mStringBox;
	tgui::TextBox::Ptr mHexBox;
};

