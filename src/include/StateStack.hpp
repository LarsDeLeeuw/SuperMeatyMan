#ifndef VIEW_STATESTACK_HPP
#define VIEW_STATESTACK_HPP

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include <SFML/Window/Event.hpp>

#include "State.hpp"

class StateStack : public std::enable_shared_from_this<StateStack> {
public:
    enum Action { Push, Pop, Clear };

public:
    template <typename T>
    void registerState(State::Type stateType);

    void update(double dt);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(State::Type stateType);
    void popState();
    void clearStack();

    bool isEmpty() const;

    [[nodiscard]] static std::shared_ptr<StateStack> create() {
        // Not using std::make_shared<StateStack> because the c'tor is private.
        return std::shared_ptr<StateStack>(new StateStack());
    }

    std::string getContext();
    void setContext(std::string context);

private:
    StateStack() = default;
    std::unique_ptr<State> createState(State::Type stateType);
    void applyPendingChanges();

    std::vector<std::unique_ptr<State>> mStack;
    std::vector<std::pair<Action, State::Type>> mPendingList;

    std::map<State::Type, std::function<std::unique_ptr<State>()>> mFactories;
    std::string mContext = "";
};

template <typename T>
void StateStack::registerState(State::Type stateType) {
    mFactories[stateType] = [this]() { return std::make_unique<T>((weak_from_this())); };
}

#endif