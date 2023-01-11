#include <memory>

#include "include/State.hpp"
#include "include/StateStack.hpp"

State::State() = default;

State::State(std::weak_ptr<StateStack> stack) : mStack(stack) {}

State::~State() = default;

void State::requestStackPush(State::Type stateType) {
    if (!mStack.expired()) {
        // Check if object pointed to is still alive.
        mStack.lock()->pushState(stateType);
    }
}

void State::requestStackPop() {
    if (!mStack.expired()) {
        // Check if object pointed to is still alive.
        mStack.lock()->popState();
    }
}

void State::requestStackClear() {
    if (!mStack.expired()) {
        // Check if object pointed to is still alive.
        mStack.lock()->clearStack();
    }
}

void State::storeContext(std::string context) {
    if (!mStack.expired()) {
        // Check if object pointed to is still alive.
        mStack.lock()->setContext(context);
    }
}

std::string State::requestContext() {
    if (!mStack.expired()) {
        // Check if object pointed to is still alive.
        return mStack.lock()->getContext();
    }
    return "";
}