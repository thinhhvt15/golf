#include "CollisionsAndEffects.h"

bool CollisionDetect::checkCollision(Entity* e, std::vector<Obstacle*>& static_obs )
{
    if (e->getTypeShape() == 0) {
        for (Obstacle* obs : static_obs) {
            if (obs->getTypeObs() == 0) {
                if (mathFunc::checkCollision(e->getRect(), obs->getRect())) return 1;
            }
            else if (obs->getTypeObs() == 1) {
                if (mathFunc::checkCollision(obs->getCir(), e->getRect())) return 1;
            }
        }
    }
    else {
        for (Obstacle* obs : static_obs) {
            if (obs->getTypeObs() == 0) {
                if (mathFunc::checkCollision(e->getCir(), obs->getRect())) return 1;
            }
            else if (obs->getTypeObs() == 1) {
                if (mathFunc::checkCollision(e->getCir(), obs->getCir())) return 1;
            }
        }
    }

    return 0;
}
