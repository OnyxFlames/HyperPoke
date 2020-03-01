#pragma once

#include <SFML/Graphics.hpp>

#include "state/StateStack.hpp"

class Application
{
private:
	ROM mROM;
	StateStack mStateStack;
	sf::RenderWindow mWindow;
public:
	Application();
	void run();

private:
	void processEvents();
	void update(sf::Time dt);
	void render();

	void registerStates();
};

