#include "include/BGTileEntity.hpp"
#include "include/Vector2D.hpp"

using namespace Logic;

BGTileEntity::BGTileEntity(Vector2D position, double width, double height) {
    mGravityAffected = false;
    mStaticBody = true;
    mViewable = true;
    mCollidable = false;

    mBody = Logic::PhysicsBody(position, Vector2D(0.0, 0.0), width, height);
}

Entity::Interaction BGTileEntity::interact(Entity::Interaction other) {
    if (other == Entity::None) {
        return Entity::Move;
    }
    return Entity::None;
}
