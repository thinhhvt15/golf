#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include "Common_Function.h"

class Settings
{
public:
    enum MODE {
        EASY = 1,
        NORMAL = 2,
        HARD = 3
    };

    enum typeSettingsPos {
        music_up = 130,
        music_down = 130 + 97,
        sfx_up = 387,
        sfx_down = 440,
        mode_up = 622,
        mode_down = 1004,
        LEFT = 620,
        RIGHT = 1125
    };

    Settings();

    void LoadIMG(const char* path, SDL_Texture* texture);
    int setVolume(int i);
    int setSfx(int i);
    int setMode(int i);

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int setSize(int w, int h);
    SDL_Texture* getButton() {return button;}
    SDL_Texture* getScreen() {return settingScreen;}
    SDL_Rect getRect() {return rect_;}
    bool mouseCanInitial() {return initialMouse;}
    void setInitialMouse(bool ok) {initialMouse = ok;}

    bool insizeMusic(int mouseX, int mouseY);
    bool insizeSFX(int mouseX, int mouseY);
    bool insizeMode(int mouseX, int mouseY);

    void setMouse(bool mouseDown, bool mousePressed);
    void loadSettingScreen(const char* path);
    void loadButton(const char* path);
    void showSettingScreen();
    void showButton();


private:
    int music, sfx, mode;
    SDL_Rect rect_;
    SDL_Texture* button;
    SDL_Texture* settingScreen;
    bool initialMouse;
};


#endif // SETTINGS_H_INCLUDED
