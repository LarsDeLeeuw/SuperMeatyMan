#include "include/Entity.hpp"
#include "include/PhysicsHitbox.hpp"
#include <algorithm>
#include <iostream>
#include <list>

using namespace Logic;

Logic::Entity::Entity() = default;

Logic::Entity::~Entity() {
    // Send out last notification to all observers that Subject will be destructed.
    std::for_each(mObservers.begin(), mObservers.end(), [this](std::weak_ptr<Observer>& observer) {
        if (!observer.expired()) {
            observer.lock()->update();
        }
    });
}

void Logic::Entity::Notify() {
    std::for_each(mObservers.begin(), mObservers.end(), [this](std::weak_ptr<Observer>& observer) {
        if (!observer.expired()) {
            observer.lock()->update(mRelativePosition, mViewable);
        }
    });
}

void Logic::Entity::setRelativePosition(Vector2D& pos) {
    mRelativePosition.setX(pos.getX());
    mRelativePosition.setY(pos.getY());
    Notify();
}

Vector2D Entity::getPosition() { return mBody.getPosition(); }
void Entity::setPosition(Vector2D& pos) { mBody.setPosition(pos); }

const Vector2D Logic::Entity::getVelocity() { return mBody.getVelocity(); }

Logic::PhysicsHitbox Logic::Entity::getHitbox() { return mBody.getHitbox(); }

void Entity::applyCollisionResponse(Vector2D& pen) { mBody.setPosition(mBody.getPosition() - pen); }

void Entity::updatePosition(double dt) { mBody.updatePosition(dt); }

void Entity::accelerate(Vector2D grav) { mBody.accelerate(grav); }

double Entity::getElasticity() { return mElasticity; }

bool Entity::isViewable() { return mViewable; }

bool Entity::isStatic() { return mStaticBody; }

bool Entity::isCollidable() { return mCollidable; }

bool Entity::affectedByGravity() { return mGravityAffected; }

void Entity::updateViewable(bool isViewable) {
    if (mViewable != isViewable) {
        mViewable = isViewable;
        Notify();
    }
}