#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <bits/stdc++.h>
#include "Common_Function.h"
#include "Settings.h"
#include "RenderWindow.h"
#include "Ball.h"
#include "Hole.h"
#include "Obstacle.h"
#include "Ellipse.h"

using namespace std;

bool gameIsRunning = 1;
Settings settings;
RenderWindow window;
float currentTime = 0, initialTime = 0;
float Time = 0;
Ball* b;
Hole h;
SDL_Texture* ballTex = nullptr;
SDL_Texture* settingTex = nullptr;
SDL_Texture* buttonTex = nullptr;
SDL_Texture* golfField = nullptr;
SDL_Texture* hole = nullptr;
SDL_Texture* box = nullptr;
SDL_Texture* mirror1 = nullptr;
SDL_Texture* mirror2 = nullptr;
SDL_Texture* mirrorCover = nullptr;
vector<SDL_Texture*> mirror;
vector<vector<SDL_Texture*>> obsTex;
vector<Obstacle*> obs, level1, level2, level3;

mt19937 rng;
int ran(int l, int r)
{
    return l + (rng() % (r - l + 1));
}

void randomObstacles()
{
    int numObs = ran(1, 20);
    for (int i = 1; i <= numObs; i++) {
        int type = ran(0, 1);
        int x = ran(0, 400);
        int y = ran(0, 700);

        Obstacle* cur_obs = new Obstacle(Vector2f(x, y));
        obs.push_back(cur_obs);
    }


//    for (int i = 0; i < numObs; i++) {
//        for (int j = i + 1; j < numObs; j++)
//            if (obs[i]->checkCollision(obs[j]))
//    }

}

void levelOne()
{
    Vector2f curPos = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3};
    Vector2f curPos1 = {SCREEN_WIDTH / 4 * 3 - 35, SCREEN_HEIGHT / 3};
    Obstacle* a_mirror = new Obstacle(Vector2f(SCREEN_WIDTH / 2 - 20, curPos1.y), 0);
    level1.push_back(a_mirror);
    Obstacle* boxObs = new Obstacle(curPos);
    Obstacle* boxObs1 = new Obstacle(curPos1);
    level1.push_back(boxObs); level1.push_back(boxObs1);
    while(curPos.y <= SCREEN_HEIGHT / 3 * 2) {
        curPos.y += 50;
        boxObs = new Obstacle(curPos);
        level1.push_back(boxObs);

        curPos1.y += 50;
        boxObs1 = new Obstacle(curPos1);
        level1.push_back(boxObs1);
    }

}

void update()
{
    SDL_Event events;
    bool isQuit = 0;
    int mouseDown = 0, mousePressed = 0;
    bool inHole = 0;
    b = new Ball;

    while(!isQuit) {
        while(SDL_PollEvent(&events)) {
            switch (events.type) {
            case SDL_QUIT:
                isQuit = 1;

            case SDL_MOUSEBUTTONDOWN:
                mouseDown = mousePressed = 1;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseDown = 0;
                break;
            }

            b -> update(mouseDown, mousePressed, level1);
        }

        if (h.inHole(b -> getBallPosX(), b -> getBallPosY()))
            inHole = 1;

        if (!inHole) {
            SDL_Rect rect = {b -> getBallPosX(), b -> getBallPosY(), 17, 17};
            window.render(ballTex, rect);

            window.render(hole, h.getX(), h.getY(), 20, 20);
        }
        else {
            inHole = 0;
            b = new Ball;
        }

        for (Obstacle* e : level1) {
//            cout << e->getTypeObs() << "\n";
            window.render(obsTex[e->getTypeObs()][e->getCurSprite()], e->getRect(), 0);
//            if (e->getTypeObs()==0)
//                cout << e->getRect().x << " " << e->getRect().y <<"\n";
            e->nextSprite();
        }

        window.Show();

//        SDL_Rect bg_rect = {(SCREEN_WIDTH - 450) / 2, 0, 450, 750};
        window.render(golfField);
    }

}

void settingScreen()
{
//    cout << (settings.getScreen() != nullptr);
    SDL_Rect rect = {(SCREEN_WIDTH - 997) / 2, 0, 997, 1004};
    window.render(settingTex, rect);
    window.render(buttonTex, settings.getRect());
    window.Show();

    bool mouseDown = 0, mousePressed = 0;
    bool isQuit = 0;
    SDL_Event events;
    while(!isQuit) {
        while(SDL_PollEvent(&events)) {

            switch (events.type) {
            case SDL_QUIT:
                isQuit = 1;

            case SDL_MOUSEBUTTONDOWN:
                mouseDown = mousePressed = 1;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseDown = 0;

            }

            settings.setMouse(mouseDown, mousePressed);
        }

        window.render(buttonTex, settings.getRect());
        window.Show();

        SDL_Rect rect = {(SCREEN_WIDTH - 997) / 2, 0, 997, 1004};
        window.render(settingTex, rect);
//        window.Show();
    }
}

int main(int argc, char* argv[])
{
    if (!window.init()) return 0;
    if (!window.createRenderer()) return 0;

    ballTex = window.loadTexture("ball.png");
    settingTex = window.loadTexture("settingScreen.png");
    buttonTex = window.loadTexture("button.png");
    golfField = window.loadTexture("golfField.png");
    hole = window.loadTexture("mainHole.png");
    box = window.loadTexture("obstacle1.png");
    mirror1 = window.loadTexture("mirror1.png");
    mirror2 = window.loadTexture("mirror2.png");
    mirrorCover = window.loadTexture("mirrorCover.png");
    mirror = {mirror1, mirror2};
    obsTex.push_back(vector<SDL_Texture*> {box});
    obsTex.push_back(mirror);
//    randomObstacles();

    levelOne();

    update();
//    settingScreen();
    window.Quit();

    return 0;
}
