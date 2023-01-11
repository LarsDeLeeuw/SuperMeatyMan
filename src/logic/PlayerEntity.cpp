#include "include/PlayerEntity.hpp"
#include "include/Constants.hpp"
#include "include/PhysicsBody.hpp"

using namespace Logic;

PlayerEntity::PlayerEntity(Vector2D position, Vector2D acceleration) {
    mGravityAffected = true;
    mStaticBody = false;
    mViewable = true;
    mCollidable = true;
    mBody = PhysicsBody(position, acceleration, CONSTANT::PLAYER_WIDTH, CONSTANT::PLAYER_HEIGHT);
}

Entity::Interaction PlayerEntity::interact(Entity::Interaction other) { return other; }

bool PlayerEntity::getAlive() { return mIsAlive; }
void PlayerEntity::setAlive(bool state) { mIsAlive = state; }