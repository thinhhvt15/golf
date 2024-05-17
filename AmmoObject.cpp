#include "AmmoObject.h"
#include "Ball.h"

AmmoObject::AmmoObject()
{
    is_move = 1;
    scale = {25, 20};
    initAmmo = SDL_GetTicks();
}

AmmoObject::AmmoObject(float x, float y)
{
    is_move = 1;
    pos = Vector2f(x, y);
    scale = {25, 20};
    initAmmo = SDL_GetTicks();
}

AmmoObject::~AmmoObject()
{

}
