#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include "Entity.h"
#include <math.h>
#include "CollisionsAndEffects.h"
#include "AmmoObject.h"
#include "Ball.h"

class Enemies : public Entity
{

public:
    Enemies();
    Enemies(float x, float y, int type);
//    ~Enemies();
    void update(float x, float y, std::vector<Obstacle*>& static_obs, std::vector<Obstacle*>& effect_obs, std::vector<Enemies*>& enemeo);
    void setType(int x) {type = x;}
    int getType() {return type;}
    std::vector<AmmoObject*> getAmmoList() {return ammoList;}
    void setAmmoList(std::vector<AmmoObject*>& ammoVec) {ammoList = ammoVec;}
    void update1(Ball* b, std::vector<Obstacle*>& static_obs, std::vector<Obstacle*>& effect_obs, std::vector<Enemies*>& enemeo,
                 SDL_Rect& camera);
    void updateAmmo(float x, float y);
    void Move(std::vector<Obstacle*>& static_obs, std::vector<Enemies*>& enemeo);
    void reload();
    void updateAmmo(Ball* b, AmmoObject* ammo, SDL_Rect& camera);
    int getCurAmmo() {return curAmmo;}
    void setDieType(int x) {dieType = x;}
    int getDieType() {return dieType;}
    void setDead(bool x) {dead = x;}
    bool isDead() {return dead;}
    void setInitAni(double x) {initAnimationTime = x;}
    double getInitAni() {return initAnimationTime;}

private:
    float velocityX, velocityY;
    std::vector<AmmoObject*> ammoList;
    int type;
    double initialTime, initAnimationTime;
    Vector2f sizeType[1] = {Vector2f(30, 40)};
    int curAmmo = 0;
    bool flip = 0;
    bool dead = 0;
    int dieType = 0;
};

#endif // ENEMIES_H_INCLUDED
