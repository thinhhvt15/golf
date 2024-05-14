#ifndef COLLISIONSANDEFFECTS_H_INCLUDED
#define COLLISIONSANDEFFECTS_H_INCLUDED

#include "Obstacle.h"

namespace CollisionDetect
{
    bool checkCollision(Entity* e, std::vector<Obstacle*>& static_obs);
//    bool checkEnemyCollision(Entity* e, std::vector<Enemies*>& enemVec);
}


#endif // COLLISIONSANDEFFECTS_H_INCLUDED
