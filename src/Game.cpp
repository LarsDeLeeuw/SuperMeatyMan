#include <chrono>
#include <memory>

#include "logic/include/Stopwatch.hpp"

#include "include/DeadState.hpp"
#include "include/Game.hpp"
#include "include/GameState.hpp"
#include "include/MenuState.hpp"
#include "include/StateStack.hpp"
#include "include/Window.hpp"

const double Game::TickRate = (1.0 / 180.0);

Game::Game() {
    mWindow = Window::getWindow()->getRenderWindow();
    registerStates();
    mStateStack->pushState(State::Type::Menu);
}

void Game::run() {
    // Main gameloop
    std::shared_ptr<Logic::Stopwatch> clock = Logic::Stopwatch::getStopwatch();

    long system_adjusted_tick = TickRate * std::chrono::steady_clock::period::den;
    while (mWindow->isOpen()) {
        while (clock->behind(system_adjusted_tick)) {
            // Update and handle events correct amount of times before rendering next frame.
            // This get's done 180 times per second and means that the game physics
            // run at the same speed on every capable system.
            processEvents();
            update(TickRate);

            if (mStateStack->isEmpty()) {
                Window::getWindow()->getRenderWindow()->close();
            }
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow->pollEvent(event)) {
        mStateStack->handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow->close();
    }
}

void Game::update(double dt) { mStateStack->update(dt); }

void Game::render() {
    mWindow->clear();
    mStateStack->draw();
    mWindow->display();
}

void Game::registerStates() {
    mStateStack->registerState<MenuState>(State::Type::Menu);
    mStateStack->registerState<GameState>(State::Type::Level);
    mStateStack->registerState<DeadState>(State::Type::Dead);
}