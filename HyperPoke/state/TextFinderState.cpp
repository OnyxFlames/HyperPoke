#include "TextFinderState.hpp"

#include "../Common.hpp"

#include "../GUI.hpp"

#include "../ROMViewer.hpp"

TextFinderState::TextFinderState(StateStack& stack, Context context)
	:	State(stack, context)
	,	mGUI(*context.window)
{
	mBackground.setSize(static_cast<sf::Vector2f>(context.window->getSize()));
	mBackground.setFillColor(BACKGROUND_COLOR);

	buildGUI();

}

void TextFinderState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackground);
	mGUI.draw();
}

bool TextFinderState::update(sf::Time dt)
{
	mGUI.updateTime(dt);

	return true;
}

bool TextFinderState::handleEvent(const sf::Event& event)
{
	mGUI.handleEvent(event);

	return false;
}

void TextFinderState::buildGUI()
{
	const auto bounds = getContext().window->getSize();




	auto return_btn = tgui::Button::create("Menu");
	return_btn->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	return_btn->setPosition(0.f, bounds.y - BUTTON_HEIGHT);
	return_btn->connect("pressed",
		[this]()
		{
			requestStackPop();
		});
	mGUI.add(return_btn);
}

void TextFinderState::checkButtonAvailablity()
{
}
