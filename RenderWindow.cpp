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
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == nullptr) {
        printf("Window get error", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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

void RenderWindow::render( int x, int y, int w, int h, SDL_Texture* texture, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, w, h };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}

void RenderWindow::render(SDL_Texture* texture, SDL_Rect rect, double angle, int flip)
{
    if (flip == 0)
        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
    else if (flip == 1)
        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_VERTICAL);
}
void RenderWindow::render(SDL_Texture* texture, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void RenderWindow::render(SDL_Texture* texture, double x, double y, double w, double h)
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

void RenderWindow::render(SDL_Texture* texture, SDL_Rect dest, SDL_Rect rect, double angle, int flip)
{
    if (flip == 0)
        SDL_RenderCopyEx(renderer, texture, &dest, &rect, angle, nullptr, SDL_FLIP_NONE);
    else if (flip == 1)
        SDL_RenderCopyEx(renderer, texture, &dest, &rect, angle, nullptr, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(renderer, texture, &dest, &rect, angle, nullptr, SDL_FLIP_VERTICAL);
}

void RenderWindow::render(SDL_Texture* texture, SDL_Rect dest, SDL_Rect rect, double angle, int flip, double Ratio)
{
    dest.h *= Ratio;
    rect.h *= Ratio;
    if (flip == 0)
        SDL_RenderCopyEx(renderer, texture, &dest, &rect, angle, nullptr, SDL_FLIP_NONE);
    else if (flip == 1)
        SDL_RenderCopyEx(renderer, texture, &dest, &rect, angle, nullptr, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(renderer, texture, &dest, &rect, angle, nullptr, SDL_FLIP_VERTICAL);
}

void RenderWindow::render(std::vector<SDL_Texture*> texVec, SDL_Rect rect, double angle)
{
    for(auto e : texVec) {
        SDL_RenderCopyEx(renderer, e, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
//        SDL_Delay(100);
    }
}

void RenderWindow::render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h;

		SDL_Rect dst;
		dst.x = p_x;
		dst.y = p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
	 	SDL_DestroyTexture(message);
}

void RenderWindow::renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h;

		SDL_Rect dst;
		dst.x = SCREEN_WIDTH/2 - src.w/2 + p_x;
		dst.y = SCREEN_HEIGHT/2 - src.h/2 + p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
}

void RenderWindow::setOpacity(SDL_Texture* texture, int opacity)
{
    SDL_SetTextureAlphaMod(texture, opacity);
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
    TTF_Quit();
}

