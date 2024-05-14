#include "MenuGame.h"

bool MENUu::insizeStart(int mouseX, int mouseY)
{
    return (mouseX >= LEFT && mouseX <= LEFT + wButton && mouseY >= upStart && mouseY <= upStart + hButton);
}

bool MENUu::insizeConfig(int mouseX, int mouseY)
{
    return (mouseX >= LEFT && mouseX <= LEFT + wButton && mouseY >= upConfig && mouseY <= upConfig + hButton);
}

bool MENUu::insizeEsc(int mouseX, int mouseY)
{

}
void MENUu::update(bool mouseDown)
{
    if (mouseDown) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (state == GAMESTATE::CONFIG) {
            if (insizeEsc(mouseX, mouseY))
                gameConfig = 0;
        }

        if (insizeStart(mouseX, mouseY))
            state = GAMESTATE::START;

        if (insizeConfig(mouseX, mouseY))
            state = GAMESTATE::CONFIG;
    }
}
