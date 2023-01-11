#ifndef VIEW_MENUSTATE_HPP
#define VIEW_MENUSTATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include <memory>

class MenuState : public State {
public:
    MenuState(std::weak_ptr<StateStack> stack);

    virtual void draw();
    virtual bool update(double dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    bool play = true;
    unsigned int mState = 0;
    sf::Font mFont;
    sf::Text playOption;
    sf::Text exitOption;
    sf::Sprite mSelectionSprite;
    sf::Texture mSelectionTexture;
    sf::Sprite mLevel1Sprite;
    sf::Texture mLevel1Texture;
    sf::Sprite mLevel2Sprite;
    sf::Texture mLevel2Texture;
    sf::Sprite mExperimentalLevelSprite;
    sf::Texture mExperimentalLevelTexture;
};

#endif