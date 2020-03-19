#pragma once

#include <array>

#include "State.hpp"
#include "../Common.hpp"
#include "TGUI/TGUI.hpp"

#include <functional>

class MonsterEditorState : public State
{
private:
	std::function<void()> UpdateMonsterList, UpdateGenderList, WriteChanges;
public:
	MonsterEditorState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	void updateGUIValues();
	virtual bool handleEvent(const sf::Event& event);

private:
	tgui::Gui mGUI;
	void buildGUI();
	void initFunctions();
	void checkButtonAvailablity();

	int16_t mSelectedIndex = 0, mPrevSelectedIndex = -1;
	tgui::ComboBox::Ptr mMonsterList;
	tgui::EditBox::Ptr mMonsterName;
	std::array<tgui::EditBox::Ptr, 6> mBaseStats;
	tgui::ComboBox::Ptr mType1, mType2;
	std::array<tgui::EditBox::Ptr, 6> mEffortValues;
	tgui::EditBox::Ptr mCatchRate;
	tgui::EditBox::Ptr mExpYield;
	tgui::ComboBox::Ptr mItem1, mItem2;
	tgui::ComboBox::Ptr mGender;
	tgui::EditBox::Ptr mGenderRatio;
	tgui::ComboBox::Ptr mGrowthRate;

	tgui::ComboBox::Ptr mEggGroup1, mEggGroup2;

	sf::RectangleShape mBackground;
};

