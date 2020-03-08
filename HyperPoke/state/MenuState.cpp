#include "MenuState.hpp"

#include "../GUI.hpp"
#include "TGUI/TGUI.hpp"

#include "../FilePrompt.hpp"

#include <filesystem>

namespace fs = std::experimental::filesystem;

MenuState::MenuState(StateStack& stack, Context context)
	:	State(stack, context)
	,	mGUI(*context.window)
{
	buildGUI();
}

void MenuState::draw()
{
	mGUI.draw();
}

bool MenuState::update(sf::Time dt)
{
	mGUI.updateTime(dt);

	checkButtonAvailablity();

	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUI.handleEvent(event);

	if (event.type == sf::Event::Resized)
	{
		mGUI.removeAllWidgets();
		buildGUI();
	}

	return false;
}

#include <Windows.h>

void MenuState::buildGUI()
{

	const auto context = getContext();
	const auto bounds = context.window->getSize();

	auto browsebutton = tgui::Button::create("Browse");
	browsebutton->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	browsebutton->setPosition(0, bounds.y - ((browsebutton->getSize().y * 2) + EDITBOX_HEIGHT));
	browsebutton->connect
	("pressed", [this]()
		{
			mRomName->setText(FilePrompt::getFilePrompt("Select a ROM", ""));
			mRomNameLabel->setText("ROM: None");
		});
	mGUI.add(browsebutton);

	auto loadbutton = tgui::Button::create("Load ROM");
	loadbutton->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	loadbutton->setPosition(BUTTON_WIDTH * 0.f, bounds.y - loadbutton->getSize().y);
	loadbutton->connect
	("pressed", [this, context]()
		{
			if (context.rom->loadFromFile(mRomName->getText()))
			{
				mRomNameLabel->setText("ROM: " + to_string(context.rom->getType()));
			}
		});
	mGUI.add(loadbutton);

	auto savebutton = tgui::Button::create("Save ROM");
	savebutton->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	savebutton->setPosition(BUTTON_WIDTH * 1.f, bounds.y - (savebutton->getSize().y));
	savebutton->connect
	("pressed", [this, context]()
		{
			const std::string file = mRomName->getText();

			if (context.rom->data.size() > 0)
			{
				context.rom->writeToFile(mRomName->getText());
				mRomNameLabel->setText("Saved to file: " + fs::path(file).filename().string());
			}
		});
	mGUI.add(savebutton);

	auto backup = tgui::Button::create("Make Backup");
	backup->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	backup->setPosition(BUTTON_WIDTH * 2.f, bounds.y - (backup->getSize().y));
	backup->connect("pressed",
		[this]()
		{
			const std::string file = mRomName->getText().toAnsiString();

			if (fs::exists(file + ".bak"))
				fs::remove(file + ".bak");

			fs::copy_file(
				file,
				file + ".bak");

			mRomNameLabel->setText("Created: " + fs::path(file + ".bak").filename().string());
		});
	backup->setEnabled(false);
	mBackupButton = backup;
	mGUI.add(backup);

	auto restore = tgui::Button::create("Restore Backup");
	restore->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	restore->setPosition(BUTTON_WIDTH * 3.f, bounds.y - backup->getSize().y);
	restore->connect("pressed",
		[this]()
		{
			const std::string backup = mRomName->getText().toAnsiString();
			const std::string file = mRomName->getText().toAnsiString().substr(0, backup.size() - 4);

			if (fs::exists(file))
				fs::remove(file);

			fs::copy_file(
				backup,
				file);

			mRomNameLabel->setText("Restored: " + fs::path(file).filename().string());
		});
	mRestoreButton = restore;
	restore->setEnabled(false);
	mGUI.add(restore);

	auto name = tgui::EditBox::create();
	name->setSize(bounds.x, EDITBOX_HEIGHT);
	name->setPosition(0, bounds.y - (savebutton->getSize().y + name->getSize().y));

	mRomName = name;
	mGUI.add(name);

	auto romnamelabel = tgui::Label::create("ROM: None");
	romnamelabel->setTextSize(18);
	romnamelabel->setPosition(browsebutton->getPosition().x + BUTTON_WIDTH, browsebutton->getPosition().y + (BUTTON_HEIGHT * 0.55f));
	mRomNameLabel = romnamelabel;
	mGUI.add(romnamelabel);

	// initally disabled buttons
	auto monstereditor = tgui::Button::create("Edit Pokemon");
	monstereditor->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	monstereditor->setPosition(0, romnamelabel->getSize().y);
	monstereditor->connect("pressed",
		[this]()
		{
			requestStackPush(States::MonsterEditor);
		});

	mMonsterEditor = monstereditor;
	mGUI.add(monstereditor);

	auto text_converter = tgui::Button::create("Text-Hex\nConverter");
	text_converter->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	text_converter->setPosition(monstereditor->getSize().x, romnamelabel->getSize().y);
	text_converter->connect("pressed",
		[this]()
		{
			requestStackPush(States::TextConverter);
		});
	mTextConverter = text_converter;

	mGUI.add(text_converter);

	auto text_search = tgui::Button::create("ROM Search");
	text_search->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	text_search->setPosition(0.f, monstereditor->getSize().y + 25.f);
	mRomSearch = text_search;
	text_search->connect("pressed",
		[this]()
		{
			requestStackPush(States::TextFinder);
		});
	mGUI.add(text_search);

	auto exit_btn = tgui::Button::create("Exit Application");
	exit_btn->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	exit_btn->setPosition(
		bounds.x - exit_btn->getSize().x,
		bounds.y - exit_btn->getSize().y);
	exit_btn->connect("pressed",
		[this]()
		{
			requestStackPop();
		});
	mGUI.add(exit_btn);
}

void MenuState::checkButtonAvailablity()
{
	if (mRomName->getText() != "")
	{
		if (fs::path(mRomName->getText().toAnsiString()).extension() == ".bak")
			mRestoreButton->setEnabled(true);
		else
			mRestoreButton->setEnabled(false);

		if (fs::path(mRomName->getText().toAnsiString()).extension() == ".gba")
			mBackupButton->setEnabled(true);
		else
			mBackupButton->setEnabled(false);
	}

	if (getContext().rom->getType() != ROMType::UNKNOWN_ROM)
	{
		mMonsterEditor->setEnabled(true);
		mRomSearch->setEnabled(true);
	}
	else
	{
		mMonsterEditor->setEnabled(false);
		mRomSearch->setEnabled(false);
	}

}
