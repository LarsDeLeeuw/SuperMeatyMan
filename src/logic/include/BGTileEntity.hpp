#ifndef LOGIC_BGTILEENTITY_HPP
#define LOGIC_BGTILEENTITY_HPP

#include "Entity.hpp"

namespace Logic {
class BGTileEntity : public Entity {
public:
    BGTileEntity(Vector2D position, double width, double height);

    Entity::Interaction interact(Entity::Interaction other) override;
};
} // namespace Logic

#endif