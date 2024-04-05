#include "BaseObject.h"

BaseObject::BaseObject() {
    rect_.x = 0;
    rect_.y = 0;
    gObject = nullptr;
    Clips.resize(FRAMES);
}

BaseObject::~BaseObject() {
    if (gObject != nullptr) {
        SDL_DestroyTexture(gObject);
    }
}

void BaseObject::SetClips(const int step, const int y, const int w, const int h)
{
    for (int i = 0; i < FRAMES; i++) {
        this->Clips[i].x = i * step;
        this->Clips[i].y = y;
        this->Clips[i].w = w;
        this->Clips[i].h = h;
    }
}

void BaseObject::SetRClips(const int step, const int y, const int w, const int h)
{
    for (int i = FRAMES - 1; i >= 0; i--) {
        this->Clips[i].x = i * step;
        this->Clips[i].y = y;
        this->Clips[i].w = w;
        this->Clips[i].h = h;
    }
}

bool BaseObject::LoadIMG(const char* path) {
//    std::cout << (renderer != nullptr) << "\n";
    gObject = SDL_CommonFunc::loadTexture(gRenderer, path);
    return (gObject != nullptr);
}

void BaseObject::Show_all()
{
    SDL_RenderCopy(gRenderer, gObject, nullptr, nullptr);
    SDL_RenderPresent(gRenderer);
}

void BaseObject::Show() {
//    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
//    SDL_SetTextureBlendMode(gObject, SDL_BLENDMODE_BLEND);
//    SDL_Rect abc = nullptr;
    SDL_CommonFunc::renderTexture(gObject, rect_, gRenderer);
    SDL_RenderPresent(gRenderer);
}

void BaseObject::ShowAnimation()
{
    SDL_CommonFunc::renderAnimation(gObject, Clips[cur_clips], rect_, gRenderer);
    SDL_RenderPresent(gRenderer);
}
