#ifndef LOGIC_ENTITYFACTORY_HPP
#define LOGIC_ENTITYFACTORY_HPP

#include "Vector2D.hpp"
#include <memory>

namespace Logic {

class Entity;

class EntityFactory {
public:
    EntityFactory();
    virtual ~EntityFactory();

    virtual std::unique_ptr<Logic::Entity> createPlayer(Vector2D& position, Vector2D& acceleration) = 0;
    virtual std::unique_ptr<Entity> createWall(Vector2D& position, double width, double height, char variant) = 0;
    virtual std::unique_ptr<Entity> createPlatform(Vector2D& position, double width, double height, char variant,
                                                   double elasticity) = 0;
    virtual std::unique_ptr<Logic::Entity> createGoal(Vector2D& position) = 0;
    virtual std::unique_ptr<Entity> createBGTile(Vector2D& position, double width, double height) = 0;

    void setViewScale(double view_scale);
    double getViewScale();

protected:
    double mViewScale = 1.0;
};
} // namespace Logic

#endif