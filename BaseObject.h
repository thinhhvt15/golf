#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Common_Function.h"
class BaseObject
{
public:
    enum Direction
    {
        LEFT = 0,
        RIGHT = 1,
        UP = 2,
        DOWN = 3
    };

    BaseObject();
    ~BaseObject();

    bool LoadIMG(const char* path);

    void SetRect(const int x, const int y) {rect_.x = x; rect_.y = y;}
    void SetSize(const int w, const int h) {rect_.w = w; rect_.h = h;}

    void SetClips(const int step, const int y, const int w, const int h);
    void SetRClips(const int step, const int y, const int w, const int h);

    SDL_Rect getRect() {return rect_;};
    int getDirection() {return direction;}
    int getCur_clips() {return cur_clips;}

    void Show();
    void Show_all();
    void ShowAnimation();

protected:
    SDL_Rect rect_;
    SDL_Texture* gObject;
    std::vector<SDL_Rect> Clips;
    int direction;
    int cur_clips;
};
#endif // BASE_OBJECT_H_
