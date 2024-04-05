#include "Common_Function.h"

SDL_Renderer* gRenderer = nullptr;
SDL_Texture* g_background = nullptr;
SDL_Event events;

SDL_Renderer* SDL_CommonFunc::createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Cannot create renderer %s\n", SDL_GetError());
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    return renderer;
}

SDL_Texture* SDL_CommonFunc::loadTexture(SDL_Renderer* renderer, const char* path)
{
//    std::cout << (renderer != nullptr) << "\n";

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

void SDL_CommonFunc::renderTexture(SDL_Texture* texture, SDL_Rect dest, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

void SDL_CommonFunc::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void SDL_CommonFunc::renderAnimation(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer)
{
//    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, &src, &dest);
}

void SDL_CommonFunc::quitSDL(SDL_Renderer* renderer, SDL_Window* window)
{
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL_CommonFunc::waitUntilKeyPressed() {
    SDL_Event e;
    while(1) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_QUIT || e.type == SDL_KEYDOWN)) return;
    }

}
