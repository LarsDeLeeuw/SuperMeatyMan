#ifndef LOGIC_SUBJECT_HPP
#define LOGIC_SUBJECT_HPP

#include "Observer.hpp"
#include <list>
#include <memory>

// Abstract class for Observer-Subject Design Pattern

// I'm using weak_ptr because I don't think a subject should keep an Observer object alive.
// Advantage: An object can get deleted without first detaching from the subject.
// Disadvantage: Have to convert weak_ptr to shared_ptr if not expired.

class Subject {
public:
    Subject();
    virtual ~Subject();

    virtual void Attach(std::weak_ptr<Observer> observer);
    virtual void Detach(std::weak_ptr<Observer> observer);
    virtual void Notify() = 0;

protected:
    std::list<std::weak_ptr<Observer>> mObservers;
};

#endif
