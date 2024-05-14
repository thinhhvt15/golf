#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "Common_Function.h"
#include "Math.h"

class Entity
{
public:
    Entity() {
        typeShape = 0;
        ratioE = 1.f;
        cir = {pos.x + r / 2.f, pos.y + r / 2.f, r};
        angle = 0;
        initialTime = 0;
        initPos = pos;
    }
//    ~Entity() {
//        SDL_DestroyTexture(texture);
//    }
    Entity(Vector2f p_scale, Vector2f p_pos) : scale(p_scale), pos(p_pos), initPos(p_pos) {}

    void setX(double x) {pos.x = x;}
    void setY(double y) {pos.y = y;}
    void setInitTime(double x) {initialTime = x;}
    double getInitTime() {return initialTime;}
    void setCurTime(double x) {currentTime = x;}
    double getCurTime() {return currentTime;}

    void setCurSprite(int x) {curSprite = x;}

    double getX() {return pos.x;}
    double getY() {return pos.y;}
    double getW() {return scale.x;}
    double getH() {return scale.y;}
    double getAngle() {return angle;}
    double getRatio() {return ratioE;}
    Circle getCir() {return cir;}
    void setCir(double x, double y, double r) {cir = Circle(x, y, r);}

    int getPar() {return par;}
    int getTypeShape() {return typeShape;}
    void setPar(int u) {par = u;}
    void setRatio(double x) {ratioE = x;}
    void setAngle(double ag) {angle = ag;}
    void setScale(double w, double h) {scale = Vector2f(w, h);}
    SDL_Rect getRect() {rect_ = {pos.x, pos.y, scale.x, scale.y}; return rect_;}
    SDL_Texture* getTex() {return texture;}
    void Show(SDL_Texture* txt, SDL_Rect);
    void nextSprite() {curSprite = (curSprite + 1) % numSprite;}
    void setNumSprite(int num) {numSprite = num;}
    int getCurSprite() {return curSprite;}
    double get_r() {return r;}
    double get_R() {return R;}
    bool angleSet() {return angle_set;}
    void setAngleIsSet(bool x) {angle_set = x;}
    Vector2f getPos() {return pos;}
    Vector2f getInitPos() {return initPos;}
    void setInitPos(Vector2f x) {initPos = x;}
    void setFlip(bool x) {flip = x;}
    bool getFlip() {return flip;}
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
    double endX, endY;
    bool flip = 0;
};


#endif // ENTITY_H_INCLUDED
