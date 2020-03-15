#include "../Common.hpp"
#include "../GUI.hpp"
#include "../ROMViewer.hpp"
#include "StarterEditorState.hpp"

StarterEditorState::StarterEditorState(StateStack& stack, Context context)
	:	State(stack, context)
{
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
}

void StarterEditorState::initFunctions()
{
}

void StarterEditorState::checkButtonAvailablity()
{
}
