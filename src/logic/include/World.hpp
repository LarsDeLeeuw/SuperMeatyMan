#ifndef DOODLEJUMPER_WORLD_HPP
#define DOODLEJUMPER_WORLD_HPP

#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "Entity.hpp"
#include "EntityFactory.hpp"
#include "PhysicsHitbox.hpp"
#include "PlayerEntity.hpp"
#include "Vector2D.hpp"

namespace Logic {
class World {
public:
    enum Input { LeftPressed, LeftReleased, RightPressed, RightReleased, JumpPressed, JumpReleased, Restart };

public:
    World(std::string levelname, std::shared_ptr<EntityFactory> factory, double window_width = 1920.0,
          double window_height = 1080.0);
    ~World();
    World& operator=(World&& other) {
        mEntities = std::move(other.mEntities);
        return *this;
    };
    void update(double dt);
    void updatePositions(double dt);
    void applyGravity();
    void applyConstraints();
    void solveCollisions();
    void calculateViewable();

    void input(Logic::World::Input event);
    void handleInput();
    std::vector<std::unique_ptr<Entity>> mEntities;

    bool finishedGame();
    bool lostGame();

private:
    bool pointIntersectsAABB(Vector2D point, PhysicsHitbox aabb);
    bool aabbIntersectsAABB(PhysicsHitbox a, PhysicsHitbox b);
    PhysicsHitbox aabbMinkowskiDiference(PhysicsHitbox a, PhysicsHitbox b);
    Vector2D aabbPenetrationVector(PhysicsHitbox aabb);

    void reset();
    void loadLevel();

private:
    static const double TERMINAL_VELOCITY_X;
    static const double TERMINAL_VELOCITY_Y;
    static const double MOVEMENT_SPEED;
    static const double GRAVITY;
    static const double FRICTION;
    static const double JUMP_FORCE;
    static const double WALLJUMP_FORCE;

    std::string mCurrentLevel;
    std::string mNextLevel;
    bool mFinished = false;
    bool mLost = false;

    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
    bool mIsJumping = false;
    bool mIsOnLeftWall = false;
    bool mIsOnRightWall = false;
    bool mIsOnFloor = false;
    bool mLeftWall = false;
    bool mColliding = false;
    bool mIsRecovering = false;
    unsigned int mCayoteTime = 0;
    bool mLevelComplete = false;

    std::shared_ptr<EntityFactory> mEntityFactory = nullptr;
    Logic::Camera mCamera;
    double mViewScale = 1.0;
    Vector2D mGravity;
};
} // namespace Logic

#endif
