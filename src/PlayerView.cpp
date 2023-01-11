#include "include/PlayerView.hpp"
#include <stdexcept>

using namespace View;

Player::Player() {
    if (!mTexture.loadFromFile("../media/textures/MeatMan.png")) {
        throw std::runtime_error("Error loading texture ../media/textures/MeatMan.png");
    }

    mSprite.setTexture(mTexture);
    // MeatMan.png is 50x50, it's position is the middle of it's hitbox, thus origin of sprite should be the middle
    mSprite.setOrigin(25, 25);
}

void Player::update(Vector2D& pos, bool viewable) {
    Entity::update(pos, viewable);

    if (pos.getX() < mPrevX) {
        if (!mLeft) {
            flip();
            mLeft = true;
        }
    } else if (pos.getX() > mPrevX) {
        if (mLeft) {
            flip();
            mLeft = false;
        }
    }
    mPrevX = pos.getX();
}