#ifndef RENDERWINDOW_H_INCLUDED
#define RENDERWINDOW_H_INCLUDED

#include "Common_Function.h"

class RenderWindow
{
public:
    bool init();
    bool createRenderer();
    SDL_Texture* loadTexture(const char* path);
    void render(SDL_Texture* texture, SDL_Rect rect);
    void render(SDL_Texture* texture, SDL_Rect dest, SDL_Rect rect);
    void render(SDL_Texture* texture, SDL_Rect rect, double angle);
    void render(SDL_Texture* texture, float x, float y, float w, float h);
    void render(SDL_Texture* texture);

    void render(std::vector<SDL_Texture*> texVec, SDL_Rect rect, double angle);
    void Show();
    void Quit();
private:
    SDL_Window* gWindow;
    SDL_Renderer* renderer;
};


#endif // RENDERWINDOW_H_INCLUDED
