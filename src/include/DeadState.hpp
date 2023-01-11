#ifndef VIEW_DEADSTATE_HPP
#define VIEW_DEADSTATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include <memory>

class DeadState : public State {
public:
    DeadState(std::weak_ptr<StateStack> stack);

    virtual void draw();
    virtual bool update(double dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite mOverlaySprite;
    sf::Texture mOverlayTexture;
    bool mVictory = false;
};

#endif