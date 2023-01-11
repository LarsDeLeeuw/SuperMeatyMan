#include "include/WallView.hpp"
#include <stdexcept>

using namespace View;

Wall::Wall(double width, double height, char variant) : Entity() {
    switch (variant) {
    case 1:
        if (!mTexture.loadFromFile("../media/textures/Stones.png")) {
            throw std::runtime_error("Error loading texture ../media/textures/Stones.png");
        }
        mSprite.setTexture(mTexture);
        mSprite.setOrigin(50, 50);
        mSprite.setScale(width / 100.0, height / 100.0);
        break;
    case 2:
        if (!mTexture.loadFromFile("../media/textures/Grass.png")) {
            throw std::runtime_error("Error loading texture ../media/textures/Grass.png");
        }
        mSprite.setTexture(mTexture);
        mSprite.setOrigin(50, 50);
        mSprite.setScale(width / 100.0, height / 100.0);
        break;
    case 10:
        if (!mTexture.loadFromFile("../media/textures/Slime.png")) {
            throw std::runtime_error("Error loading texture ../media/textures/Slime.png");
        }
        mSprite.setTexture(mTexture);
        mSprite.setOrigin(50, 50);
        mSprite.setScale(width / 100.0, height / 100.0);
        break;
    default:
        if (!mTexture.loadFromFile("../media/textures/Dirt.png")) {
            throw std::runtime_error("Error loading texture ../media/textures/Dirt.png");
        }
        mSprite.setTexture(mTexture);
        mSprite.setOrigin(50, 50);
        mSprite.setScale(width / 100.0, height / 100.0);
        break;
    }
}
