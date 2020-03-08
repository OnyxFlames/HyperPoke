#pragma once

#include "State.hpp"

#include "TGUI/TGUI.hpp"


#include <functional>

class TextConverterState : public State
{
private:
	std::function<void()> ConvertString, ConvertHex, ClearFields;
public:
	TextConverterState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	sf::RectangleShape mBackground;
private:
	tgui::Gui mGUI;
	void buildGUI();
	void initFunctions();
	void checkButtonAvailablity();

	tgui::Button::Ptr mConvertButton;
	tgui::TextBox::Ptr mStringBox;
	tgui::TextBox::Ptr mHexBox;
};

