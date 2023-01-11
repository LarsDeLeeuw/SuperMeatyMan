#include "include/LevelLoader.hpp"
#include "include/Vector2D.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

Logic::LevelLoader::LevelLoader(std::string filename, std::shared_ptr<EntityFactory> factory) {
    // Load level inputfile into parser
    try {
        loadFile(filename);
    } catch (std::runtime_error& e) {
        throw std::runtime_error(e.what());
    } catch (...) {
        throw std::runtime_error("Unknown exception occured whilst opening file in LevelLoader");
    }

    for (TiXmlElement* element = getRoot()->FirstChildElement(); element != NULL;
         element = element->NextSiblingElement()) {
        // Go over every XML-element until eof is reached
        if (element->Value() == std::string("GENERAL")) {
            // Parse general leveldata
            for (TiXmlElement* entity_element = element->FirstChildElement(); entity_element != NULL;
                 entity_element = entity_element->NextSiblingElement()) {
                // Go over every child of the element
                if (entity_element->Value() == std::string("Camera")) {
                    char* pEnd;
                    if (entity_element->FirstChildElement("width") != NULL) {
                        mCamResolution.setX(
                            strtod(entity_element->FirstChildElement("width")->FirstChild()->ToText()->Value(), &pEnd));
                        factory->setViewScale(factory->getViewScale() / mCamResolution.getX());
                    }
                    if (entity_element->FirstChildElement("height") != NULL) {
                        mCamResolution.setY(strtod(
                            entity_element->FirstChildElement("height")->FirstChild()->ToText()->Value(), &pEnd));
                    }
                    if (entity_element->FirstChildElement("autoscroll") != NULL) {
                        if (entity_element->FirstChildElement("autoscroll")->FirstChildElement("direction") == NULL) {
                            std::cerr << "No direction element inside autoscroll found, ignoring autoscroll."
                                      << std::endl;
                            continue;
                        }
                        std::string direction = entity_element->FirstChildElement("autoscroll")
                                                    ->FirstChildElement("direction")
                                                    ->FirstChild()
                                                    ->ToText()
                                                    ->Value();
                        if (entity_element->FirstChildElement("autoscroll")->FirstChildElement("speed") == NULL) {
                            std::cerr << "No direction element inside autoscroll found, ignoring autoscroll."
                                      << std::endl;
                            continue;
                        }
                        double speed = strtod(entity_element->FirstChildElement("autoscroll")
                                                  ->FirstChildElement("speed")
                                                  ->FirstChild()
                                                  ->ToText()
                                                  ->Value(),
                                              &pEnd);
                        if (direction == std::string("horizontal")) {
                            mCamMovement.setX(speed);
                        } else {
                            mCamMovement.setY(speed);
                        }
                    }
                }
            }
        }

        if (element->Value() == std::string("ENTITIES")) {
            if (element->FirstChildElement()->Value() != std::string("Player")) {
                throw std::runtime_error("Player not declared (first).");
            }

            for (TiXmlElement* entity_element = element->FirstChildElement(); entity_element != NULL;
                 entity_element = entity_element->NextSiblingElement()) {
                if (entity_element->FirstChildElement("x_pos") == NULL) {
                    throw std::runtime_error("Entity missing required field.");
                }
                if (entity_element->FirstChildElement("y_pos") == NULL) {
                    throw std::runtime_error("Entity missing required field.");
                }
                char* pEnd;
                double x_pos =
                    strtod(entity_element->FirstChildElement("x_pos")->FirstChild()->ToText()->Value(), &pEnd);
                double y_pos =
                    strtod(entity_element->FirstChildElement("y_pos")->FirstChild()->ToText()->Value(), &pEnd);

                Vector2D pos = Vector2D(x_pos, y_pos);

                if (entity_element->Value() == std::string("GrassPlatform")) {
                    // Compound statement for declaring a 'grassplatform' which is just a bunch off walls.
                    // Created this to simplify level creation e.g. media/levels/level2.xml
                    pos = pos + Vector2D(-100.0, 0.0);
                    mEntities.push_back(factory->createWall(pos, 50.0, 50.0, 2));
                    for (int i = 0; i < 4; i++) {
                        pos = pos + Vector2D(50.0, 0.0);
                        mEntities.push_back(factory->createWall(pos, 50.0, 50.0, 2));
                    }
                    pos = pos + Vector2D(-150.0, -50.0);
                    mEntities.push_back(factory->createWall(pos, 50.0, 50.0, 0));
                    for (int i = 0; i < 2; i++) {
                        pos = pos + Vector2D(50.0, 0.0);
                        mEntities.push_back(factory->createWall(pos, 50.0, 50.0, 0));
                    }
                    continue;
                } else if (entity_element->Value() == std::string("Goal")) {
                    // Goal Entity
                    mEntities.push_back(factory->createGoal(pos));
                    if (entity_element->FirstChildElement("nextlevel") == NULL) {
                        // No level after
                    } else {
                        mNextLevel = entity_element->FirstChildElement("nextlevel")->FirstChild()->ToText()->Value();
                    }
                    continue;
                } else if (entity_element->Value() == std::string("Player")) {
                    // Player Entity
                    Vector2D acc = Vector2D(0.0, 0.0);
                    mEntities.push_back(factory->createPlayer(pos, acc));
                    continue;
                }

                if (entity_element->FirstChildElement("width") == NULL) {
                    throw std::runtime_error("Entity missing required field.");
                }
                if (entity_element->FirstChildElement("height") == NULL) {
                    throw std::runtime_error("Entity missing required field.");
                }
                double width =
                    strtod(entity_element->FirstChildElement("width")->FirstChild()->ToText()->Value(), &pEnd);
                double height =
                    strtod(entity_element->FirstChildElement("height")->FirstChild()->ToText()->Value(), &pEnd);
                if (entity_element->Value() == std::string("BGTile")) {
                    // BGTile Entity
                    mEntities.push_back(factory->createBGTile(pos, width, height));
                    continue;
                }

                if (entity_element->FirstChildElement("variant") == NULL) {
                    throw std::runtime_error("Entity missing required field.");
                }
                char variant =
                    strtod(entity_element->FirstChildElement("variant")->FirstChild()->ToText()->Value(), &pEnd);

                if (entity_element->Value() == std::string("WALLS")) {
                    // Compound statement for multiple Wall Entity
                    if (entity_element->FirstChildElement("amount") == NULL) {
                        throw std::runtime_error("Entity missing required field.");
                    }
                    if (entity_element->FirstChildElement("direction") == NULL) {
                        throw std::runtime_error("Entity missing required field.");
                    }
                    int amount =
                        strtod(entity_element->FirstChildElement("amount")->FirstChild()->ToText()->Value(), &pEnd);
                    std::string direction =
                        entity_element->FirstChildElement("direction")->FirstChild()->ToText()->Value();
                    if (direction == std::string("horizontal")) {
                        while (amount-- > 0) {
                            mEntities.push_back(factory->createWall(pos, width, height, variant));
                            pos = pos + Vector2D(width, 0.0);
                        }
                    } else {
                        while (amount-- > 0) {
                            mEntities.push_back(factory->createWall(pos, width, height, variant));
                            pos = pos + Vector2D(0.0, height);
                        }
                    }
                } else if (entity_element->Value() == std::string("Wall")) {
                    // Wall Entity
                    mEntities.push_back(factory->createWall(pos, width, height, variant));
                } else if (entity_element->Value() == std::string("Platform")) {
                    // Experimental entity
                    double elasticity = 1.0;
                    if (entity_element->FirstChildElement("elasticity") != NULL) {
                        elasticity = strtod(
                            entity_element->FirstChildElement("elasticity")->FirstChild()->ToText()->Value(), &pEnd);
                    }
                    mEntities.push_back(factory->createPlatform(pos, width, height, variant, elasticity));
                } else if (entity_element->Value() == std::string("DIAG")) {
                    // Experimenting with aproximating slope not used in premade levels
                    if (entity_element->FirstChildElement("direction") == NULL) {
                        throw std::runtime_error("Entity missing required field.");
                    }
                    std::string direction =
                        entity_element->FirstChildElement("direction")->FirstChild()->ToText()->Value();
                    double temp = 200.0;
                    if (direction == std::string("down")) {
                        for (int i = 0; i < temp; i++) {
                            mEntities.push_back(factory->createPlatform(pos, 100 / temp, 100 / temp, 0, 1.0));
                            pos = pos + Vector2D(100 / temp, -100 / temp);
                        }
                    } else {
                        for (int i = 0; i < temp; i++) {
                            mEntities.push_back(factory->createPlatform(pos, 100 / temp, 100 / temp, 0, 1.0));
                            pos = pos + Vector2D(100 / temp, 100 / temp);
                        }
                    }
                }
            }
        }
    }
}

void Logic::LevelLoader::getEntities(std::vector<std::unique_ptr<Entity>>& new_owner) {
    // First find highest position of static entity
    const int size = mEntities.size();
    for (int i = 0; i < size; i++) {
        if (mEntities[i]->isStatic()) {
            if (mEntities[i]->getPosition().getY() > mMaxCamHeight)
                mMaxCamHeight = mEntities[i]->getPosition().getY();
        }
    }
    // Make sure cam does not show area above maxheight
    mMaxCamHeight -= (mCamResolution.getY() / 2);
    std::move(begin(mEntities), end(mEntities), std::back_inserter(new_owner));
    mEntities.clear();
}

std::string Logic::LevelLoader::getNextLevel() { return mNextLevel; }

std::tuple<Vector2D, Vector2D, double> Logic::LevelLoader::getCameraSettings() {
    return std::make_tuple(mCamResolution, mCamMovement, mMaxCamHeight);
}