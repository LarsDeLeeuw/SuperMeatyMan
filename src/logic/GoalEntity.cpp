#include "include/GoalEntity.hpp"
#include "include/Constants.hpp"
#include "include/Vector2D.hpp"

using namespace Logic;

GoalEntity::GoalEntity(Vector2D position) {
    mGravityAffected = false;
    mStaticBody = true;
    mViewable = true;
    mCollidable = true;
    mBody = Logic::PhysicsBody(position, Vector2D(0.0, 0.0), CONSTANT::GOAL_WIDTH, CONSTANT::GOAL_HEIGHT);
}

Entity::Interaction GoalEntity::interact(Entity::Interaction other) {
    if (other == Entity::None) {
        return Entity::Finish;
    }
    return Entity::None;
}
