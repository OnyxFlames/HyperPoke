#include "Application.hpp"

#include "Common.hpp"

Application::Application()
	:	mWindow(sf::VideoMode(720, 640), "HyperPoke", sf::Style::Close)
	,	mStateStack(State::Context(mWindow, mROM))
	,	mDefaultState(States::MenuState)
{
	registerStates();

	mStateStack.pushState(mDefaultState);
}

void Application::run()
{
	sf::Clock mClock;
	while (mWindow.isOpen())
	{
		processEvents();
		update(mClock.restart());
		render();
	}
}

void Application::setDefaultState(States::ID state)
{
	mDefaultState = state;
}

void Application::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}

}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);

	if (mStateStack.isEmpty())
		mWindow.close();
}

void Application::render()
{
	mWindow.clear(BACKGROUND_COLOR);
	mStateStack.draw();
	mWindow.display();
}

#include "state/AllStates.hpp"

void Application::registerStates()
{
	mStateStack.registerState<MenuState>(States::MenuState);
	mStateStack.registerState<MonsterEditorState>(States::MonsterEditor);
	mStateStack.registerState<TextConverterState>(States::TextConverter);
	mStateStack.registerState<TextFinderState>(States::TextFinder);
	mStateStack.registerState<StarterEditorState>(States::StarterEditor);
}
