#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <iostream>

struct Vector2f
{
    float x, y;
    Vector2f() : x(0.0f), y(0.0f) {}
    Vector2f(float x_, float y_) : x(x_), y(y_) {}

    void print() {
        std::cout << x << ", " << y << "\n";
    }

    Vector2f operator - (Vector2f v) {
        return Vector2f(this->x - v.x, this->y - v.y);
    }
};
struct Linear
{
    float A, B;
    Linear(Vector2f a, Vector2f b) {
        A = (a.y - b.y) / (a.x - b.x);
        B = b.y - a.x * A;
    }
};

#endif // MATH_H_INCLUDED
