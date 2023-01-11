#include "include/Vector2D.hpp"
#include <iostream>
#include <math.h>

Vector2D::Vector2D() {
    mX = 0.0;
    mY = 0.0;
}

Vector2D::Vector2D(double x, double y) {
    mX = x;
    mY = y;
}

double Vector2D::length() { return std::sqrt(mX * mX + mY * mY); }

const double Vector2D::getX() { return mX; }

void Vector2D::setX(double x) { mX = x; }

const double Vector2D::getY() { return mY; }

void Vector2D::setY(double y) { mY = y; }

Vector2D Vector2D::operator+(const Vector2D& b) {
    Vector2D retObj = Vector2D();
    retObj.mX = mX + b.mX;
    retObj.mY = mY + b.mY;
    return retObj;
}

Vector2D Vector2D::operator-(const Vector2D& b) {
    Vector2D retObj = Vector2D();
    retObj.mX = mX - b.mX;
    retObj.mY = mY - b.mY;
    return retObj;
}

Vector2D Vector2D::operator*(const Vector2D& b) {
    Vector2D retObj = Vector2D();
    retObj.mX = mX * b.mX;
    retObj.mY = mY * b.mY;
    return retObj;
}

Vector2D Vector2D::operator*(const double b) {
    Vector2D retObj = Vector2D();
    retObj.mX = mX * b;
    retObj.mY = mY * b;
    return retObj;
}

Vector2D Vector2D::operator/(const double b) {
    Vector2D retObj = Vector2D();
    retObj.mX = mX / b;
    retObj.mY = mY / b;
    return retObj;
}