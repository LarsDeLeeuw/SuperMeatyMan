#ifndef VIEW_GAME_HPP
#define VIEW_GAME_HPP

#include "State.hpp"
#include "StateStack.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class StateStack;

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(double dt);
    void render();
    void registerStates();

private:
    static const double TickRate;
    std::shared_ptr<sf::RenderWindow> mWindow;
    std::shared_ptr<StateStack> mStateStack = StateStack::create();
};

#endif
