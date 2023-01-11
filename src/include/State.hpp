#ifndef VIEW_STATE_HPP
#define VIEW_STATE_HPP

#include <SFML/Window/Event.hpp>
#include <memory>

class StateStack;

class State {
public:
    enum Type { Menu, Level, Dead, None };

public:
    State();
    State(std::weak_ptr<StateStack> stack);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(double dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPush(State::Type stateType);
    void requestStackPop();
    void requestStackClear();
    void storeContext(std::string context);
    std::string requestContext();

private:
    std::weak_ptr<StateStack> mStack;
};

#endif