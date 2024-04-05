#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "Common_Function.h"
#include "Math.h"

class Entity
{
public:
    Entity() {}
    ~Entity() {
        SDL_DestroyTexture(texture);
    }
    Entity(Vector2f p_scale, Vector2f p_pos) : scale(p_scale), pos(p_pos) {}

    void setX(float x) {pos.x = x;}
    void setY(float y) {pos.y = y;}
    float getX() {return pos.x;}
    float getY() {return pos.y;}
    float getW() {return scale.x;}
    float getH() {return scale.y;}
    void setScale(float w, float h) {scale = Vector2f(w, h);}
    SDL_Rect getRect() {rect_ = {pos.x, pos.y, scale.x, scale.y}; return rect_;}
    SDL_Texture* getTex() {return texture;}
    void Show(SDL_Texture* txt, SDL_Rect);
    void nextSprite() {curSprite = (curSprite + 1) % numSprite;}
    void setNumSprite(int num) {numSprite = num;}
    int getCurSprite() {return curSprite;}
    float get_r() {return r;}
    float get_R() {return R;}
    bool checkCollision( Entity* y )
    {
        SDL_Rect a = {this->pos.x, this->pos.y, this->scale.x, this->scale.y};
        SDL_Rect b = {y->pos.x, y->pos.y, y->scale.x, y->scale.y};
        //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;

        //Calculate the sides of rect A
        leftA = a.x;
        rightA = a.x + a.w;
        topA = a.y;
        bottomA = a.y + a.h;

        //Calculate the sides of rect B
        leftB = b.x;
        rightB = b.x + b.w;
        topB = b.y;
        bottomB = b.y + b.h;

          //If any of the sides from A are outside of B
        if( bottomA <= topB )
        {
            return false;
        }

        if( topA >= bottomB )
        {
            return false;
        }

        if( rightA <= leftB )
        {
            return false;
        }

        if( leftA >= rightB )
        {
            return false;
        }

        //If none of the sides from A are outside B
        return true;
    }

protected:
    SDL_Rect rect_;
    Vector2f scale, pos;
    SDL_Texture* texture;
    double angle;
    int curSprite = 0;
    int numSprite;
    float r, R;
};


#endif // ENTITY_H_INCLUDED
