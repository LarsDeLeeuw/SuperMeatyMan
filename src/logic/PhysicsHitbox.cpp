#include "include/PhysicsHitbox.hpp"
#include "include/Vector2D.hpp"

Logic::PhysicsHitbox::PhysicsHitbox() : m_position(Vector2D(0.0, 0.0)), m_half_size(Vector2D(0.0, 0.0)) {}

Logic::PhysicsHitbox::PhysicsHitbox(Vector2D position, Vector2D half_size)
    : m_position(position), m_half_size(half_size) {}

Vector2D Logic::PhysicsHitbox::getPosition() { return m_position; }

void Logic::PhysicsHitbox::setPosition(Vector2D pos) { m_position = pos; }