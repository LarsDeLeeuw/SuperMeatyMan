#ifndef LOGIC_OBSERVER_HPP
#define LOGIC_OBSERVER_HPP

#include "Vector2D.hpp"

// Abstract class for Observer-Subject Design Pattern
class Observer {
public:
    Observer();
    virtual ~Observer();
    virtual void update() = 0;
    virtual void update(Vector2D& pos, bool viewable) = 0;
};

#endif
