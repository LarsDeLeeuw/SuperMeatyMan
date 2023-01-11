#include "include/Subject.hpp"

Subject::Subject() = default;

Subject::~Subject() = default;

void Subject::Attach(std::weak_ptr<Observer> observer) { mObservers.push_back(observer); }

void Subject::Detach(std::weak_ptr<Observer> observer) {
    bool eFound = false;
    for (std::list<std::weak_ptr<Observer>>::iterator it = mObservers.begin(); it != mObservers.end(); ++it) {
        if (observer.lock() == (*it).lock()) {
            mObservers.erase(it);
            eFound = true;
        }
    }
    if (!eFound) {
        // std::cout << "raise exception lol\n";
    }
}
