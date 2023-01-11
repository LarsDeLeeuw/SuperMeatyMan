#ifndef VIEW_PLAYERVIEW_HPP
#define VIEW_PLAYERVIEW_HPP

#include "EntityView.hpp"

namespace View {
class Player : public Entity {
public:
    Player();
    void update(Vector2D& pos, bool viewable) override;

private:
    double mPrevX = 0.0;
    bool mLeft = false;
};
} // namespace View

#endif