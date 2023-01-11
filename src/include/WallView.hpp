#ifndef VIEW_WALLVIEW_HPP
#define VIEW_WALLVIEW_HPP

#include "EntityView.hpp"

namespace View {
class Wall : public Entity {
public:
    Wall(double width, double height, char variant);
};
} // namespace View

#endif