#ifndef LOGIC_LEVELLOADER_HPP
#define LOGIC_LEVELLOADER_HPP

#include <memory>
#include <vector>

#include "tinyxml/tinyxml.h"

#include "AbstractParser.hpp"
#include "Entity.hpp"
#include "EntityFactory.hpp"
#include "Vector2D.hpp"

namespace Logic {
class LevelLoader : public AbstractParser {
public:
    LevelLoader(std::string filename, std::shared_ptr<EntityFactory> factory);
    void getEntities(std::vector<std::unique_ptr<Entity>>& new_owner);
    std::string getNextLevel();
    std::tuple<Vector2D, Vector2D, double> getCameraSettings();

private:
    std::shared_ptr<EntityFactory> mEntityFactory;
    std::vector<std::unique_ptr<Entity>> mEntities;
    std::string mNextLevel = "";
    double mMaxCamHeight = 0.0;
    Vector2D mCamResolution = Vector2D(1920.0, 1080.0); // Default
    Vector2D mCamMovement =
        Vector2D(0.0, 0.0); // Zero vector means no scrolling, x or y value determinine autoscroll speed and direction
};
} // namespace Logic

#endif