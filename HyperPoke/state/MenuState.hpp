#pragma once

#include "State.hpp"

#include "TGUI/TGUI.hpp"

#include <functional>

class MenuState : public State
{
private:
	std::function<void()> BrowseFiles, LoadROM, SaveROM, MakeBackup, RestoreBackup;
public:
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	tgui::Gui mGUI;
	void buildGUI();
	void initFunctions();
	void checkButtonAvailablity();

	tgui::EditBox::Ptr mRomName;
	tgui::Label::Ptr mRomNameLabel;
	tgui::Button::Ptr mMonsterEditor;
	tgui::Button::Ptr mTextConverter;
	tgui::Button::Ptr mRomSearch;

	tgui::Button::Ptr mBackupButton;
	tgui::Button::Ptr mRestoreButton;
};

