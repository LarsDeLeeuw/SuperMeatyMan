#include <cassert>
#include <memory>
#include <utility>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "include/State.hpp"
#include "include/StateStack.hpp"

std::string StateStack::getContext() { return mContext; }

void StateStack::setContext(std::string context) { mContext = context; }

std::unique_ptr<State> StateStack::createState(State::Type stateType) {
    auto found = mFactories.find(stateType);
    assert(found != mFactories.end()); // Handle this exception?

    return found->second();
}

void StateStack::update(double dt) {
    // Update every state in stack
    for (long unsigned int i = 0; i < mStack.size(); i++) {
        mStack[i]->update(dt);
    }
    applyPendingChanges();
}

void StateStack::draw() {
    // Draw every state in stack
    for (long unsigned int i = 0; i < mStack.size(); i++) {
        mStack[i]->draw();
    }
}

void StateStack::handleEvent(const sf::Event& event) {
    // handleEvent for every state in stack
    for (long unsigned int i = 0; i < mStack.size(); i++) {
        mStack[i]->handleEvent(event);
    }
    applyPendingChanges();
}

void StateStack::pushState(State::Type stateType) { mPendingList.push_back(std::make_pair(Push, stateType)); }

void StateStack::popState() { mPendingList.push_back(std::make_pair(Pop, State::Type::None)); }

void StateStack::clearStack() { mPendingList.push_back(std::make_pair(Clear, State::Type::None)); }

bool StateStack::isEmpty() const { return mStack.empty(); }

void StateStack::applyPendingChanges() {
    // Go through pending changes and execute FIFO order, clear pending after.
    for (std::pair<Action, State::Type> pending_change : mPendingList) {
        switch (pending_change.first) {
        case Push:
            mStack.push_back(createState(pending_change.second));
            break;
        case Pop:
            mStack.pop_back();
            break;
        case Clear:
            mStack.clear();
            break;
        }
    }

    mPendingList.clear();
}