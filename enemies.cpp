#include "Enemies.h"

Enemies::Enemies()
{
    velocityX = 0;
    velocityY = 0;
    initialTime = 0;
    currentTime = 0;
    cir = {pos.x + r, pos.y + r, r};
    curAmmo = 0;
    initPos = pos;
//    reload();
}

Enemies::Enemies(float x, float y, int type_)
{
    pos = Vector2f(x, y);
    type = type_;
    scale = sizeType[type];
    velocityX = 0;
    velocityY = 0;
    curAmmo = 0;
    initPos = pos;
    if (type == 0) setNumSprite(4);
//    reload();
}

bool checkEnemyCollision(Entity* e, std::vector<Enemies*>& enemVec)
{
    for (Enemies* enem : enemVec) {
        if (enem == e) continue;
        if (enem->getTypeShape() == 0) {
            if (mathFunc::checkCollision(enem->getRect(), e->getRect())) return 1;
        }
        else if (enem->getTypeShape() == 1) {
            if (mathFunc::checkCollision(enem->getCir(), e->getRect())) return 1;
        }
    }

    return 0;
}

double currentTime;
void handleEnemyThroughEffects(Enemies* enem, std::vector<Obstacle*>& effect_obs)
{
    for (Obstacle* e : effect_obs) {
        if (e->getTypeObs() == 1)  {
            Vector2f i1(e->getX() + e->getW() / 2.f, e->getY() + e->getH() / 2.f); // tam guong
            Vector2f i2(enem->getX() + enem->getW() / 2.f, enem->getY() + enem->getH() / 2.f); // tam qua bong

            if ( e->isOpen() && effect_obs[e->getPar()]->isOpen() && (e->get_r() - enem->get_r()) * (e->get_r() - enem->get_r())  >= mathFunc::distance(i1, i2) ) {
                enem->setX(effect_obs[e->getPar()]->getX() + e->get_r());
                enem->setY(effect_obs[e->getPar()]->getY() + e->get_r());

                double x = SDL_GetTicks();
                effect_obs[e->getPar()]->setInitTime(x);
                e->setInitTime(x);

                effect_obs[e->getPar()]->setOpen(false);
                e->setOpen(false);
            }

            currentTime = SDL_GetTicks();
            if (currentTime - e->getInitTime() >= 1000)
                e->setOpen(true);
        }
    }
}

void Enemies::Move(std::vector<Obstacle*>& static_obs, std::vector<Enemies*>& enemeo)
{
    setX(getX() + velocityX);

    if (CollisionDetect::checkCollision(this, static_obs) || checkEnemyCollision(this, enemeo))
        setX(getX() - velocityX);

    setY(getY() + velocityY);
    if (CollisionDetect::checkCollision(this, static_obs) || checkEnemyCollision(this, enemeo))
        setY(getY() - velocityY);
}
void Enemies::update(float x, float y, std::vector<Obstacle*>& static_obs, std::vector<Obstacle*>& effect_obs, std::vector<Enemies*>& enemeo)
{
    velocityX = mathFunc::getSign(x - getX()) * 0.1;
    velocityY = mathFunc::getSign(y - getY()) * 0.1;

    handleEnemyThroughEffects(this, effect_obs);
    Move(static_obs, enemeo);
}

void Enemies::reload()
{
    ammoList.clear();
    AmmoObject* newAmmo = new AmmoObject(getX(), getY());
    for (int i = 0; i < 5; i++)
        ammoList.push_back(newAmmo);

}
void Enemies::updateAmmo(Ball* b, AmmoObject* ammo, SDL_Rect& camera)
{
    double guessX = b->getBallPosX() + camera.x + b->getVelocityX();
    double guessY = b->getBallPosY() + camera.y + b->getVelocityY();

    if (!ammo->angleSet()) {
        ammo->setAngle(-atan2(guessX - getX(), guessY - getY()) * 180 / 3.1415);
        ammo->setAngleIsSet(1);
        ammo->setDistance( SDL_sqrt( SDL_pow(guessX - getX(), 2) + SDL_pow(guessY - getY(), 2)) );
        ammo->setDirectionX( (guessX - getX()) / ammo->getDistance() * 0.25);
        ammo->setDirectionY( (guessY - getY()) / ammo->getDistance() * 0.25 );
//        ammo->setVelocityY(SDL_sqrt(0.5 * 0.5 - SDL_pow(ammo->getVelocityX(), 2)));
    }

    ammo->setX(ammo->getX() + ammo->getDirectionX());
    ammo->setY(ammo->getY() + ammo->getDirectionY());
}

void Enemies::update1(Ball* b, std::vector<Obstacle*>& static_obs, std::vector<Obstacle*>& effect_obs, std::vector<Enemies*>& enemeo,
                      SDL_Rect& camera)
{
    curSprite = (curSprite + 1) % numSprite + 1;
    for (int i = 0; i < (int)ammoList.size(); i++)
        updateAmmo(b, ammoList.at(i), camera);

    velocityX = mathFunc::getSign(b->getBallPosX() - getX()) * 0.1;
    velocityY = mathFunc::getSign(b->getBallPosY() - getY()) * 0.1;

    if (velocityX == 0 && velocityY == 0)
        curSprite = 0;

    if (mathFunc::getSign(b->getBallPosX() - getX()) < 0)
        setFlip(1);
    else
        setFlip(0);

    handleEnemyThroughEffects(this, effect_obs);
    Move(static_obs, enemeo);

    if (SDL_GetTicks() - getCurTime() >= 500) {
        AmmoObject* newAmmo = new AmmoObject(getX(), getY());
        ammoList.push_back(newAmmo);
        setCurTime(SDL_GetTicks());
    }

    if ((int)ammoList.size() == 5) {
        if (SDL_GetTicks() - getInitTime() >= 3000) {
            ammoList.clear();
            setInitTime(SDL_GetTicks());
        }
    }

}
