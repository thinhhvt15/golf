#include "RenderWindow.h"

bool RenderWindow::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not be intialize %s\n", SDL_GetError());
        return 0;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0) {
        printf("IMG could not be intialize %s\n", IMG_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              450, 750, SDL_WINDOW_SHOWN);

    if (gWindow == nullptr) {
        printf("Window get error", SDL_GetError());
        return 0;
    }

    return 1;
}

bool RenderWindow::createRenderer()
{
    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Cannot create renderer %s\n", SDL_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return 1;
}

SDL_Texture* RenderWindow::loadTexture(const char* path)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s\n", path, IMG_GetError());
    }
    else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    }
//    texture = IMG_LoadTexture(gRenderer, path);


    if (texture == nullptr) {
        printf("Cannot load texture %s\n", path, SDL_GetError());
    }

    return texture;
}

void RenderWindow::render(SDL_Texture* texture, SDL_Rect rect, double angle)
{
    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}
void RenderWindow::render(SDL_Texture* texture, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void RenderWindow::render(SDL_Texture* texture, float x, float y, float w, float h)
{
    SDL_Rect rect;
    rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void RenderWindow::render(SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void RenderWindow::render(SDL_Texture* texture, SDL_Rect dest, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, &dest, &rect);
}

void RenderWindow::render(std::vector<SDL_Texture*> texVec, SDL_Rect rect, double angle)
{
    for(auto e : texVec) {
        SDL_RenderCopyEx(renderer, e, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
//        SDL_Delay(100);
    }
}
void RenderWindow::Show()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::Quit()
{
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

