#pragma once

#include "State.hpp"

#include "TGUI/TGUI.hpp"

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	tgui::Gui mGUI;
	void buildGUI();
	void checkButtonAvailablity();

	tgui::EditBox::Ptr mRomName;
	tgui::Label::Ptr mRomNameLabel;
	tgui::Button::Ptr mMonsterEditor;
	tgui::Button::Ptr mTextConverter;
	tgui::Button::Ptr mRomSearch;

	tgui::Button::Ptr mBackupButton;
	tgui::Button::Ptr mRestoreButton;
};

