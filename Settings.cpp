#include "Settings.h"

Settings::Settings()
{
    music = 100;
    sfx = 100;
    mode = 100;
    rect_.x = 620;
    rect_.y = 130;
    rect_.w = 50;
    rect_.h = 60;
    button = nullptr;
    settingScreen = nullptr;
}

//void Settings::LoadIMG(const char* path, SDL_Renderer* gRenderer, SDL_Texture* texture) {
//    texture = SDL_CommonFunc::loadTexture(gRenderer, path);
//}

int Settings::setVolume(int i) {music = i;}
int Settings::setSfx(int i) {sfx = i;}
int Settings::setMode(int i) {mode = i;}

int Settings::getX() {return rect_.x;}
int Settings::getY() {return rect_.y;}
void Settings::setX(int x) {rect_.x = x;}
void Settings::setY(int y) {rect_.y = y;}
int Settings::setSize(int w, int h)
{
    rect_.w = w;
    rect_.h = h;
}

bool Settings::insizeMusic(int mouseX, int mouseY)
{
    return (music_up <= mouseY && mouseY <= music_down &&
        LEFT <= mouseX && mouseX <= RIGHT);
}

bool Settings::insizeMode(int mouseX, int mouseY)
{
    return (mode_up <= mouseY && mouseY <= mode_down &&
        LEFT <= mouseX && mouseX <= RIGHT);
}

bool Settings::insizeSFX(int mouseX, int mouseY)
{
    return (sfx_up <= mouseY && mouseY <= sfx_down &&
        LEFT <= mouseX && mouseX <= RIGHT);
}

void Settings::setMouse(bool mouseDown, bool mousePressed)
{

//    if (mousePressed) {
//        int mouseX = 0, mouseY = 0;
//        SDL_GetMouseState(&mouseX, &mouseY);
//
//        std::cout << "1: " << mouseX << " " << mouseY << "\n";
//    }

    if (mouseDown) {
            int mouseX = 0, mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
        if (insizeMode(mouseX, mouseY) || insizeMusic(mouseX, mouseY)
            || insizeSFX(mouseX, mouseY))
                setInitialMouse(true);
        if (mouseCanInitial()) {

//            std::cout << "2: " << mouseX << " " << mouseY << "\n";
            if (mouseX > RIGHT)
                mouseX = RIGHT;
            else if (mouseX < LEFT)
                mouseX = LEFT;

            setX(mouseX); setY(130);
        }
    }

//        setX(mouseX); setY(mouseY);
//        setX(mouseX); setY(mouseY);
}

//void Settings::loadSettingScreen(const char* path)
//{
//    settingScreen = SDL_CommonFunc::loadTexture(gRenderer, path);
//}

//void Settings::loadButton(const char* path)
//{
//    button = SDL_CommonFunc::loadTexture(gRenderer, path);
//}

//void Settings::showSettingScreen() {
//    SDL_Rect rect = {(SCREEN_WIDTH - 997) / 2, 0, 997, 1004};
//    SDL_RenderCopy(gRenderer, settingScreen, nullptr, &rect);
//}

//void Settings::showButton() {
//    SDL_RenderCopy(gRenderer, button, nullptr, &rect_);
//}
