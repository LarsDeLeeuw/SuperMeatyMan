#ifndef VIEW_GAMESTATE_HPP
#define VIEW_GAMESTATE_HPP

#include <memory>

#include "../logic/include/World.hpp"

#include "ConcreteEntityFactory.hpp"
#include "State.hpp"

class GameState : public State {
public:
    GameState(std::weak_ptr<StateStack> stack);

    virtual void draw();
    virtual bool update(double dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    bool mWaitingJumpRelease = false;
    bool mIdle = false;
    std::shared_ptr<View::ConcreteEntityFactory> mConcreteFactory = std::make_shared<View::ConcreteEntityFactory>();
    std::unique_ptr<Logic::World> mWorld;
};

#endif