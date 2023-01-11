#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "include/Constants.hpp"
#include "include/LevelLoader.hpp"
#include "include/World.hpp"

using namespace Logic;

const double World::TERMINAL_VELOCITY_X = 1.0;
const double World::MOVEMENT_SPEED = 200.0;
const double World::TERMINAL_VELOCITY_Y = 1.0;
const double World::JUMP_FORCE = 0.9;
const double World::WALLJUMP_FORCE = 0.8;
const double World::FRICTION = -1000.0;
const double World::GRAVITY = 100.0;

Logic::World::World(std::string levelname, std::shared_ptr<EntityFactory> factory, double window_width,
                    double window_height) {
    factory->setViewScale(window_width);
    mGravity = Vector2D(0.0, -GRAVITY);
    mCurrentLevel = levelname;
    mEntityFactory = factory;
    LevelLoader loader = LevelLoader(levelname, factory);
    mViewScale = factory->getViewScale();
    loader.getEntities(mEntities);
    mNextLevel = loader.getNextLevel();
    auto CamSettings = loader.getCameraSettings();
    mCamera.setResolution(std::get<0>(CamSettings));
    mCamera.setVelocity(std::get<1>(CamSettings));
    mCamera.setMaxY(std::get<2>(CamSettings));
}

Logic::World::~World() = default;

void Logic::World::update(double dt) {
    applyConstraints();
    solveCollisions();
    handleInput();
    updatePositions(dt);
    calculateViewable();
    if (mLevelComplete)
        loadLevel();
}

void Logic::World::input(Logic::World::Input event) {
    // Method with which World can recieve one of it's own defined events from outside of Logic library.
    switch (event) {
    case Logic::World::LeftPressed:
        mIsMovingLeft = true;
        break;
    case Logic::World::LeftReleased:
        mIsMovingLeft = false;
        break;
    case Logic::World::RightPressed:
        mIsMovingRight = true;
        break;
    case Logic::World::RightReleased:
        mIsMovingRight = false;
        break;
    case Logic::World::JumpPressed:
        mIsJumping = true;
        break;
    case Logic::World::JumpReleased:
        mIsJumping = false;
        break;
    case Logic::World::Restart:
        loadLevel();
        break;
    }
}

void Logic::World::handleInput() {
    if (mIsMovingRight && (!mIsOnRightWall)) {
        Vector2D player_velocity = mEntities[0]->getVelocity();
        if (player_velocity.getX() < TERMINAL_VELOCITY_X) {
            mEntities[0]->accelerate(Vector2D(World::MOVEMENT_SPEED, 0.0));
        }
    }

    if (mIsMovingLeft && (!mIsOnLeftWall)) {
        Vector2D player_velocity = mEntities[0]->getVelocity();
        if (player_velocity.getX() > -1 * TERMINAL_VELOCITY_X) {
            mEntities[0]->accelerate(Vector2D(-World::MOVEMENT_SPEED, 0.0));
        }
    }

    if (mIsJumping) {
        if (!mIsRecovering && (mCayoteTime)) {
            // Register jump, activate recovering so that player can't jump midair
            mIsJumping = false;
            mIsRecovering = true;
            const double vertical_velocity = mEntities[0]->getVelocity().mY;
            Vector2D JumpForce = Vector2D(0.0, -JUMP_FORCE);

            if (vertical_velocity < JUMP_FORCE) {
                if (vertical_velocity > 0) {
                    JumpForce.setY(JumpForce.getY() + vertical_velocity);
                } else {
                    JumpForce.setY(JumpForce.getY() + vertical_velocity);
                }
            } else {
                JumpForce.setY(0.0);
            }

            mEntities[0]->applyCollisionResponse(JumpForce);
        } else if (mIsOnLeftWall || mIsOnRightWall) {
            mIsJumping = false;
            Vector2D WallJumpForce = Vector2D(WALLJUMP_FORCE, -WALLJUMP_FORCE);
            const double vertical_velocity = mEntities[0]->getVelocity().mY;
            const double horizontal_velocity = mEntities[0]->getVelocity().mX;

            if (vertical_velocity < WALLJUMP_FORCE) {
                if (vertical_velocity > 0) {
                    WallJumpForce.setY(WallJumpForce.getY() + vertical_velocity);
                } else {
                    WallJumpForce.setY(WallJumpForce.getY() + vertical_velocity);
                }
            } else {
                WallJumpForce.setY(0.0);
            }

            if (mIsOnLeftWall) {
                WallJumpForce.setX(WallJumpForce.getX() * -1);
            }

            WallJumpForce.setX(WallJumpForce.getX() + horizontal_velocity);

            mIsOnLeftWall = false;
            mIsOnRightWall = false;
            mEntities[0]->applyCollisionResponse(WallJumpForce);
        }
    }

    if (mCayoteTime)
        mCayoteTime--;
}

bool Logic::World::lostGame() { return mLost; }

void Logic::World::calculateViewable() {
    const PhysicsHitbox cam_hitbox = mCamera.getHitbox();
    const Vector2D cam_pos = mCamera.getHitbox().getPosition();
    const double cam_factor = (mCamera.getHeight() / 2.0) + cam_pos.mY;
    const double cam_factor_x = cam_pos.mX - (mCamera.getWidth() / 2.0);

    const int entity_count = mEntities.size();
    for (int i = 0; i < entity_count; ++i) {
        if (aabbIntersectsAABB(mEntities[i]->getHitbox(), cam_hitbox)) {
            Vector2D obj_pos = mEntities[i]->getPosition();
            mEntities[i]->updateViewable(true);
            Vector2D calculated = Vector2D((obj_pos.mX - cam_factor_x), (cam_factor - obj_pos.mY)) * mViewScale;
            mEntities[i]->setRelativePosition(calculated);
        } else {
            mEntities[i]->updateViewable(false);
        }
    }
}

void Logic::World::updatePositions(double dt) {

    // Update entity positions
    mEntities[0]->updatePosition(dt);
    // OPTIMIZATION: Current version of game the player entity is the only none static entity.
    // So looping over all entities is wastefull, can change back if adding enemies for example.
    // For regular levels this was no issue but when experimenting with the slope approximation
    // there was some slowdown
    // std::for_each(mEntities.begin(), mEntities.end(), [dt](std::unique_ptr<Entity>& obj){
    //     if(!obj->isStatic()){
    //         obj->updatePosition(dt);
    //     }
    // });

    // Update camera position if required
    Vector2D cam_pos = mCamera.getPosition();
    const double cam_x = cam_pos.getX();
    const double cam_y = cam_pos.getY();
    const double cam_height = mCamera.getHeight() / 2.0;

    const Vector2D player_pos = mEntities[0]->getPosition();
    if (cam_y >= mCamera.getMaxY())
        return;
    if (mCamera.autoscroller()) {
        mCamera.setPosition(cam_pos + mCamera.getVelocity());
    } else if (player_pos.mY > cam_y + cam_height * 0.6) {
        mCamera.setPosition(Vector2D(cam_x, cam_y + (player_pos.mY - (cam_y + cam_height * 0.6))));
    }
}

void Logic::World::applyConstraints() {
    if (!mEntities[0]->isViewable()) {
        // If player is no longer viewable by camera it dies and level is lost.
        mLost = true;
        return; // void return to not perform unneccecary calculations
    }

    Vector2D player_velocity = mEntities[0]->getVelocity();

    if (player_velocity.getY() > -1 * TERMINAL_VELOCITY_Y) {
        mEntities[0]->accelerate(mGravity);
    }
    // OPTIMIZATION: Current version of game the player entity is the only one affected by gravity.
    // So looping over all entities is wastefull, can change back if adding enemies for example.
    // For regular levels this was no issue but when experimenting with the slope approximation
    // there was some slowdown

    // std::for_each(mEntities.begin(), mEntities.end(), [this](std::unique_ptr<Entity>& obj){
    //     if(obj->affectedByGravity()){
    //         if(obj->getVelocity().mY > -1*TERMINAL_VELOCITY_Y){
    //             obj->accelerate(mGravity);
    //         }
    //     }
    // });
}

void Logic::World::solveCollisions() {
    // Handles the collision detection and response.

    mIsOnLeftWall = false;
    mIsOnRightWall = false;

    mColliding = false;

    const int entity_count = mEntities.size();
    for (int i = 0; i < entity_count; ++i) {
        // Loop over every entity

        if (!mEntities[i]->isCollidable() || mEntities[i]->isStatic()) {
            // If object is not collidable and movable no point in proceeding further in loop
            continue;
        }

        for (int k = 0; k < entity_count; ++k) {
            // Loop over every entity to attempt to detect collision

            if (!mEntities[k]->isCollidable() || i == k) {
                // If object is not collidable or attempting to detect collison of entity with itself then no point in
                // proceeding further in loop
                continue;
            }

            const PhysicsHitbox hitbox_entity_i = mEntities[i]->getHitbox();
            const PhysicsHitbox hitbox_entity_k = mEntities[k]->getHitbox();
            if (aabbIntersectsAABB(hitbox_entity_i, hitbox_entity_k)) {
                // Collision detected, calculate collision response
                Vector2D pen = aabbPenetrationVector(aabbMinkowskiDiference(hitbox_entity_i, hitbox_entity_k)) *
                               mEntities[k]->getElasticity();
                const Vector2D velocity = mEntities[0]->getVelocity();

                if (i == 0) {
                    // player_airborne_flag = false;
                    if (mEntities[k]->interact(Entity::None) == Entity::Finish) {
                        mLevelComplete = true;
                    } else if (pen.mY <= -0.001) {
                        // Player is touching entity from above

                        mIsRecovering = false;
                        mCayoteTime = 90;
                        /*
                         *   First checking for movementevent and then velocity is most efficient evaluation,
                         *   because how AND logic gets compiled. Since velocity in direction of movementevent
                         *   is happens more frequently then velocity in direction without movement event
                         */
                        if (!mIsMovingLeft && velocity.mX < 0) {
                            mEntities[0]->accelerate(Vector2D(velocity.mX * FRICTION, 0.0));
                        } else if (!mIsMovingRight && velocity.mX > 0) {
                            mEntities[0]->accelerate(Vector2D(velocity.mX * FRICTION, 0.0));
                        }
                    } else if (pen.mY == 0.0 && (pen.mX != 0.0)) {
                        // Walltouch certain
                        if (pen.mX < 0) {
                            mIsOnLeftWall = true;
                        } else {
                            mIsOnRightWall = true;
                        }
                    } else if (pen.mY == 0.0 && (pen.mX == 0.0)) {
                        // Could be Walltouch, could be floortouch.
                        const Vector2D position_P = hitbox_entity_i.m_position;
                        const Vector2D position_W = hitbox_entity_k.m_position;
                        const Vector2D half_size_P = hitbox_entity_i.m_half_size;
                        const Vector2D half_size_W = hitbox_entity_k.m_half_size;
                        if ((position_P.mY > position_W.mY) &&
                            (position_P.mY - half_size_P.mY) - (position_W.mY + half_size_W.mY) >= -0.1) {
                            if ((position_P.mX > position_W.mX) &&
                                position_P.mX - half_size_P.mX <= position_W.mX + half_size_W.mX) {
                                // mIsOnFloor = true;
                            } else if ((position_P.mX < position_W.mX) &&
                                       position_P.mX + half_size_P.mX >= position_W.mX - half_size_W.mX) {
                                // mIsOnFloor = true;
                            }
                        } else if ((position_P.mX > position_W.mX) &&
                                   position_P.mX - half_size_P.mX <= position_W.mX + half_size_W.mX) {
                            mIsOnLeftWall = true;
                            if (velocity.mY < 0.0) {
                                // apply friction for sliding from side of entity only if falling down
                                mEntities[0]->accelerate(
                                    Vector2D(0.0, GRAVITY * (velocity.mY) / (-1.1 * (TERMINAL_VELOCITY_Y))));
                            }
                        } else if ((position_P.mX < position_W.mX) &&
                                   position_P.mX + half_size_P.mX >= position_W.mX - half_size_W.mX) {
                            mIsOnRightWall = true;
                            if (velocity.mY < 0.0) {
                                // apply friction for sliding from side of entity only if falling down
                                mEntities[0]->accelerate(
                                    Vector2D(0.0, GRAVITY * (velocity.mY) / (-1.1 * (TERMINAL_VELOCITY_Y))));
                            }
                        } else {
                            std::cout << "No penetration " << std::endl;
                        }
                    }
                }
                mEntities[i]->applyCollisionResponse(pen);
            }
        }

        break;
        // OPTIMIZATION: Current version of game the player entity is the only one which is movable.
        // So we break out of loop, can change back if adding enemies for example.
        // For regular levels this was no issue but when experimenting with the slope approximation
        // there was some slowdown
    }
}

bool Logic::World::pointIntersectsAABB(Vector2D point, PhysicsHitbox aabb) {
    Vector2D min_vec = aabb.m_position - aabb.m_half_size;
    Vector2D max_vec = aabb.m_position + aabb.m_half_size;
    return point.mX >= min_vec.mX && point.mX <= max_vec.mX && point.mY >= min_vec.mY && point.mY <= max_vec.mY;
}

Logic::PhysicsHitbox Logic::World::aabbMinkowskiDiference(PhysicsHitbox a, PhysicsHitbox b) {
    // Calculate and return MinkowskiDifference hitbox of two aabb's
    return PhysicsHitbox(a.m_position - b.m_position, a.m_half_size + b.m_half_size);
}

bool Logic::World::aabbIntersectsAABB(PhysicsHitbox a, PhysicsHitbox b) {
    return pointIntersectsAABB(Vector2D(0.0, 0.0), aabbMinkowskiDiference(a, b));
}

Vector2D Logic::World::aabbPenetrationVector(PhysicsHitbox aabb) {
    // Calculate the displacement vector based on the MinkowskiDifference hitbox
    Vector2D min_vec = aabb.m_position - aabb.m_half_size;
    Vector2D max_vec = aabb.m_position + aabb.m_half_size;

    double temp_min_dist = std::fabs(min_vec.mX);
    double temp_x = min_vec.mX;
    double temp_y = 0.0;
    if (std::fabs(max_vec.mX) < temp_min_dist) {
        temp_min_dist = std::fabs(max_vec.mX);
        temp_x = max_vec.mX;
    }
    if (std::fabs(min_vec.mY) < temp_min_dist) {
        temp_min_dist = std::fabs(min_vec.mY);
        temp_x = 0.0;
        temp_y = min_vec.mY;
    }
    if (std::fabs(max_vec.mY) < temp_min_dist) {
        temp_x = 0.0;
        temp_y = max_vec.mY;
    }

    return Vector2D(temp_x, temp_y);
}

void Logic::World::reset() {
    mEntities.clear();
    mIsMovingLeft = false;
    mIsMovingRight = false;
    mIsJumping = false;
    mIsOnLeftWall = false;
    mIsOnRightWall = false;
    mLeftWall = false;
    mIsRecovering = false;
    mLevelComplete = false;
    mLost = false;
}

void Logic::World::loadLevel() {
    if (mLost) {
        reset();
        mEntityFactory->setViewScale(mViewScale * mCamera.getWidth());
        LevelLoader loader = LevelLoader(mCurrentLevel, mEntityFactory);
        mViewScale = mEntityFactory->getViewScale();
        loader.getEntities(mEntities);
        mNextLevel = loader.getNextLevel();

        auto CamSettings = loader.getCameraSettings();
        mCamera.setResolution(std::get<0>(CamSettings));
        mCamera.setVelocity(std::get<1>(CamSettings));
        mCamera.setMaxY(std::get<2>(CamSettings));
        mCamera.setPosition(Vector2D(mCamera.getWidth() / 2.0, mCamera.getHeight() / 2.0));
    } else {
        if (mNextLevel == "") {
            mFinished = true;
        } else {
            reset();
            mEntityFactory->setViewScale(mViewScale * mCamera.getWidth());
            LevelLoader loader = LevelLoader(mNextLevel, mEntityFactory);
            mViewScale = mEntityFactory->getViewScale();
            loader.getEntities(mEntities);
            mNextLevel = loader.getNextLevel();
            auto CamSettings = loader.getCameraSettings();
            mCamera.setResolution(std::get<0>(CamSettings));
            mCamera.setVelocity(std::get<1>(CamSettings));
            mCamera.setMaxY(std::get<2>(CamSettings));
            mCamera.setPosition(Vector2D(mCamera.getWidth() / 2.0, mCamera.getHeight() / 2.0));
        }
    }
}

bool Logic::World::finishedGame() { return mFinished; }