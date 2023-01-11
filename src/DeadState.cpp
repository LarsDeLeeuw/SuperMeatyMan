#include "include/DeadState.hpp"
#include "include/Window.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

DeadState::DeadState(std::weak_ptr<StateStack> stack) : State(stack) {
    std::string context = requestContext();
    if (context == "dead") {
        if (!mOverlayTexture.loadFromFile("../media/textures/YOU DIED.png")) {
            throw std::runtime_error("Error loading texture ../media/textures/YOU DIED.png");
        }
        mOverlaySprite.setTexture(mOverlayTexture);
    } else if (context == "victory") {
        mVictory = true;
        if (!mOverlayTexture.loadFromFile("../media/textures/VICTORY.png")) {
            throw std::runtime_error("Error loading texture ../media/textures/VICTORY.png");
        }
        mOverlaySprite.setTexture(mOverlayTexture);
    } else {
        throw std::logic_error("Unknown context in DeadState contstruction");
    }

    double window_scale = Window::getWindow()->getRenderWindow()->getSize().x / 1920.0; // Overlays are 1920x1080
    mOverlaySprite.setScale(window_scale, window_scale);
}

void DeadState::draw() {
    // Get the renderwindow
    std::shared_ptr<sf::RenderWindow> window = Window::getWindow()->getRenderWindow();

    window->setView(window->getDefaultView());
    // Draw the stuff I want to show
    window->draw(mOverlaySprite);
}

bool DeadState::update(double dt) {
    // DeadState doesn't need update method, all is handled with handleEvent.
    return true;
}

bool DeadState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Escape) {
        requestStackPop();
        if (mVictory) {
            requestStackPop();
            requestStackPush(State::Type::Menu);
        }
    }

    return true;
}