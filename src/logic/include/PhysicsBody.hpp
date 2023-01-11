#ifndef LOGIC_PHYSICSBODY_HPP
#define LOGIC_PHYSICSBODY_HPP

#include "PhysicsHitbox.hpp"
#include "Vector2D.hpp"

namespace Logic {
class PhysicsBody {
public:
    PhysicsBody();
    PhysicsBody(Vector2D pos, Vector2D acc, double width, double height);

    Vector2D getPosition();
    void setPosition(Vector2D pos);
    const Vector2D getVelocity();
    Vector2D getAcceleration();
    void setAcceleration(Vector2D acc);
    PhysicsHitbox getHitbox();

    void updatePosition(double dt);
    void accelerate(Vector2D acc);

private:
    PhysicsHitbox mHitbox;
    Vector2D mPositionOld = Vector2D(0.0, 0.0);
    Vector2D mAcceleration = Vector2D(0.0, 0.0);
};
} // namespace Logic

#endif