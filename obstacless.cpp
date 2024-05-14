#include "Obstacle.h"

Obstacle::Obstacle() {
    typeObs = typeOb::BOX;
    pos = Vector2f(20.f, 20.f);
    scale = Vector2f(50.f, 50.f);
    is_open = true;
}

Obstacle::Obstacle(Vector2f pos_, double R_)
{
    typeObs = 1;
    numSprite = 2;
    pos = pos_;
    R = R_;
    scale = scaleTypes[typeObs];
    r = scale.x / 2.f;
    is_open = true;
}

Obstacle::Obstacle(Vector2f pos_) {
    numSprite = 1;
    typeObs = 0;
    pos = pos_;
    is_open = true;
    scale = scaleTypes[typeObs];
}


