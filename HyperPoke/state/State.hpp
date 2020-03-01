#pragma once

#include "../ROM.hpp"
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
//#include "StateStack.hpp"
#include "StateIdentifiers.hpp"
/*
    Core state
    Used to control different tool menus while keeping the ROM data accessable universally

*/

class StateStack;

class State
{
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context 
    { 
        sf::RenderWindow* window;
        ROM* rom;
        Context(sf::RenderWindow& window, ROM& rom);
    };
public:
    State(StateStack& stack, Context context);
    virtual ~State();
    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;
protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStateClear();
    Context getContext() const;
private:
    StateStack* mStack;
    Context mContext;
};