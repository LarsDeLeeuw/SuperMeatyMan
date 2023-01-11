#ifndef VIEW_CONCRETEENTITYFACTORY_HPP
#define VIEW_CONCRETEENTITYFACTORY_HPP

#include <vector>

#include "../logic/include/EntityFactory.hpp"

namespace View {

class Entity;

class ConcreteEntityFactory : public Logic::EntityFactory {
public:
    ConcreteEntityFactory();

    virtual std::unique_ptr<Logic::Entity> createPlayer(Vector2D& position, Vector2D& acceleration) override;
    virtual std::unique_ptr<Logic::Entity> createWall(Vector2D& position, double width, double height,
                                                      char variant) override;
    virtual std::unique_ptr<Logic::Entity> createPlatform(Vector2D& position, double width, double height, char variant,
                                                          double elasticity) override;
    virtual std::unique_ptr<Logic::Entity> createGoal(Vector2D& position) override;
    virtual std::unique_ptr<Logic::Entity> createBGTile(Vector2D& position, double width, double height) override;

    void drawEntities();

private:
    std::vector<std::shared_ptr<View::Entity>> mEntityViews;
};
} // namespace View

#endif