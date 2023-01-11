#include "include/PhysicsBody.hpp"
#include "include/PhysicsHitbox.hpp"
#include "include/Vector2D.hpp"
#include <iostream>

Logic::PhysicsBody::PhysicsBody() {
    mAcceleration = Vector2D(0.0, 0.0);
    mPositionOld = Vector2D(0.0, 0.0);
    mHitbox = PhysicsHitbox(Vector2D(0.0, 0.0), Vector2D(0.0, 0.0));
}

Logic::PhysicsBody::PhysicsBody(Vector2D pos, Vector2D acc, double width, double height) {
    mAcceleration = acc;
    mPositionOld = pos;
    mHitbox = PhysicsHitbox(pos, Vector2D(width / 2.0, height / 2.0));
}

Vector2D Logic::PhysicsBody::getPosition() { return mHitbox.getPosition(); }

const Vector2D Logic::PhysicsBody::getVelocity() { return mHitbox.getPosition() - mPositionOld; }

void Logic::PhysicsBody::setPosition(Vector2D pos) { mHitbox.setPosition(pos); }

Vector2D Logic::PhysicsBody::getAcceleration() { return mAcceleration; }

void Logic::PhysicsBody::setAcceleration(Vector2D acc) { mAcceleration = acc; }

Logic::PhysicsHitbox Logic::PhysicsBody::getHitbox() { return mHitbox; }

void Logic::PhysicsBody::updatePosition(double dt) {
    Vector2D current_position = mHitbox.getPosition();
    const Vector2D velocity = current_position - mPositionOld;
    mPositionOld = current_position;
    // Perform Verlet integration
    mHitbox.setPosition(current_position + velocity + mAcceleration * dt * dt);
    // Reset acceleration
    mAcceleration = Vector2D(0.0, 0.0);
}

void Logic::PhysicsBody::accelerate(Vector2D acc) { mAcceleration = mAcceleration + acc; }