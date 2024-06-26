#ifndef AMMOOBJECT_H_INCLUDED
#define AMMOOBJECT_H_INCLUDED

#include "BaseObject.h"

class AmmoObject : public BaseObject
{
public:
    AmmoObject();
    AmmoObject(float x, float y);
    ~AmmoObject();
    bool isMove() {return is_move;}
    void setMove(bool x) {is_move = x;}
    void setVelocityX(double x) {velocityX = x;}
    double getVelocityX() {return velocityX;}
    void setVelocityY(double y) {velocityY = y;}
    double getVelocityY() {return velocityY;}

    void setInitAmmo(double x) {initAmmo = x;}
    double getInitAmmo() {return initAmmo;}

private:
    double velocityX, velocityY;
    bool is_move;
    double initAmmo = 0;
};

#endif // AMMOOBJECT_H_INCLUDED
