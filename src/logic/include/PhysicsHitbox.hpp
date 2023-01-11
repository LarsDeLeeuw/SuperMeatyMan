#ifndef LOGIC_PHYSICSHITBOX_HPP
#define LOGIC_PHYSICSHITBOX_HPP

#include "Vector2D.hpp"

namespace Logic {
class PhysicsHitbox {
    // Currently aabb but could transform this to abstract class and create seperate aabb and other hitbox type if
    // needed
public:
    PhysicsHitbox();
    PhysicsHitbox(Vector2D position, Vector2D half_size);
    Vector2D getPosition();
    void setPosition(Vector2D pos);
    Vector2D m_position;
    Vector2D m_half_size;
};

} // namespace Logic

#endif