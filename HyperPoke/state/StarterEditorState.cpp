#include "../Common.hpp"
#include "../GUI.hpp"
#include "../ROMViewer.hpp"
#include "StarterEditorState.hpp"

StarterEditorState::StarterEditorState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUI(*context.window)
{
	buildGUI();
}

void StarterEditorState::draw()
{
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
