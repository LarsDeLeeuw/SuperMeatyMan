#include "include/MenuState.hpp"
#include "include/Window.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

MenuState::MenuState(std::weak_ptr<StateStack> stack) : State(stack) {
    // Construct the MenuState
    if (!mFont.loadFromFile("../media/Sansation.ttf")) {
        throw std::runtime_error("Error loading font ../media/Sansation.ttf");
    }

    const double preview_scale = 0.3;

    if (!mLevel1Texture.loadFromFile("../media/textures/Level1Preview.png")) {
        throw std::runtime_error("Error loading texture ../media/textures/Level1Preview.png");
    }
    mLevel1Sprite.setTexture(mLevel1Texture);
    mLevel1Sprite.setPosition(30.f, 60.f);
    mLevel1Sprite.setScale(preview_scale, preview_scale);

    if (!mLevel2Texture.loadFromFile("../media/textures/Level2Preview.png")) {
        throw std::runtime_error("Error loading texture ../media/textures/Level2Preview.png");
    }
    mLevel2Sprite.setTexture(mLevel2Texture);
    mLevel2Sprite.setPosition(30.f, 200.f);
    mLevel2Sprite.setScale(preview_scale, preview_scale);

    if (!mExperimentalLevelTexture.loadFromFile("../media/textures/ExperimentalLevelPreview.png")) {
        throw std::runtime_error("Error loading texture ../media/textures/ExperimentalLevelPreview.png");
    }
    mExperimentalLevelSprite.setTexture(mExperimentalLevelTexture);
    mExperimentalLevelSprite.setPosition(30.f, 340.f);
    mExperimentalLevelSprite.setScale(preview_scale, preview_scale);

    playOption.setFont(mFont);
    playOption.setString("Levels");
    playOption.setPosition(60.f, 10.f);

    exitOption.setFont(mFont);
    exitOption.setString("Press ENTER to start!\n\t Press ESC to exit.");
    exitOption.setPosition(230.f, 210.f);

    if (!mSelectionTexture.loadFromFile("../media/textures/Border.png")) {
        throw std::runtime_error("Error loading texture ../media/textures/Border.png");
    }
    mSelectionSprite.setTexture(mSelectionTexture);
    mSelectionSprite.setPosition(22.f, 54.f);
    mSelectionSprite.setScale(preview_scale + 0.02, preview_scale + 0.02);
}

void MenuState::draw() {
    // Get the renderwindow
    std::shared_ptr<sf::RenderWindow> window = Window::getWindow()->getRenderWindow();

    window->setView(window->getDefaultView());
    // Draw the stuff I want to show
    window->draw(mLevel1Sprite);
    window->draw(mLevel2Sprite);
    window->draw(mExperimentalLevelSprite);
    window->draw(mSelectionSprite);
    window->draw(playOption);
    window->draw(exitOption);
}

bool MenuState::update(double dt) {
    switch (mState % 3) {
    case 0:
        mSelectionSprite.setPosition(22.f, 54.f);
        break;
    case 1:
        mSelectionSprite.setPosition(22.f, 194.f);
        break;
    case 2:
        mSelectionSprite.setPosition(22.f, 334.f);
        break;
    }
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
    // Menu logic based on inputevents.
    // Selected level gets stored as context,
    // this context can then be used by other states (e.g. during contruction of LevelState) but is not required.
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Escape) {
        requestStackPop();
    }
    if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
        switch (mState % 3) {
        case 0:
            storeContext("../media/levels/level1.xml");
            requestStackPop();
            requestStackPush(State::Type::Level);
            break;
        case 1:
            storeContext("../media/levels/level2.xml");
            requestStackPop();
            requestStackPush(State::Type::Level);
            break;
        case 2:
            storeContext("../media/levels/level3.xml");
            requestStackPop();
            requestStackPush(State::Type::Level);
            break;
        }
    } else if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
        if (mState % 3 == 0) {
            mState += 2;
        } else {
            mState -= 1;
        }
    } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
        if (mState % 3 == 2) {
            mState -= 2;
        } else {
            mState += 1;
        }
    }

    return true;
}