#include <algorithm>
#include <iostream>
#include <memory>

#include "logic/include/BGTileEntity.hpp"
#include "logic/include/EntityFactory.hpp"
#include "logic/include/GoalEntity.hpp"
#include "logic/include/PlatformEntity.hpp"
#include "logic/include/PlayerEntity.hpp"
#include "logic/include/Vector2D.hpp"
#include "logic/include/WallEntity.hpp"

#include "include/BGTileView.hpp"
#include "include/ConcreteEntityFactory.hpp"
#include "include/GoalView.hpp"
#include "include/PlayerView.hpp"
#include "include/WallView.hpp"

View::ConcreteEntityFactory::ConcreteEntityFactory() = default;

void View::ConcreteEntityFactory::drawEntities() {
    // As a rule for the levelspecifications the BGTile always needs to be the last entity declared.
    // We can use this to then first draw the BGTile so every other entity get's drawn above it.
    (*(mEntityViews.end() - 1))->draw();
    for (auto it = mEntityViews.begin(); it != mEntityViews.end() - 1;) {
        if ((*it)->active()) {
            if ((*it)->isViewable()) {
                (*it)->draw();
            }
            ++it;
        } else {
            // Entity views for entities that no longer exist should get removed.
            it = mEntityViews.erase(it);
        }
    }
    // As a rule for the levelspecifications the Player always needs to be the first entity declared.
    // We can use this to draw the Player last so it gets drawn above every other entity.
    (*(mEntityViews.begin()))->draw();
}

std::unique_ptr<Logic::Entity> View::ConcreteEntityFactory::createPlayer(Vector2D& position, Vector2D& acceleration) {
    std::unique_ptr<Logic::Entity> ret = std::make_unique<Logic::PlayerEntity>(position, acceleration);
    std::shared_ptr<View::Entity> view = std::make_shared<View::Player>();
    view->setScale(mViewScale);
    ret->Attach(view);
    mEntityViews.push_back(view);
    return ret;
}

std::unique_ptr<Logic::Entity> View::ConcreteEntityFactory::createBGTile(Vector2D& position, double width,
                                                                         double height) {
    std::unique_ptr<Logic::Entity> ret = std::make_unique<Logic::BGTileEntity>(position, width, height);
    std::shared_ptr<View::Entity> view = std::make_shared<View::BGTile>(width, height);
    view->setScale(mViewScale);
    ret->Attach(view);
    mEntityViews.push_back(view);
    return ret;
}

std::unique_ptr<Logic::Entity> View::ConcreteEntityFactory::createWall(Vector2D& position, double width, double height,
                                                                       char variant) {
    std::unique_ptr<Logic::Entity> ret = std::make_unique<Logic::WallEntity>(position, width, height);
    std::shared_ptr<View::Entity> view = std::make_shared<View::Wall>(width, height, variant);
    view->setScale(mViewScale);
    ret->Attach(view);
    mEntityViews.push_back(view);
    return ret;
}

std::unique_ptr<Logic::Entity> View::ConcreteEntityFactory::createPlatform(Vector2D& position, double width,
                                                                           double height, char variant,
                                                                           double elasticity) {
    std::unique_ptr<Logic::Entity> ret = std::make_unique<Logic::PlatformEntity>(position, width, height, elasticity);
    std::shared_ptr<View::Entity> view = std::make_shared<View::Wall>(width, height, variant + 10);
    view->setScale(mViewScale);
    ret->Attach(view);
    mEntityViews.push_back(view);
    return ret;
}

std::unique_ptr<Logic::Entity> View::ConcreteEntityFactory::createGoal(Vector2D& position) {
    std::unique_ptr<Logic::Entity> ret = std::make_unique<Logic::GoalEntity>(position);
    std::shared_ptr<View::Entity> view = std::make_shared<View::Goal>();
    view->setScale(mViewScale);
    ret->Attach(view);
    mEntityViews.push_back(view);
    return ret;
}
