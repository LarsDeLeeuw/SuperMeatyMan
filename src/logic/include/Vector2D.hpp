#ifndef LOGIC_VECTOR2D_HPP
#define LOGIC_VECTOR2D_HPP

class Vector2D {
public:
    Vector2D();
    Vector2D(double x, double y);
    double length();
    Vector2D operator+(const Vector2D& b);
    Vector2D operator-(const Vector2D& b);
    Vector2D operator*(const Vector2D& b);
    Vector2D operator*(const double b);
    Vector2D operator/(const double b);
    const double getX();
    void setX(double x);
    const double getY();
    void setY(double y);
    // Made these members public for performance reasons.
    // Accesing these via getters and setters could introduce way to many useless function calls depending on compiler.
    double mX;
    double mY;
};

#endif