#include "TextFinderState.hpp"

#include "../Common.hpp"

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

}

void TextFinderState::checkButtonAvailablity()
{
}
