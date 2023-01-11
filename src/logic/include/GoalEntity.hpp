#ifndef LOGIC_GOALENTITY_HPP
#define LOGIC_GOALENTITY_HPP

#include "Entity.hpp"

namespace Logic {
class GoalEntity : public Entity {
public:
    GoalEntity(Vector2D position);

    Entity::Interaction interact(Entity::Interaction other) override;
};
} // namespace Logic

#endif