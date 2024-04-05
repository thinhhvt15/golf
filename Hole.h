#ifndef HOLE_H_INCLUDED
#define HOLE_H_INCLUDED

#include "Entity.h"
class Hole : public Entity
{
public:
    Hole() {
        scale = {20, 20};
        pos = {450.f / 2, 100};
    }
    bool inHole(int X, int Y) {return pos.x - 4 <= X && X <= pos.x + 22 && pos.y - 4 <= Y && Y <= pos.y + 22;}

};

#endif // HOLE_H_INCLUDED
