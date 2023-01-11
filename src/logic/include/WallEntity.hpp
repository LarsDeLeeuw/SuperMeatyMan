#ifndef LOGIC_WALLENTITY_HPP
#define LOGIC_WALLENTITY_HPP

#include "Entity.hpp"

namespace Logic {
class WallEntity : public Entity {
public:
    WallEntity(Vector2D position);
    WallEntity(Vector2D position, double width, double height);
    Entity::Interaction interact(Entity::Interaction other) override;
};
} // namespace Logic

#endif