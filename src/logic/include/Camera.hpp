#ifndef LOGIC_CAMERA_HPP
#define LOGIC_CAMERA_HPP

#include "PhysicsBody.hpp"
#include "PhysicsHitbox.hpp"
#include "Vector2D.hpp"

namespace Logic {
class Camera {
public:
    Camera();
    ~Camera();

    void setResolution(Vector2D res);
    void setVelocity(Vector2D vel);
    void setMaxY(double maxy);
    double getMaxY();

    double getWidth();
    double getHeight();
    PhysicsHitbox getHitbox();

    void setPosition(Vector2D pos);
    Vector2D getPosition();
    bool autoscroller();
    Vector2D getVelocity();

private:
    PhysicsBody mBody;
    Vector2D mPosition = Vector2D(0.0, 720);
    double mWidth = 0.0;
    double mHeight = 0.0;
    double mMaxCamY = 0.0;
    Vector2D mVelocity = Vector2D(0.0, 0.0);
    bool mAutoscroller = false;
};
} // namespace Logic

#endif
