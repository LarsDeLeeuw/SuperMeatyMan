#include "include/EntityView.hpp"
#include "include/Window.hpp"

using namespace View;

Entity::Entity() = default;

Entity::~Entity() = default;

void Entity::update() { waitingForDelete = true; }

void Entity::update(Vector2D& pos, bool viewable) {
    mSprite.setPosition(pos.getX(), pos.getY());
    mViewable = viewable;
}

void Entity::flip() { mSprite.scale(-1.0, 1.0); }

void Entity::setScale(double scale) { mSprite.scale(scale, scale); }

void Entity::draw() { Window::getWindow()->getRenderWindow()->draw(mSprite); }

bool Entity::isViewable() { return mViewable; }

bool Entity::active() { return !waitingForDelete; }
