#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <iostream>
#include <SDL.h>

struct Vector2f
{
    double x, y;
    Vector2f() : x(0.0f), y(0.0f) {}
    Vector2f(double x_, double y_) : x(x_), y(y_) {}

    void print() {
        std::cout << x << ", " << y << "\n";
    }

    Vector2f operator - (Vector2f v) {
        return Vector2f(this->x - v.x, this->y - v.y);
    }
};
struct Linear
{
    double A, B;
    Linear(Vector2f a, Vector2f b) {
        A = (a.y - b.y) / (a.x - b.x);
        B = b.y - a.x * A;
    }
    Linear(double nx, double ny, Vector2f a) {
        A = -nx / ny;
        B = nx * a.x + ny * a.y;
    }
};

struct Circle
{
    int x, y;
    double r;
    Circle() {x = 0; y = 0; r = -1;}
    Circle(int x_, int y_, int r_) : x(x_), y(y_), r(r_) {}

    void print() {
        std::cout << x << ", " << y << "\n" << r << "\n";
    }
};

namespace mathFunc
{
    bool checkCollision(Circle a, Circle b);
    bool checkCollision(Circle a, SDL_Rect b);

    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool checkPointInside(Vector2f p, SDL_Rect a);

    Vector2f findIntersection(Linear c, Linear d);
    double distance(Vector2f c, Vector2f d);
    double distance(Vector2f c, Linear d);
    double cross(Vector2f c, Vector2f d);
    double dot(Vector2f c, Vector2f d);
    int getSign(double x);

}
#endif // MATH_H_INCLUDED
