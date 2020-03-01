#include "StateStack.hpp"

#include <cassert>


StateStack::StateStack(State::Context context)
	:	mContext(context)
{
}

void StateStack::update(sf::Time dt)
{
	for (auto itr = mStack.begin(); itr != mStack.end(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (State::Ptr& state : mStack)
		state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}
	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop, States::Unknown));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear, States::Unknown));
}

bool StateStack::isEmpty()
{
	return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (auto& change : mPendingList)
	{
		switch (change.action)
		{
		case Push:	mStack.push_back(createState(change.stateID)); break;
		case Pop:	mStack.pop_back(); break;
		case Clear:	mStack.clear(); break;
		}
	}

	mPendingList.clear();
}
