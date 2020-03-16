#include "../Common.hpp"
#include "../GUI.hpp"
#include "../ROMViewer.hpp"
#include "StarterEditorState.hpp"

StarterEditorState::StarterEditorState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUI(*context.window)
{
	mBackground.setSize(static_cast<sf::Vector2f>(context.window->getSize()));
	mBackground.setFillColor(BACKGROUND_COLOR);

	buildGUI();
}

void StarterEditorState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackground);
	mGUI.draw();
}

bool StarterEditorState::update(sf::Time dt)
{
	mGUI.updateTime(dt);
	return false;
}

bool StarterEditorState::handleEvent(const sf::Event& event)
{
	mGUI.handleEvent(event);
	return false;
}

void StarterEditorState::buildGUI()
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

void StarterEditorState::initFunctions()
{
}

void StarterEditorState::checkButtonAvailablity()
{
}
