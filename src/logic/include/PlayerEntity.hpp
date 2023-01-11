#ifndef LOGIC_PLAYERENTITY_HPP
#define LOGIC_PLAYERENTITY_HPP

#include "Entity.hpp"

namespace Logic {
class PlayerEntity : public Entity {
public:
    PlayerEntity(Vector2D position, Vector2D acceleration);
    Entity::Interaction interact(Entity::Interaction other) override;

    bool getAlive();
    void setAlive(bool state);

private:
    bool mIsAlive = true;
};
} // namespace Logic

#endif