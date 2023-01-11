#ifndef LOGIC_ENTITY_HPP
#define LOGIC_ENTITY_HPP

#include "PhysicsBody.hpp"
#include "PhysicsHitbox.hpp"
#include "Subject.hpp"
#include "Vector2D.hpp"
#include <list>

namespace Logic {

class Entity : public Subject {
public:
    enum Interaction { None, Move, Teleport, Damage, Finish };

public:
    Entity();
    virtual ~Entity();
    // TODO: Should implement these too because of Rule Of Five
    // Entity(Entity& other) = default;
    // Entity& operator=(Entity& other) = default;
    // Entity(Entity&& other) = default;
    // Entity& operator=(Entity&& other) = default;

    virtual void Notify() override;

    virtual Vector2D getPosition();
    virtual void setPosition(Vector2D& pos);

    virtual const Vector2D getVelocity();
    virtual PhysicsHitbox getHitbox();

    virtual void applyCollisionResponse(Vector2D& pen);
    void updatePosition(double dt);
    void accelerate(Vector2D grav);

    virtual void setRelativePosition(Vector2D& pos);

    virtual Interaction interact(Interaction other) = 0;

    double getElasticity();
    bool isViewable();
    bool isStatic();
    bool isCollidable();
    bool affectedByGravity();
    void updateViewable(bool isViewable);

protected:
    bool mViewable = false;
    bool mCollidable = true;
    bool mGravityAffected = false;
    bool mStaticBody = true;

    double mElasticity = 1.0; // Minimal bounce
    Logic::PhysicsBody mBody = PhysicsBody();
    Vector2D mRelativePosition = Vector2D(0.0, 0.0);
};
} // namespace Logic

#endif
