#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

#include "Entity.h"

class Obstacle : public Entity
{
public:

    Obstacle();
    Obstacle(Vector2f pos_);
    Obstacle(Vector2f pos_, double R_);
    enum typeOb
    {
        BOX = 0,
        MIRROR = 1
    };
    int getTypeObs() {return typeObs;}
    bool isOpen() {return is_open;}
    void setOpen(bool x) {is_open = x;}

private:
    bool impact;
    int typeObs;
    Vector2f scaleTypes[3] = {Vector2f(50.f, 50.f), Vector2f(70.f, 70.f)};
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, -1, 0, 1};
    bool is_open;
};



#endif // OBSTACLE_H_INCLUDED
