#ifndef VIEW_ENTITYVIEW_HPP
#define VIEW_ENTITYVIEW_HPP

#include <SFML/Graphics.hpp>

#include "../logic/include/Observer.hpp"

namespace View {
class Entity : public Observer {
public:
    Entity();
    virtual ~Entity();

    void update() override;
    virtual void update(Vector2D& pos, bool viewable) override;

    void draw();
    void flip();
    void setScale(double scale);
    bool active();
    bool isViewable();

protected:
    // Every Entity's view will require a sprite and texture
    sf::Sprite mSprite;
    sf::Texture mTexture;

private:
    bool mViewable = false;
    bool waitingForDelete = false;
};
} // namespace View

#endif