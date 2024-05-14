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
    void render(SDL_Texture* texture, SDL_Rect dest, SDL_Rect rect, double angle, int flip);
    void render(SDL_Texture* texture, SDL_Rect dest, SDL_Rect rect, double angle, int flip, double Ratio);
    void render(SDL_Texture* texture, SDL_Rect rect, double angle, int flip);
    void render(SDL_Texture* texture, double x, double y, double w, double h);
    void render(SDL_Texture* texture);
    void setOpacity(SDL_Texture* texture, int opacity);

    void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);

    void renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    void render( int x, int y, int w, int h, SDL_Texture* texture, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void render(std::vector<SDL_Texture*> texVec, SDL_Rect rect, double angle);
    void Show();
    void Quit();
private:
    SDL_Window* gWindow;
    SDL_Renderer* renderer;
};


#endif // RENDERWINDOW_H_INCLUDED
