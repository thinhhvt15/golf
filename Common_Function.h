#ifndef Common_Function
#define Common_Function

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

static const char* WINDOW_TITLE = "SDLON";
const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 750;

const int TOTAL_TILES = 176;
const int TOTAL_TILE_SPRITES = 12;
const int LEVEL_WIDTH = 1920;
const int LEVEL_HEIGHT = 1920;

const int MAX_TILES_Y = 60;
const int MAX_TILES_X = 60;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int FRAMES = 16;

extern bool gameIsRunning;
extern bool gameMenu;
extern bool gameConfig;
extern bool gameStart;
extern bool gameEnd;
extern bool startPressed;
extern bool isQuit;
extern bool skill_1;
extern SDL_Rect camera;
extern int state;
extern int gameMode;

enum GAMESTATE
{
    MENU = 0,
    START = 1,
    CONFIG = 2,
    PAUSE = 3,
    QUIT = 4,
    DIED = 5,
    Itr = 6
};

enum GAMEMODE
{
    EASY = 0,
    MEDIUM = 1,
    HARD = 2
};
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

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

typedef struct Map
{
    int start_x_, start_y_;
    int max_x_, max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};
#endif // Common_Function
