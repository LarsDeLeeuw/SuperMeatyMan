#include "include/EntityFactory.hpp"

using namespace Logic;

EntityFactory::EntityFactory() = default;

EntityFactory::~EntityFactory() = default;

void EntityFactory::setViewScale(double view_scale) { mViewScale = view_scale; }
double EntityFactory::getViewScale() { return mViewScale; }