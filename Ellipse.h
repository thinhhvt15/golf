#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED

#include "Math.h"
#include "Obstacle.h"
#include "Ball.h"

class Ellipse : public Obstacle
{
public:
    Ellipse();
//    Ellipse(Vector2f center_, float rx_, float ry_) : pos(center_), rx(rx_), ry(ry_) {}
//    Ellipse(Vector2f center_, float rx_, float ry_, float Rx_, float Ry_) : pos(center_), rx(rx_), ry(ry_), Rx(Rx_), Ry(Ry_) {}
    ~Ellipse();

private:
    float rx, ry;
    float Rx, Ry;
};

bool checkCollision(Ellipse* E, Ball* b);

#endif // ELLIPSE_H_INCLUDED
