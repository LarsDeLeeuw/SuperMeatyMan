#include "include/Camera.hpp"
#include "include/PhysicsBody.hpp"
#include "include/PhysicsHitbox.hpp"
#include "include/Vector2D.hpp"

Logic::Camera::Camera() {
    mPosition = Vector2D(0.0, 0.0);
    mWidth = 1920.0;
    mHeight = 1080.0;
    // mBody = PhysicsBody(Vector2D(960.0, 540.0), Vector2D(0.0, 0.0), 1920.0, 1080.0);
    mBody = PhysicsBody(Vector2D(mWidth / 2, mHeight / 2), Vector2D(0.0, 0.0), mWidth, mHeight);
}

bool Logic::Camera::autoscroller() { return !(mVelocity.getX() == 0.0 && mVelocity.mY == 0.0); }

Vector2D Logic::Camera::getVelocity() { return mVelocity; }

void Logic::Camera::setVelocity(Vector2D vel) { mVelocity = vel; }

void Logic::Camera::setResolution(Vector2D res) {
    mWidth = res.getX();
    mHeight = res.getY();
    mBody = PhysicsBody(Vector2D(mWidth / 2, mHeight / 2), Vector2D(0.0, 0.0), mWidth, mHeight);
}

void Logic::Camera::setMaxY(double maxy) { mMaxCamY = maxy; }
double Logic::Camera::getMaxY() { return mMaxCamY; }

Logic::Camera::~Camera() {}

Vector2D Logic::Camera::getPosition() { return mBody.getPosition(); }

Logic::PhysicsHitbox Logic::Camera::getHitbox() { return mBody.getHitbox(); }

void Logic::Camera::setPosition(Vector2D pos) { mBody.setPosition(pos); }

double Logic::Camera::getWidth() { return mWidth; }

double Logic::Camera::getHeight() { return mHeight; }