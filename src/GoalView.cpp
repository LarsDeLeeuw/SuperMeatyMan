#include "include/GoalView.hpp"
#include <stdexcept>

using namespace View;

View::Goal::Goal() {
    if (!mTexture.loadFromFile("../media/textures/Portal.png")) {
        throw std::runtime_error("Error loading texture ../media/textures/Portal.png");
    }

    mSprite.setTexture(mTexture);
    // Portal.png is 100x100, it's position is the middle of it's hitbox, thus origin of sprite should be the middle
    mSprite.setOrigin(50, 50);
}