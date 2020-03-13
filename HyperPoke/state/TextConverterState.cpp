#include "TextConverterState.hpp"

#include "../GUI.hpp"
#include <string>
#include "../Text.hpp"
#include <sstream>
#include <iomanip>

#include "../ByteArray.hpp"

TextConverterState::TextConverterState(StateStack& stack, Context context)
	:	State(stack, context)
	,	mGUI(*context.window)
{
	// initialize what the buttons will do
	initFunctions();
	buildGUI();

	mBackground.setSize(static_cast<sf::Vector2f>(context.window->getSize()));
	mBackground.setFillColor(BACKGROUND_COLOR);
}

void TextConverterState::draw()
{
	sf::RenderWindow& mWindow(*getContext().window);
	mWindow.draw(mBackground);
	mGUI.draw();
}

bool TextConverterState::update(sf::Time dt)
{
	mGUI.updateTime(dt);
	return false;
}

bool TextConverterState::handleEvent(const sf::Event& event)
{
	mGUI.handleEvent(event);
	return false;
}

void TextConverterState::buildGUI()
{
	auto string_box = tgui::TextBox::create();
	string_box->setSize(375.f, 250.f);
	string_box->setPosition(25.f, 25.f);
	mStringBox = string_box;
	mGUI.add(string_box);

	auto hex_box = tgui::TextBox::create();
	hex_box->setSize(375.f, 250.f);
	hex_box->setPosition(
		25.f,
		hex_box->getPosition().y + string_box->getSize().y + 50.f
	);
	mHexBox = hex_box;
	mGUI.add(hex_box);

	auto convert_str_button = tgui::Button::create("Convert String");
	convert_str_button->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	convert_str_button->setPosition(
		string_box->getPosition().x + string_box->getSize().x,
		string_box->getPosition().y
		);
	convert_str_button->connect("pressed", ConvertString);

	mConvertButton = convert_str_button;

	mGUI.add(convert_str_button);

	auto convert_hex_button = tgui::Button::create("Convert Hex");
	convert_hex_button->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	convert_hex_button->setPosition(
		hex_box->getPosition().x + hex_box->getSize().x,
		convert_str_button->getPosition().y + convert_str_button->getSize().y
	);
	convert_hex_button->connect("pressed", ConvertHex);
	mGUI.add(convert_hex_button);

	auto clear_fields = tgui::Button::create("Clear Fields");
	clear_fields->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	clear_fields->setPosition(
		hex_box->getPosition().x + hex_box->getSize().x, 
		convert_hex_button->getPosition().y + convert_hex_button->getSize().y
	);
	clear_fields->connect("pressed", ClearFields);
	mGUI.add(clear_fields);

	auto string_lbl = tgui::Label::create("String:");
	string_lbl->setTextSize(21);
	mGUI.add(string_lbl);

	auto hex_lbl = tgui::Label::create("Hex:");
	hex_lbl->setTextSize(21);
	hex_lbl->setPosition(0.f, string_box->getPosition().y + string_box->getSize().y);

	mGUI.add(hex_lbl);
	auto return_button = tgui::Button::create("Menu");
	return_button->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	return_button->setPosition(
		0.f,
		getContext().window->getSize().y - return_button->getSize().y);

	return_button->connect("pressed",
	[this]()
	{
			requestStackPop();
	});

	mGUI.add(return_button);
}

void TextConverterState::initFunctions()
{
	ConvertString = [this]()
	{
		if (mStringBox->getText().getSize() > 0)
			mHexBox->setText(ByteArrayToByteString(Text<std::wstring>::encode(mStringBox->getText())));
		else
			mHexBox->setText("");
	};

	ConvertHex = [this]()
	{
		if (mHexBox->getText().getSize() > 0)
			mStringBox->setText(Text<std::wstring>::decode(ByteStringToByteArray(mHexBox->getText()).data()));
		else
			mStringBox->setText("");
	};

	ClearFields = [this]()
	{
		mStringBox->setText("");
		mHexBox->setText("");
	};
}

void TextConverterState::checkButtonAvailablity()
{
}
