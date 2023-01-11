#include "include/GameState.hpp"
#include "include/State.hpp"
#include "include/StateStack.hpp"
#include "include/Window.hpp"
#include "logic/include/World.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>

GameState::GameState(std::weak_ptr<StateStack> state) : State(state) {
    auto window_size = Window::getWindow()->getRenderWindow()->getSize();
    mWorld = std::make_unique<Logic::World>(requestContext(), mConcreteFactory, window_size.x, window_size.y);
}

void GameState::draw() { mConcreteFactory->drawEntities(); }

bool GameState::update(double dt) {
    if (mWorld->lostGame()) {
        if (!mIdle) {
            storeContext("dead");
            requestStackPush(State::Type::Dead);
            mIdle = true;
        }
    } else if (mWorld->finishedGame()) {
        if (!mIdle) {
            storeContext("victory");
            requestStackPush(State::Type::Dead);
            mIdle = true;
        }
    } else {
        mWorld->update(dt);
    }

    return true;
}

bool GameState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed && event.type != sf::Event::KeyReleased) {
        // Fail fast principle
        return false;
    }
    if (mIdle) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter) {
                if (mWorld->finishedGame()) {
                    mIdle = false;
                } else {
                    mIdle = false;
                    mWorld->input(Logic::World::Input::Restart);
                }
            }
        }
        return false;
    }
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            requestStackPop();
            requestStackPush(State::Type::Menu);
            break;
        case sf::Keyboard::Space:
            if (!mWaitingJumpRelease) {
                mWorld->input(Logic::World::Input::JumpPressed);
                mWaitingJumpRelease = true;
            }
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            mWorld->input(Logic::World::Input::LeftPressed);
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            mWorld->input(Logic::World::Input::RightPressed);
            break;
        default:
            break;
        }
    } else {
        switch (event.key.code) {
        case sf::Keyboard::Space:
            mWaitingJumpRelease = false;
            mWorld->input(Logic::World::Input::JumpReleased);
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            mWorld->input(Logic::World::Input::LeftReleased);
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            mWorld->input(Logic::World::Input::RightReleased);
            break;
        default:
            break;
        }
    }

    return true;
}