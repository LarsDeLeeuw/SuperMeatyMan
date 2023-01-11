#include "include/BGTileView.hpp"
#include <stdexcept>

using namespace View;

View::BGTile::BGTile(double width, double height) {
    if (!mTexture.loadFromFile("../media/textures/BGTile1.png")) {
        throw std::runtime_error("Error loading texture ../media/textures/BGTile1.png");
    }
    mSprite.setTexture(mTexture);
    // BGTile.png is 1920x3240, it's position is the middle of it's hitbox, thus origin of sprite should be the middle
    mSprite.setOrigin(960, 1620);
    mSprite.setScale(width / 1920.0, height / 3240.0);
}