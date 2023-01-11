#include "include/PlatformEntity.hpp"
#include "include/Constants.hpp"
#include "include/Vector2D.hpp"

using namespace Logic;

PlatformEntity::PlatformEntity(Vector2D position) {
    mGravityAffected = false;
    mStaticBody = true;
    mViewable = true;
    mCollidable = true;
    mBody =
        Logic::PhysicsBody(position, Vector2D(0.0, 0.0), CONSTANT::DEFAULT_WALL_WIDTH, CONSTANT::DEFAULT_WALL_HEIGHT);
}

PlatformEntity::PlatformEntity(Vector2D position, double width, double height, double elasticity) {
    mGravityAffected = false;
    mStaticBody = true;
    mViewable = true;
    mCollidable = true;
    mElasticity = elasticity;
    mBody = Logic::PhysicsBody(position, Vector2D(0.0, 0.0), width, height);
}

Entity::Interaction PlatformEntity::interact(Entity::Interaction other) {
    if (other == Entity::None) {
        return Entity::Move;
    }
    return Entity::None;
}
