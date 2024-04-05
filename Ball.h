#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Common_Function.h"
#include "Entity.h"
#include "Obstacle.h"

const int BALL_HEIGHT = 15;
const int BALL_WIDTH = 15;

class Ball : public Entity
{
public:
    Ball();
    void setBallPosX(float x) {pos.x = x;}
    void setBallPosY(float y) {pos.y = y;}
    float getBallPosX() {return pos.x;}
    float getBallPosY() {return pos.y;}
    SDL_Texture* getBallTex() {return ball;}
    SDL_Texture* getHoleTex() {return hole;}

    bool checkCollision(std::vector<Obstacle*>& obs);
    bool checkBallClicked();
    bool ballClicked() {return ball_clicked;}

    bool isMove() {return canMove;}
    void setBallIsMove(bool ok) {canMove = ok;}

    void setBall_clicked(bool ok) {ball_clicked = ok;}
    void setInitialMouseX(int x) {initialMouseX = x;}
    void setInitialMouseY(int y) {initialMouseY = y;}

    void setVelocityX(float v) {velocityX = v;}
    void setVelocityY(float v) {velocityY = v;}
    float getVelocityX() {return velocityX;}
    float getVelocityY() {return velocityY;}
    int getInitialMouseX() {return initialMouseX;}
    int getInitialMouseY() {return initialMouseY;}

    int getSign(double x) {
        return (x >= 0) ? 1 : -1;
    }

    void setEndMouse(Vector2f v) {endMouse = v;}
    Vector2f getEndMouse() {return endMouse;}

    void update(bool mouseDown, bool mousePressed, std::vector<Obstacle*>& obs);

private:
    Vector2f endMouse;
    int initialMouseX, initialMouseY;
    float velocityX, velocityY, dirX, dirY, r;
    bool ball_clicked, canMove = true;
    SDL_Rect ballRect_;
    SDL_Texture* ball;
    SDL_Texture* hole;
};


#endif // BALL_H_INCLUDED
