#ifndef Common_Function
#define Common_Function

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

static const char* WINDOW_TITLE = "SDLON";
const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 450;
const int FRAMES = 16;

namespace SDL_CommonFunc
{
    SDL_Renderer* createRenderer(SDL_Window* window);
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
    void renderTexture(SDL_Texture* texture, SDL_Rect dest, SDL_Renderer* renderer);
    void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer);
    void renderAnimation(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer);
    void quitSDL(SDL_Renderer* renderer, SDL_Window* window);
    void waitUntilKeyPressed();
};
#endif // Common_Function
