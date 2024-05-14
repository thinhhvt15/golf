#ifndef MENUGAME_H_INCLUDED
#define MENUGAME_H_INCLUDED

#include "Math.h"
#include "Common_Function.h"

class MENUu
{
public:
    enum buttonPos
    {
        LEFT = (750 - 200) / 2,
        upStart = 750 / 2 - 100,
        upConfig = 750 / 2 + 130,
        upEsc = 100,
        wButton = 200,
        hButton = 92
    };

    bool insizeEsc(int mouseX, int mouseY);
    bool insizeStart(int mouseX, int mouseY);
    bool insizeConfig(int mouseX, int mouseY);
    void update(bool mouseDown);
private:
    SDL_Rect rect_;
    Vector2f scaleType[1] = {Vector2f(200, 92)};
};

#endif // MENUGAME_H_INCLUDED
