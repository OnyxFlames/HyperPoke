#pragma once

#include <SFML/Graphics.hpp>

#include "state/StateStack.hpp"

class Application
{
private:
	ROM mROM;
	StateStack mStateStack;
	sf::RenderWindow mWindow;
	States::ID mDefaultState;
public:
	Application();
	void run();
	void setDefaultState(States::ID state);
private:
	void processEvents();
	void update(sf::Time dt);
	void render();

	void registerStates();
};

