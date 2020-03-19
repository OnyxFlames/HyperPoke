#include "MenuState.hpp"

#include "TGUI/TGUI.hpp"
#include "MonsterEditorState.hpp"

#include "../monster/Monster.hpp"

#include "../Text.hpp"
#include "../GUI.hpp"

#include "../ROMViewer.hpp"

#include "../Memory.hpp"

MonsterEditorState::MonsterEditorState(StateStack& stack, Context context)
	:	State(stack, context)
	,	mGUI(*context.window)
{
	initFunctions();
	buildGUI();

	mBackground.setFillColor(BACKGROUND_COLOR);
	mBackground.setSize(static_cast<sf::Vector2f>(context.window->getSize()));


	auto data = context.rom->data.data();

}

void MonsterEditorState::draw()
{
	sf::RenderWindow& mWindow = *getContext().window;
	mWindow.draw(mBackground);
	mGUI.draw();
}

bool MonsterEditorState::update(sf::Time dt)
{
	mGUI.updateTime(dt);

	if (mSelectedIndex != mPrevSelectedIndex)
		updateGUIValues();

	return false;
}

void MonsterEditorState::updateGUIValues()
{
	ROMViewer rv(*getContext().rom);
	OffsetTable table(getContext().rom->getType());
	uint8_t* data = getContext().rom->data.data();
	MonsterBaseStats basestats = rv.readMonsterStats(mSelectedIndex);

	mBaseStats[0]->setText(std::to_string(basestats.base_HP));
	mBaseStats[1]->setText(std::to_string(basestats.base_attack));
	mBaseStats[2]->setText(std::to_string(basestats.base_defense));
	mBaseStats[3]->setText(std::to_string(basestats.base_spattack));
	mBaseStats[4]->setText(std::to_string(basestats.base_spdefense));
	mBaseStats[5]->setText(std::to_string(basestats.base_speed));

	mType1->setSelectedItemByIndex(basestats.type1);
	mType2->setSelectedItemByIndex(basestats.type2);


	mEffortValues[0]->setText(std::to_string(basestats.effort_yield.HP));
	mEffortValues[1]->setText(std::to_string(basestats.effort_yield.Attack));
	mEffortValues[2]->setText(std::to_string(basestats.effort_yield.Defense));
	mEffortValues[3]->setText(std::to_string(basestats.effort_yield.SpAttack));
	mEffortValues[4]->setText(std::to_string(basestats.effort_yield.SpDefense));
	mEffortValues[5]->setText(std::to_string(basestats.effort_yield.Speed));

	mCatchRate->setText(std::to_string(basestats.catch_rate));
	mExpYield->setText(std::to_string(basestats.base_xp_yield));

	mItem1->setSelectedItemByIndex(basestats.item1);
	mItem2->setSelectedItemByIndex(basestats.item2);

	if (decodeGender(basestats.gender) == MonsterGender::MixedGender)
	{
		mGenderRatio->setEnabled(true);
		mGender->setSelectedItemByIndex(decodeGender(basestats.gender));
	}
	else
	{
		mGender->setSelectedItemByIndex(decodeGender(basestats.gender));
		mGenderRatio->setEnabled(false);
	}
	mGenderRatio->setText(std::to_string(basestats.gender));

	mGrowthRate->setSelectedItemByIndex(basestats.levelup_type);

	mEggGroup1->setSelectedItemByIndex(basestats.egg_group1);
	mEggGroup2->setSelectedItemByIndex(basestats.egg_group2);

	mPrevSelectedIndex = mSelectedIndex;
}

bool MonsterEditorState::handleEvent(const sf::Event& event)
{
	mGUI.handleEvent(event);
	return false;
}
// TODO: Move into separate GUI building functions, or make positions/sizes based off of config file
void MonsterEditorState::buildGUI()
{
	auto monsterlist = tgui::ComboBox::create();
	monsterlist->setSize(DROPDOWN_WIDTH, DROPDOWN_HEIGHT);
	monsterlist->setPosition(25.f, 25.f);
	monsterlist->setItemsToDisplay(25);
	monsterlist->connect("ItemSelected", UpdateMonsterList);
	mMonsterList = monsterlist;
	mGUI.add(monsterlist);

	auto monstername = tgui::EditBox::create();
	monstername->setSize(EDITBOX_WIDTH, DROPDOWN_HEIGHT);
	monstername->setPosition(monsterlist->getSize().x + 25.f, 25.f);
	mMonsterName = monstername;
	mGUI.add(monstername);

	const std::string label_names[] =
	{
		"HP",
		"Atk",
		"Def",
		"Sp.Atk",
		"Sp.Def",
		"Speed",
	};

	for (size_t i = 0; i < 6; ++i)
	{
		auto label = tgui::Label::create("Base " + label_names[i] + ":");
		label->setPosition(monsterlist->getPosition().x, monstername->getPosition().y + (label->getSize().y * (i + 1) * 1.1f));
		mGUI.add(label);
	
		auto basestat = tgui::EditBox::create();
		basestat->setSize(50.f, 18.f);
		basestat->setPosition(monstername->getPosition().x, monstername->getPosition().y + (label->getSize().y * (i + 1) * 1.1f));

		mBaseStats[i] = basestat;

		mGUI.add(basestat);
	}

	ROM& rom = *getContext().rom;
	sf::RenderWindow& window = *getContext().window;

	OffsetTable table(rom.getType());

	std::vector<uint8_t>& data = rom.data;

	ROMViewer rv(rom);

	for (size_t i = 0; i < MONSTER_COUNT; ++i)
	{
		mMonsterList->addItem(rv.readMonsterName(i));
	}

	mMonsterList->setSelectedItemByIndex(mSelectedIndex);

	const float TYPE_OFFSETY = 25.f;

	auto type1_lbl = tgui::Label::create("Type 1:");
	type1_lbl->setPosition(monsterlist->getPosition().x, mBaseStats.back()->getPosition().y + TYPE_OFFSETY);
	mGUI.add(type1_lbl);

	auto type1_list = tgui::ComboBox::create();
	type1_list->setPosition(monstername->getPosition().x, mBaseStats.back()->getPosition().y + TYPE_OFFSETY);
	type1_list->setSize(80.f, DROPDOWN_HEIGHT);

	for (size_t i = 0; i < TYPE_COUNT; ++i)
		type1_list->addItem(rv.readTypeName(i));

	mType1 = type1_list;
	mGUI.add(type1_list);

	auto type2_lbl = tgui::Label::create("Type 2:");
	type2_lbl->setPosition(monsterlist->getPosition().x, mBaseStats.back()->getPosition().y + TYPE_OFFSETY + type1_lbl->getSize().y);
	mGUI.add(type2_lbl);

	auto type2_list = tgui::ComboBox::create();
	type2_list->setPosition(monstername->getPosition().x, mBaseStats.back()->getPosition().y + TYPE_OFFSETY + mType1->getSize().y);
	type2_list->setSize(80.f, DROPDOWN_HEIGHT);

	for (size_t i = 0; i < TYPE_COUNT; ++i)
		type2_list->addItem(rv.readTypeName(i));

	mType2 = type2_list;
	mGUI.add(type2_list);

	for (size_t i = 0; i < 6; ++i)
	{
		auto lbl_effort = tgui::Label::create(label_names[i] + " Effort:");
		const auto size = lbl_effort->getSize().y;
		lbl_effort->setPosition(mMonsterList->getPosition().x, mType2->getPosition().y + TYPE_OFFSETY + (size * (i)) + (1.1f * i));
	
		mGUI.add(lbl_effort);

		auto txt_effort = tgui::EditBox::create();
		txt_effort->setSize(50.f, 18.f);
		txt_effort->setPosition(mMonsterName->getPosition().x, mType2->getPosition().y + TYPE_OFFSETY + (size * (i)) + (1.1f * i));
		mEffortValues[i] = txt_effort;
		mGUI.add(txt_effort);
	}


	auto catchratelbl = tgui::Label::create("Catch Rate:");
	catchratelbl->setPosition(mMonsterList->getPosition().x, mEffortValues.back()->getPosition().y + TYPE_OFFSETY);
	mGUI.add(catchratelbl);

	auto catchratetxt = tgui::EditBox::create();
	catchratetxt->setSize(50.f, 18.f);
	catchratetxt->setPosition(mMonsterName->getPosition().x, catchratelbl->getPosition().y);
	mCatchRate = catchratetxt;
	mGUI.add(catchratetxt);

	auto basexplbl = tgui::Label::create("Base XP Yield:");
	basexplbl->setPosition(catchratelbl->getPosition().x, catchratelbl->getPosition().y + catchratelbl->getSize().y);

	mGUI.add(basexplbl);

	auto basexptxt = tgui::EditBox::create();
	basexptxt->setSize(50.f, 18.f);
	basexptxt->setPosition(catchratetxt->getPosition().x, catchratetxt->getPosition().y + catchratetxt->getSize().y);
	mExpYield = basexptxt;
	mGUI.add(basexptxt);

	auto item1lbl = tgui::Label::create("Item 1:");
	item1lbl->setPosition(mBaseStats[0]->getPosition().x + 100.f, mBaseStats[0]->getPosition().y);
	mGUI.add(item1lbl);

	auto item2lbl = tgui::Label::create("Item 2:");
	item2lbl->setPosition(mBaseStats[1]->getPosition().x + 100.f, mBaseStats[1]->getPosition().y);
	mGUI.add(item2lbl);

	const auto romType = getContext().rom->getType();

	auto item1drp = tgui::ComboBox::create();
	item1drp->setPosition(
		item1lbl->getPosition().x + item1lbl->getSize().x,
		item1lbl->getPosition().y);
	item1drp->setSize(125.f, 18.f);
	item1drp->setItemsToDisplay(20);
	for (size_t i = 0; 
		(isFRLGBase(romType) ? i < ITEM_COUNT_FRLG : i < ITEM_COUNT_RSE); ++i)
		item1drp->addItem(rv.readItemName(i));
	mItem1 = item1drp;
	mGUI.add(item1drp);

	auto item2drp = tgui::ComboBox::create();
	item2drp->setPosition(
		item2lbl->getPosition().x + item2lbl->getSize().x,
		item2lbl->getPosition().y);
	item2drp->setSize(125.f, 18.f);
	item2drp->setItemsToDisplay(20);

	for (size_t i = 0; 
		(isFRLGBase(romType) ? i < ITEM_COUNT_FRLG : i < ITEM_COUNT_RSE); ++i)
		item2drp->addItem(rv.readItemName(i));
	mItem2 = item2drp;
	mGUI.add(item2drp);

	auto lblgender = tgui::Label::create("Gender:");
	lblgender->setPosition(item2lbl->getPosition().x, item2lbl->getPosition().y + (item2lbl->getSize().y * 2.f));

	mGUI.add(lblgender);

	auto cbogender = tgui::ComboBox::create();
	cbogender->setPosition(
		lblgender->getPosition().x + lblgender->getSize().x,
		lblgender->getPosition().y);
	cbogender->setSize(80.f, 18.f);
	cbogender->connect("itemselected", UpdateGenderList);
	for (size_t i = 0; i < MonsterGender::GenderCount; ++i)
		cbogender->addItem(to_string(static_cast<MonsterGender>(i)));
	mGender = cbogender;
	mGUI.add(cbogender);

	auto txtgender = tgui::EditBox::create();
	txtgender->setPosition(
		cbogender->getPosition().x + cbogender->getSize().x + 4.f,
		cbogender->getPosition().y);
	txtgender->setSize(36.f, 18.f);
	mGenderRatio = txtgender;
	mGUI.add(txtgender);

	const char* growth_rates[]
	{
		"Medium Fast (1,000,000)",
		"Erratic (600,000)",
		"Flucuating (1,640,000)",
		"Medium Slow (1,059,860)",
		"Fast (800,000)",
		"Slow (1,250,000)"
	};

	auto growth_rate_lbl = tgui::Label::create("XP Rate: ");
	growth_rate_lbl->setPosition(lblgender->getPosition().x, lblgender->getPosition().y + growth_rate_lbl->getSize().y);

	mGUI.add(growth_rate_lbl);

	auto growth_rate_cbo = tgui::ComboBox::create();
	growth_rate_cbo->setPosition(growth_rate_lbl->getPosition().x + growth_rate_lbl->getSize().x, growth_rate_lbl->getPosition().y);
	growth_rate_cbo->setSize(180.f, 18.f);
	mGrowthRate = growth_rate_cbo;
	for (size_t i = 0; i < 6; ++i) growth_rate_cbo->addItem(growth_rates[i]);
	mGUI.add(growth_rate_cbo);

	auto egg_group_lbl = tgui::Label::create("Egg Group 1: ");
	egg_group_lbl->setPosition(growth_rate_lbl->getPosition().x, growth_rate_lbl->getPosition().y + egg_group_lbl->getSize().y);
	mGUI.add(egg_group_lbl);

	auto egg_group_lbl2 = tgui::Label::create("Egg Group 2: ");
	egg_group_lbl2->setPosition(growth_rate_lbl->getPosition().x, growth_rate_lbl->getPosition().y + egg_group_lbl->getSize().y * 2);
	mGUI.add(egg_group_lbl2);

	auto egg_group_cbo1 = tgui::ComboBox::create();
	egg_group_cbo1->setPosition(egg_group_lbl->getPosition().x + egg_group_lbl->getSize().x, egg_group_lbl->getPosition().y);
	mEggGroup1 = egg_group_cbo1;
	auto egg_group_cbo2 = tgui::ComboBox::create();
	egg_group_cbo2->setPosition(egg_group_lbl2->getPosition().x + egg_group_lbl2->getSize().x, egg_group_lbl2->getPosition().y);
	mEggGroup2 = egg_group_cbo2;
	mGUI.add(egg_group_cbo1);
	mGUI.add(egg_group_cbo2);

	for (size_t i = 0; i < 16; ++i)
	{
		mEggGroup1->addItem(toMonsterEggGroup((uint8_t)i));
		mEggGroup2->addItem(toMonsterEggGroup((uint8_t)i));
	}

	auto return_btn = tgui::Button::create("Menu");
	return_btn->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	return_btn->setPosition(0.f, window.getSize().y - return_btn->getSize().y);

	return_btn->connect("pressed",
		[this]()
		{
			requestStackPop();
		});

	mGUI.add(return_btn);

	auto write_changes = tgui::Button::create("Write Changes");
	write_changes->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	write_changes->setPosition(BUTTON_WIDTH, window.getSize().y - BUTTON_HEIGHT);
	write_changes->connect("pressed", WriteChanges);
		
	mGUI.add(write_changes);
}

void MonsterEditorState::initFunctions()
{
	UpdateMonsterList = [this]()
	{
		mMonsterName->setText(mMonsterList->getSelectedItem());
		mSelectedIndex = mMonsterList->getSelectedItemIndex();
	};

	UpdateGenderList = [this]()
	{
		if (mGender->getSelectedItemIndex() == MonsterGender::MixedGender)
			mGenderRatio->setEnabled(true);
		else
			mGenderRatio->setEnabled(false);
	};

	WriteChanges = [this]()
	{
		ROMViewer rv(*getContext().rom);
		// Name
		if (mMonsterName->getText() != mMonsterList->getSelectedItem()
			&& rv.writeMonsterName(mSelectedIndex, mMonsterName->getText()))
			mMonsterList->changeItemByIndex(mSelectedIndex, mMonsterName->getText());

#define valueOf(x)		(static_cast<uint8_t>(std::stoi(x->getText().toAnsiString())))
#define valueAs(x, t)	(static_cast<t>(std::stoi(x->getText().toAnsiString())))
#define indexOf(x)		(static_cast<uint8_t>(x->getSelectedItemIndex()))
#define indexAs(x, t)	(static_cast<t>(x->getSelectedItemIndex()))

		// load initial data first, this is because MonsterBaseStats does not have a default constructor
		MonsterBaseStats stats(rv.readMonsterStats(mSelectedIndex));
		// Note: The order is due to the menu not lining up with the way the values are stored
		stats.base_HP = valueOf(mBaseStats[0]);
		stats.base_attack = valueOf(mBaseStats[1]);
		stats.base_defense = valueOf(mBaseStats[2]);
		stats.base_spattack = valueOf(mBaseStats[3]);
		stats.base_spdefense = valueOf(mBaseStats[4]);
		stats.base_speed = valueOf(mBaseStats[5]);

		stats.type1 = indexOf(mType1);
		stats.type2 = indexOf(mType2);

		stats.effort_yield.HP = valueOf(mEffortValues[0]);
		stats.effort_yield.Attack = valueOf(mEffortValues[1]);
		stats.effort_yield.Defense = valueOf(mEffortValues[2]);
		stats.effort_yield.SpAttack = valueOf(mEffortValues[3]);
		stats.effort_yield.SpDefense = valueOf(mEffortValues[4]);
		stats.effort_yield.Speed = valueOf(mEffortValues[5]);

		stats.catch_rate = valueOf(mCatchRate);
		stats.base_xp_yield = valueOf(mExpYield);

		stats.item1 = indexAs(mItem1, uint16_t);
		stats.item2 = indexAs(mItem2, uint16_t);

		switch (indexOf(mGender))
		{
		case MonsterGender::MixedGender:
			// use written value or set to Mixed default
			stats.gender = decodeGender(valueOf(mGenderRatio)) != MonsterGender::MixedGender
				? 127 : valueOf(mGenderRatio);
			break;
		case MonsterGender::AlwaysMale: stats.gender = 0; break;
		case MonsterGender::AlwaysFemale: stats.gender = 254; break;
		case MonsterGender::Genderless: stats.gender = 255; break;
		default: printf("Invalid gender value\n");
		}

		stats.levelup_type = indexOf(mGrowthRate);
		stats.egg_group1 = indexOf(mEggGroup1);
		stats.egg_group2 = indexOf(mEggGroup2);

		if (rv.writeMonsterStats(mSelectedIndex, stats))
			updateGUIValues();


	};
}

void MonsterEditorState::checkButtonAvailablity()
{
}
