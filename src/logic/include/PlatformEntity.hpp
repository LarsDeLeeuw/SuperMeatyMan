#ifndef LOGIC_PLATFORMENTITY_HPP
#define LOGIC_PlatformEntity_HPP

#include "Entity.hpp"

namespace Logic {
class PlatformEntity : public Entity {
public:
    PlatformEntity(Vector2D position);
    PlatformEntity(Vector2D position, double width, double height, double elasticity);
    Entity::Interaction interact(Entity::Interaction other) override;
};
} // namespace Logic

#endif