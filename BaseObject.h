#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "Common_Function.h"
#include "Math.h"

class BaseObject
{
public:
    void setX(double x) {pos.x = x;}
    void setY(double y) {pos.y = y;}
    void setInitTime(double x) {initialTime = x;}
    double getInitTime() {return initialTime;}
    void setCurTime(double x) {currentTime = x;}
    double getCurTime() {return currentTime;}

    double getX() {return pos.x;}
    double getY() {return pos.y;}
    double getW() {return scale.x;}
    double getH() {return scale.y;}
    double getAngle() {return angle;}
    double getRatio() {return ratioE;}
    void setCir(double x, double y, double r) {cir = Circle(x, y, r);}
    Circle getCir() {return cir;}
    int getPar() {return par;}
    int getTypeShape() {return typeShape;}
    void setPar(int u) {par = u;}
    void setRatio(double x) {ratioE = x;}
    void setAngle(double ag) {angle = ag;}
    void setScale(double w, double h) {scale = Vector2f(w, h);}
    SDL_Rect getRect() {rect_ = {pos.x, pos.y, scale.x, scale.y}; return rect_;}
    SDL_Texture* getTex() {return texture;}
    void setTex(SDL_Texture* tex) {texture = tex;}
    void nextSprite() {curSprite = (curSprite + 1) % numSprite;}
    void setNumSprite(int num) {numSprite = num;}
    int getCurSprite() {return curSprite;}
    double get_r() {return r;}
    double get_R() {return R;}
    void set_r(double r_) {r = r_;}
    bool angleSet() {return angle_set;}
    void setAngleIsSet(bool x) {angle_set = x;}
    Vector2f getPos() {return pos;}
    Vector2f getInitPos() {return initPos;}
    void setInitPos(Vector2f x) {initPos = x;}
    double getDirectionX() {return directionX;}
    double getDirectionY() {return directionY;}
    double getDistance() {return distance;}
    void setDirectionX(double x) {directionX = x;}
    void setDirectionY(double y) {directionY = y;}
    void setDistance(double d) {distance = d;}
    void setEndX(double x) {endX = x;}
    void setEndY(double y) {endY = y;}
    double getEndX() {return endX;}
    double getEndY() {return endY;}

protected:
    bool angle_set;
    SDL_Rect rect_;
    Vector2f scale, pos, initPos;
    SDL_Texture* texture;
    double angle;
    int curSprite = 0;
    int numSprite;
    double r, R;
    Circle cir;
    double ratioE;
    int par;
    int typeShape;
    double initialTime, currentTime;
    bool flip = 0;
    double directionX = 0, directionY = 0, distance = 0;
    double endX, endY;
};

#endif // BASEOBJECT_H_INCLUDED
