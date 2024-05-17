#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Common_Function.h"
#include <math.h>
#include "Entity.h"
#include "Obstacle.h"
#include "skill.h"
#include "Tiles.h"
#include "AmmoObject.h"

const int BALL_HEIGHT = 15;
const int BALL_WIDTH = 15;

bool touchesWall( SDL_Rect box, Tile* tiles[] );

class Ball : public Entity
{
public:
    Ball();
//    ~Ball();
    void setBallPosX(double x) {pos.x = x;}
    void setBallPosY(double y) {pos.y = y;}
//    void setCir(Circle& x) {cir = x;}
    double getBallPosX() {return pos.x;}
    double getBallPosY() {return pos.y;}
    SDL_Texture* getBallTex() {return ball;}
    SDL_Texture* getHoleTex() {return hole;}

    Circle getCircle() {return cir;}
    bool checkSquareCollision(Obstacle* squareObs);
    bool checkCircleCollision(Obstacle* circleObs);
    bool checkCollision(std::vector<Obstacle*>& obs);
    bool checkBallClicked();

    void handleMirror(Obstacle* e);
    void handleEffect(std::vector<Obstacle*>& effect_obs);
    bool ballClicked() {return ball_clicked;}

    void setDead(bool d) {dead = d;}
    bool isDead() {return dead;}
    bool isMove() {return canMove;}
    void setBallIsMove(bool ok) {canMove = ok;}

    void setBall_clicked(bool ok) {ball_clicked = ok;}
    void setInitialMouseX(int x) {initialMouseX = x;}
    void setInitialMouseY(int y) {initialMouseY = y;}

    void setVelocityX(double v) {velocityX = v;}
    void setVelocityY(double v) {velocityY = v;}
    double getVelocityX() {return velocityX;}
    double getVelocityY() {return velocityY;}
    int getInitialMouseX() {return initialMouseX;}
    int getInitialMouseY() {return initialMouseY;}

    int getSign(double x) {
        return (x >= 0) ? 1 : -1;
    }

    void setEndMouse(Vector2f v) {endMouse = v;}
    Vector2f getEndMouse() {return endMouse;}

    void setSkill_r(int x) {circleBoom->set_r(x);}
    int getSkill_r() {return circleBoom->get_r();}
    void useSkill_0(int i);
    void useSkill_1(int i);
    void useSkill_2(int i);
    void setSkill(bool x, int i) {skill[i] = x;}
    bool getSkill(int i) {return skill[i];}
    double getCoolDownTime(int x) {return coolDownTime[x];}
    void setCoolDownTime(double time, int x) {coolDownTime[x] = time;}
    double getInitSkill(int x) {return initSkill[x];}
    void setInitSkill(double time, int x) {initSkill[x] = time;}

    void setCamera( SDL_Rect& camera );
    void setHP(int x) {healthPoints = x;}
    int getHP() {return healthPoints;}
    void setOther0(double x) {otherInit0 = x;}
    double getOther0() {return otherInit0;}
    double getCoolDown(int i) {return coolDown[i];}

    void updateAmmo(AmmoObject* ammo, int mouseX, int mouseY);
    void updateAmmoList(std::vector<AmmoObject*> x) {ammoList = x;}
    std::vector<AmmoObject*> getAmmoList() {return ammoList;}

    void updateCoolDown();
    void update(bool mouseDown, bool mousePressed, std::vector<Obstacle*>& effect_obs,
                    std::vector<Obstacle*>& static_obs, Tile *tiles[]);

private:
    std::vector<AmmoObject*> ammoList;
    Vector2f endMouse;
    int initialMouseX, initialMouseY;
    double velocityX, velocityY, dirX, dirY, r;
    double coolDown[4] = {2000, 500, 8000, 3000};
    bool ball_clicked, canMove = true;
    SDL_Rect ballRect_;
    SDL_Texture* ball;
    SDL_Texture* hole;
    bool dead;
    Circle cir;
    Skill* circleBoom = new Skill(0, 0);
    bool skill[4] = {0, 0, 0, 0};
    double initSkill[4] = {0, 0, 0, 0};
    double coolDownTime[4] = {0, 0, 0, 0};
    double otherInit0 = 0;

    int healthPoints = 100;

};


#endif // BALL_H_INCLUDED
