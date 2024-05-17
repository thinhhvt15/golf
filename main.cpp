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
#include "Enemies.h"
#include "MenuGame.h"
#include "Tiles.h"
#include "gameMap.h"
#include "Timer.h"

using namespace std;

Settings settings;
RenderWindow window;
double Time = 0;
Ball* b;
Hole h;

bool init = (window.init() && window.createRenderer());
SDL_Texture* blackTex = window.loadTexture("black.png");
SDL_Texture* ballTex = window.loadTexture("ball.png");
SDL_Texture* settingTex = window.loadTexture("settingScreen.png");
SDL_Texture* buttonTex = window.loadTexture("button.png");
SDL_Texture* golfField = window.loadTexture("golfField.png");
SDL_Texture* hole = window.loadTexture("mainHole.png");
SDL_Texture* box = window.loadTexture("obstacle1.png");
SDL_Texture* mirror1 = window.loadTexture("mirror1.png");
SDL_Texture* mirror2 = window.loadTexture("mirror2.png");
SDL_Texture* mirrorCover = window.loadTexture("mirrorCover.png");
SDL_Texture* chaseEnemy = window.loadTexture("chaseEnemy.png");
SDL_Texture* startButton = window.loadTexture("startButton.png");
SDL_Texture* configButton = window.loadTexture("configButton.png");
SDL_Texture* menuScreen = window.loadTexture("Menu.png");
SDL_Texture* laserTex = window.loadTexture("laser.png");
SDL_Texture* skill_0Tex = window.loadTexture("circleBoom.png");
SDL_Texture* freezeTex = window.loadTexture("freeze.png");
SDL_Texture* bg_art = window.loadTexture("background.png");
SDL_Texture* intensityTex = window.loadTexture("intensity.png");

SDL_Texture* cross = window.loadTexture("cross.png");
SDL_Texture* blur = window.loadTexture("blur.png");
SDL_Texture* quitTex = window.loadTexture("Quit.png");
SDL_Texture* menuTex = window.loadTexture("MenuTex.png");
SDL_Texture* playTex = window.loadTexture("PlayButton.png");
SDL_Texture* healthBarTex = window.loadTexture("healthBar.png");
SDL_Texture* mapTiles = window.loadTexture("mapTile.png");
SDL_Texture* border = window.loadTexture("border.png");
SDL_Texture* configBarTex = window.loadTexture("configBar.png");
SDL_Texture* tryAgainTex = window.loadTexture("tryAgain.png");
SDL_Texture* backButton = window.loadTexture("backButton.png");
SDL_Texture* settingButton = window.loadTexture("settingButton.png");

TTF_Font* font48 = TTF_OpenFont("font.ttf", 48);
TTF_Font* font32 = TTF_OpenFont("font.ttf", 32);
TTF_Font* font16 = TTF_OpenFont("font.ttf", 16);
TTF_Font* font64 = TTF_OpenFont("font.ttf", 64);

SDL_Rect gTileClips[ TOTAL_TILES ];
Tile* tileSet[ 10000 ];
vector<SDL_Texture*> mirror;
vector<vector<SDL_Texture*>> obsTex;
vector<Obstacle*> obs, static_obs, effect_obs;
vector<Enemies*> enemeo;
vector<Enemies*> deadZombies;
vector<SDL_Texture*> zombie(4);
vector<SDL_Texture*> shockwaveTex(5);
vector<SDL_Texture*> simpleDead(5);
vector<SDL_Texture*> skill_Tex(5);

Mix_Chunk* skill0_sfx = Mix_LoadWAV("sfx/skill0.mp3");
Mix_Chunk* skill1_sfx = Mix_LoadWAV("sfx/skill1.mp3");
Mix_Music* music = Mix_LoadMUS("sfx/chill.mp3");
Mix_Music* bg_music = Mix_LoadMUS("sfx/backgroundMusic.mp3");

SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};
bool pauseState = 0;

vector<int> high_score;
int startPoint;
//GameMap game_map;
int prevState = -1;

mt19937 rng;
int ran(int l, int r)
{
    return l + (rng() % (r - l + 1));
}

void dieAnimation(Enemies* e)
{

}
bool check(int X, int Y, SDL_Rect cur)
{
    for (Enemies* e : enemeo) {
        if (mathFunc::checkCollision(e->getRect(), cur))
            return false;
    }

    return true;
}

bool setTiles( Tile* tiles[] )
{
	bool tilesLoaded = true;

    int x = 0, y = 0;

    std::ifstream map( "map.map" );

    if( map.fail() )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		for( int i = 0; i < MAX_TILES_Y; ++i )
		{
		    y = i * TILE_HEIGHT;
		    for (int j = 0; j < MAX_TILES_X; ++j) {
                int tileType = -1;

//                map >> tileType;
                tileType = 81;

                if( map.fail() )
                {
                    printf( "Error loading map: Unexpected end of file!\n" );
                    tilesLoaded = false;
                    break;
                }

                x = j * TILE_WIDTH;
                tiles[ i * MAX_TILES_X + j ] = new Tile( x, y, tileType );

		    }
		}

		if (tilesLoaded) {
            for (int i = 0; i < TOTAL_TILES; i++) {
                int r = i / 16, c = i - r * 16;
                gTileClips[i] = {c * TILE_WIDTH, r * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
            }
		}
	}

	map.close();
	return tilesLoaded;
}

void randomChaseEnemy(int width, int height, int posX, int posY)
{
    int maxEnemies = width * height / 400;
    int numEnemies = 1;

    int x = ran(posX, posX + width), y = ran(posY, posY + height);
//    Enemies* enem = new Enemies(x, y, 0);
//    enemeo.push_back(enem);

    SDL_Rect cur;

    while(--numEnemies) {
        do {
            x = ran(posX, posX + width);
            y = ran(posY, posY + height);
            cur = {x, y, 20, 20};
        }
        while(check(x, y, cur) == false);
        Enemies* enem = new Enemies(x, y, 0);
        enemeo.push_back(enem);
    }
}

double timer = 2000;
double initTime, curTime;
void spawnZombies(double& iniTime, double& curTime, int posX, int posY, int w, int h)
{
    if (curTime - iniTime >= timer) {
        int x, y;
        SDL_Rect cur;
//        do {
            x = ran(posX, posX + w);
            y = ran(posY, posY + h);
            cur = {x, y, 20, 20};
//        }
//        while(check(x, y, cur) == false);
        Enemies* enem = new Enemies(x, y, 0);
        enem->setNumSprite(3);
        enemeo.push_back(enem);
        iniTime = 0;
        timer -= 10;
    }
}

void levelOne()
{
    Vector2f curPos = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8};
    Vector2f curPos1 = {SCREEN_WIDTH / 4 * 3 - 35, SCREEN_HEIGHT / 8};
    Obstacle* mirror_1 = new Obstacle(Vector2f(SCREEN_WIDTH / 2 - 20, curPos1.y + 80), 0);
    h.setX(SCREEN_WIDTH / 2);
    h.setY(curPos1.y + 250);
    effect_obs.push_back(mirror_1);
    Obstacle* boxObs = new Obstacle(curPos);
    Obstacle* boxObs1 = new Obstacle(curPos1);
    static_obs.push_back(boxObs); static_obs.push_back(boxObs1);

    while(curPos.x + 50 < curPos1.x) {
        curPos.x += 50;
        boxObs = new Obstacle(curPos);
//        static_obs.push_back(boxObs);
    }

    curPos.x = SCREEN_WIDTH / 4;
    while(curPos.y <= SCREEN_HEIGHT / 2) {
        curPos.y += 50;
        boxObs = new Obstacle(curPos);
//        static_obs.push_back(boxObs);

        curPos1.y += 50;
        boxObs1 = new Obstacle(curPos1);
//        static_obs.push_back(boxObs1);
    }

    while(curPos.x + 50 < curPos1.x) {
        curPos.x += 50;
        boxObs = new Obstacle(curPos);
//        static_obs.push_back(boxObs);
    }
    Obstacle* mirror_2 = new Obstacle(Vector2f(SCREEN_WIDTH / 2 - 20, curPos1.y + 200), 0);
    mirror_2->setPar(0);
    mirror_1->setPar((int)effect_obs.size());
    effect_obs.push_back(mirror_2);
}

void levelTwo()
{
    Enemies* enem = new Enemies(100, 100, 0);
    enemeo.push_back(enem);
    enem = new Enemies(SCREEN_WIDTH - 100, 100, 0);
    enemeo.push_back(enem);
    enem = new Enemies(100, SCREEN_HEIGHT - 100, 0);
    enemeo.push_back(enem);
    enem = new Enemies(SCREEN_HEIGHT - 100, SCREEN_WIDTH - 100, 0);
    enemeo.push_back(enem);
}

void decreaseHP_Enemy(Enemies* e, int dec)
{
    e->setHP(e->getHP() - dec);
    if (e->getHP() <= 0) {
        e->setDead(1);
    }
}

bool skill_0 = 0, skill_2 = 0;
bool freeze = 0;
double initTimeFreeze = 0, initCBoom = 0, initThunder = 0;
bool isProtected = 0;

void Restart()
{
    b = new Ball;
    enemeo.clear();
}

void dieScreen()
{
    window.render(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, "YOU DIED", font64, black);

    SDL_Rect tryAgainRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 80, 80};
    SDL_Rect menuRect = {SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 + 20, 80, 80};
    window.render(tryAgainTex, tryAgainRect, 0, 0);
    window.render(menuTex, menuRect, 0, 0);

    bool mouseDown = 0;
    SDL_Event events;
    while(SDL_PollEvent(&events)) {
        switch(events.type) {
        case (SDL_MOUSEBUTTONDOWN):
            mouseDown = 1;
            break;
        }
    }

    if (mouseDown) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), tryAgainRect)) {
            Restart();
            state = GAMESTATE::START;
        }
        else if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), menuRect)) {
            state = GAMESTATE::MENU;
            Mix_PlayMusic(bg_music, -1);
        }
    }
}

void update()
{
    SDL_Event events;
    int mouseDown = 0, mousePressed = 0;
    bool inHole = 0;
    bool ingameStart = 0;

    while(SDL_PollEvent(&events)) {
        switch (events.type) {

        case SDL_MOUSEBUTTONDOWN:
            mouseDown = mousePressed = 1;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseDown = 0;
            break;

        case SDL_KEYDOWN:
            switch(events.key.keysym.sym) {
            case (SDLK_1):
                skill_0 = 1;
                break;

            case (SDLK_2):
                skill_1 = 1;
                break;

            case (SDLK_3):
                skill_2 = 1;
                break;

            case (SDLK_ESCAPE):
                if (state == GAMESTATE::START)
                    state = GAMESTATE::PAUSE;
            }
        }

        b->update(mouseDown, mousePressed, effect_obs, static_obs, tileSet);
    }

    SDL_Rect dir[4];
    dir[0] = {0, 0, 200, LEVEL_HEIGHT};
    dir[1] = {0, 0, LEVEL_WIDTH, 200};
    dir[2] = {LEVEL_WIDTH - 200, 0, 200, LEVEL_HEIGHT};
    dir[3] = {0, LEVEL_HEIGHT - 200, LEVEL_WIDTH, 200};

    int ranNum = ran(0, 3);


    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    b->setCamera(camera);
//    b->setCir(b->getX(), b->getY(), b->getW() / 2);
//    cout << b->getCir().r << "\n";

    if (b->ballClicked()) {
        ingameStart = 1;
        if (!startPoint)
            startPoint = SDL_GetTicks();
    }

    if (ingameStart) {
        if (!initTime)
            initTime = SDL_GetTicks();
        else {
            curTime = SDL_GetTicks();
    //        if (enemeo.size() == 0)
            spawnZombies(initTime, curTime, dir[ranNum].x, dir[ranNum].y, dir[ranNum].w, dir[ranNum].h);
        }
    }

    if (ingameStart) {
        for (Enemies* e : enemeo)
            e->update1(b, static_obs, effect_obs, enemeo, camera);
    }

    for( int i = 0; i < 3600; ++i )
    {
        SDL_Rect rect = {tileSet[i]->getBox().x - camera.x, tileSet[i]->getBox().y - camera.y, TILE_WIDTH, TILE_HEIGHT};
        window.render(mapTiles, gTileClips[tileSet[i]->getType()], rect, 0, 0);
    }

    if (b->isDead())
        isQuit = 1;

    if (h.inHole(b->getBallPosX(), b->getBallPosY()))
        inHole = 1;

    for (Obstacle* e : static_obs) {
        SDL_Rect rect = e->getRect();
        rect.x -= camera.x;
        rect.y -= camera.y;
        window.render(obsTex[e->getTypeObs()][e->getCurSprite()], rect, 0, 0);
        e->nextSprite();
    }

    if (skill_2) {
        b->useSkill_2(2);
        if (b->getSkill(2)) {
            Mix_PlayChannel(-1, skill1_sfx, 0);
            int d = 0;
            vector<pair<double, int>> getMinDis;
            for (Enemies* enem : enemeo)
                getMinDis.push_back({ mathFunc::distance(Vector2f(enem->getX(), enem->getY()), Vector2f(b->getX(), b->getY())), d++ });

            sort(getMinDis.begin(), getMinDis.end());
            for (int i = 0; i < min(4, (int)getMinDis.size()); i++) {
                if (getMinDis[i].first > 400 * 400) break;

                decreaseHP_Enemy(enemeo[getMinDis[i].second], 100);
                if (enemeo[getMinDis[i].second]->isDead()) {
                    enemeo[getMinDis[i].second]->setDieType(1);
                    enemeo[getMinDis[i].second]->setNumSprite(4);
                    enemeo[getMinDis[i].second]->setCurSprite(0);
                    deadZombies.push_back(enemeo[getMinDis[i].second]);
                }
            }
        }
        else
            skill_2 = 0;
    }

    if (skill_1) {
        b->useSkill_1(1);
        if (b->getSkill(1) == 0)
            skill_1 = 0;
    }

    for (int i = 0; i < (int)b->getAmmoList().size(); i++) {
        int mouseX, mouseY;
        if (skill_1)
            SDL_GetMouseState(&mouseX, &mouseY);

        AmmoObject* cur = b->getAmmoList().at(i);
        b->updateAmmo(cur, mouseX, mouseY);
        SDL_Rect rect = cur->getRect();

        for (Enemies* e : enemeo) {
            SDL_Rect enemy = e->getRect();
            enemy.x -= camera.x;
            enemy.y -= camera.y;
            if (mathFunc::checkCollision(rect, enemy)) {
                decreaseHP_Enemy(e, 100);
                deadZombies.push_back(e);
            }
        }
        window.render(laserTex, rect, cur->getAngle() + 90, 0);
    }

    for (Obstacle* e : effect_obs) {
        SDL_Rect rect = e->getRect();
        rect.x -= camera.x;
        rect.y -= camera.y;
        window.render(obsTex[e->getTypeObs()][e->getCurSprite()], rect, 0, 0);
        e->nextSprite();
    }

    int d = 0;
    b->setCir( b->getX() + b->getW() / 2, b->getY() + b->getH() / 2, b->getW() / 2 );
    for (Enemies* enem : enemeo) {
        Circle curCir = Circle( b->getX() + b->getW() / 2, b->getY() + b->getH() / 2, b->getSkill_r() );
        curCir.x += camera.x;
        curCir.y += camera.y;
        if ( mathFunc::checkCollision(curCir, enem->getRect()) && b->getSkill_r() > 0) {
            enem->setHP(enem->getHP() - 10);

            if (enem->getHP() <= 0) {
                enem->setDead(1);
                enem->setDieType(0);
                enem->setCurSprite(0);
                enem->setNumSprite(5);
                b->setSkill_r(0);
            }
        }
    }

    double ratioHP = b->getHP() * 1.0 / 100;

    SDL_Rect hpRect = {b->getX() - 30, b->getY() - 30, 80 * ratioHP, 10};
    window.render(healthBarTex, hpRect);

    if (skill_0) {
        b->useSkill_0(0);
        if (b->getSkill(0) == 0) {
            skill_0 = 0;
            if (b->getOther0() == 0)
                b->setOther0(SDL_GetTicks());
//            isProtected = 1;
        }
        else {
            Mix_PlayChannel(-1, skill0_sfx, 0);
        }
    }

//    if (skill_0 == 0 && b->getSkill(0) != 0) {
//        if (SDL_GetTicks() - b->getOther0() >= 2000) {
//            skill_0 = 1;
//            b->setOther0(0);
//            isProtected = 1;
//        }
//    }
//
//    if (skill_0)
//        isProtected = 0;


    if (b->getSkill(0) == 1) {
        int r = b->getSkill_r();
        SDL_Rect rect = {b->getBallPosX() + 8 - (25 + r) / 2, b->getBallPosY() + 8 - (25 + r) / 2, 25 + r, 25 + r};
        window.render(skill_0Tex, rect, 0, 0);
    }

    for (Enemies* e : enemeo) {
        if (b->isDead()) {
            state = GAMESTATE::DIED;
            break;
        }
        if (e == nullptr) continue;
        vector<Enemies*> copVec = enemeo;

        if (e->isDead()) {
            deadZombies.push_back(e);
            copVec.erase(copVec.begin() + d);
            enemeo = copVec;
//            delete e;
//            e = nullptr;
            continue;
        }

        SDL_Rect rect = e->getRect();
        rect.x -= camera.x;
        rect.y -= camera.y;

        window.render(zombie.at(e->getCurSprite()), rect, 0, e->getFlip());

        for (int i = 0; i < e->getAmmoList().size(); i++) {
            auto vec = e->getAmmoList();
            if (vec.empty()) break;
            rect = e->getAmmoList().at(i)->getRect();
            rect.x -= camera.x;
            rect.y -= camera.y;

            if (gameMode == 0 && SDL_GetTicks() - vec[i]->getInitAmmo() >= 500) {
                vec.erase(vec.begin() + i);
                e->setAmmoList(vec);
                continue;
            }
            else if (gameMode == 1 && SDL_GetTicks() - vec[i]->getInitAmmo() >= 1000) {
                vec.erase(vec.begin() + i);
                e->setAmmoList(vec);
                continue;
            }
            if (mathFunc::checkCollision(b->getRect(), rect)) {
                vec.erase(vec.begin() + i);
                e->setAmmoList(vec);
                if (!isProtected) {
                    b->setHP(b->getHP() - 10);
//                    cout << "1\n";
                }

                if (b->getHP() <= 0) {
                    b->setDead(1);
                    state = GAMESTATE::DIED;
                    high_score.push_back(SDL_GetTicks() - startPoint);
                    startPoint = 0;
                    break;
                }
            }
            else
                window.render(laserTex, rect, e->getAmmoList().at(i)->getAngle() + 90, 0);
        }

        d++;
    }

    d = 0;
    for (Enemies* e : deadZombies) {
        if (e->getDieType() == 1) {

//            cout << e->getCurSprite() << "\n";
            if (e->getInitAni() == 0)
                e->setInitAni(SDL_GetTicks());

            SDL_Rect rect = e->getRect();
            rect.x -= camera.x;
            rect.y -= camera.y;
            rect.w += 10;
            rect.h += 5;
//            cout << e->getCurSprite() << "\n";
            window.render(shockwaveTex[e->getCurSprite()], rect, 0, e->getFlip());

            if (e->getCurSprite() == 4) {
                e->setCurSprite(0);
                e->setDieType(0);
                e->setNumSprite(5);
                e->setInitAni(0);
                continue;
            }
            e->setCurSprite(int((SDL_GetTicks() - e->getInitAni()) * 3 / 1000) % 5);

        }
        d++;
    }

    d = 0;
    for (Enemies* e : deadZombies) {

        if (e->getDieType() == 0) {
            if (e->getInitAni() == 0)
                e->setInitAni(SDL_GetTicks());

            if (e->getCurSprite() >= 4) {
                auto vec = deadZombies;
                vec.erase(vec.begin() + d);
                deadZombies = vec;
                continue;
            }
            else {
                SDL_Rect rect = e->getRect();
                rect.x -= camera.x;
                rect.y -= camera.y;
                window.render(simpleDead[e->getCurSprite()], rect, 0, e->getFlip());
                e->setCurSprite(int((SDL_GetTicks() - e->getInitAni()) * 3 / 1000) % 5);
            }
        }
        d++;
    }

    SDL_Rect rect = {b->getBallPosX(), b->getBallPosY(), 17, 17};
    SDL_Rect dest = {0, 0, 17, 17};
    window.render(ballTex, dest, rect, b->getAngle() + 270, 0, b->getRatio());

    int x = 20;

    SDL_Rect configRect = {600, 0, 80, 80};
    window.render(settingButton, configRect, 0, 0);

    if (mouseDown) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), configRect)) {
            prevState = state;
            state = GAMESTATE::CONFIG;
        }

    }

    for (int i = 0; i < 3; i++) {
        string coolDownTime = to_string(b->getCoolDownTime(i) / 1000.0);
        int cnt = 0, j;
        bool ok = 0;
        for (j = 0; j < (int)coolDownTime.size(); j++) {
            if (cnt == 2) break;
            if (ok)
                cnt++;
            if (coolDownTime[j] == '.')
                ok = 1;
        }

        string str = coolDownTime.substr(0, j);

        double ratioCoolDown = b->getCoolDownTime(i) / b->getCoolDown(i);
        window.render(x += 100, SCREEN_HEIGHT - 30, str.c_str(), font16, white);
        SDL_Rect blurR = {x, SCREEN_HEIGHT - 80, 30 * ratioCoolDown, 30};
        SDL_Rect rect = {x, SCREEN_HEIGHT - 80, 30, 30};
        window.render(skill_Tex[i], rect, 0, 0);
        rect.x -= 3; rect.y -= 3;
        rect.w += 3; rect.h += 3;
        window.render(border, rect, 0, 0);
        window.render(blur, blurR, 0, 0);
    }

    b->updateCoolDown();
}

//int instate = 0;
//
//bool instruction1()
//{
//
//    SDL_Event events;
//
//    bool mouseDown = 0, mousePressed = 0;
//    while(SDL_PollEvent(&events)) {
//        switch (events.type) {
//
//        case SDL_MOUSEBUTTONDOWN:
//            mouseDown = mousePressed = 1;
//            break;
//
//        case SDL_MOUSEBUTTONUP:
//            mouseDown = 0;
//            break;
//
//        case SDL_KEYDOWN:
//            switch(events.key.keysym.sym) {
//            case (SDLK_1):
//                skill_0 = 1;
//                break;
//
//            case (SDLK_2):
//                skill_1 = 1;
//                break;
//
//            case (SDLK_3):
//                skill_2 = 1;
//                break;
//
//            case (SDLK_ESCAPE):
//                if (state == GAMESTATE::START)
//                    state = GAMESTATE::PAUSE;
//            }
//        }
//
//        b->update(1, 1, effect_obs, static_obs, tileSet);
//    }
//
//    window.render(500, 200, "Di chuyen qua bong nguoc huong con chuot");
//    window.render(600, 200, "Move the ball opposite the direction of the mouse");
//    window.render(0, 600, "SKIP", font32, white);
//    if (mouseDown) {
//        int mouseX, mouseY;
//        SDL_GetMouseState(&mouseX, &mouseY);
//
//        if (mouseX >= 500 && mouseY <= 200) {
//            instate++;
//            return 1;
//        }
//    }
//
//    return 0;
//}
//
//bool instruction2()
//{
//    SDL_Event events;
//
//    bool mouseDown = 0, mousePressed = 0;
//    bool skill_0 = 0, skill_1 = 0, skill_2 = 0;
//    while(SDL_PollEvent(&events)) {
//        switch (events.type) {
//
//        case SDL_MOUSEBUTTONDOWN:
//            mouseDown = mousePressed = 1;
//            break;
//
//        case SDL_MOUSEBUTTONUP:
//            mouseDown = 0;
//            break;
//
//        case SDL_KEYDOWN:
//            switch(events.key.keysym.sym) {
//            case (SDLK_1):
//                skill_0 = 1;
//                break;
//
//            case (SDLK_2):
//                skill_1 = 1;
//                break;
//
//            case (SDLK_3):
//                skill_2 = 1;
//                break;
//
//            case (SDLK_ESCAPE):
//                if (state == GAMESTATE::START)
//                    state = GAMESTATE::PAUSE;
//            }
//        }
//
//        b->update(1, 1, effect_obs, static_obs, tileSet);
//    }
//
//    window.render(500, 200, "An phim '1' de dung chieu thu nhat");
//    window.render(600, 200, "Press '1' to use skill 1");
//    window.render(0, 600, "SKIP", font32, white);
//    if (mouseDown) {
//        int mouseX, mouseY;
//        SDL_GetMouseState(&mouseX, &mouseY);
//
//        if (skill_0 && mouseX >= 500 && mouseY <= 200) {
//            instate++;
//            return 1;
//        }
//    }
//
//    return 0;
//}
//
//bool instruction3()
//{
//    SDL_Event events;
//
//    bool mouseDown = 0, mousePressed = 0;
//    bool skill_0 = 0, skill_1 = 0, skill_2 = 0;
//    while(SDL_PollEvent(&events)) {
//        switch (events.type) {
//
//        case SDL_MOUSEBUTTONDOWN:
//            mouseDown = mousePressed = 1;
//            break;
//
//        case SDL_MOUSEBUTTONUP:
//            mouseDown = 0;
//            break;
//
//        case SDL_KEYDOWN:
//            switch(events.key.keysym.sym) {
//            case (SDLK_1):
//                skill_0 = 1;
//                break;
//
//            case (SDLK_2):
//                skill_1 = 1;
//                break;
//
//            case (SDLK_3):
//                skill_2 = 1;
//                break;
//
//            case (SDLK_ESCAPE):
//                if (state == GAMESTATE::START)
//                    state = GAMESTATE::PAUSE;
//            }
//        }
//
//        b->update(1, 1, effect_obs, static_obs, tileSet);
//    }
//
//    window.render(500, 200, "An phim '2' de dung chieu thu hai");
//    window.render(600, 200, "Press '2' to use skill 2");
//    window.render(0, 600, "SKIP", font32, white);
//    if (mouseDown) {
//        int mouseX, mouseY;
//        SDL_GetMouseState(&mouseX, &mouseY);
//
//        if (skill_1 && mouseX >= 500 && mouseY <= 200) {
//            instate++;
//            return 1;
//        }
//    }
//
//    return 0;
//}
//
//Enemies* e = new Enemies(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
//
//bool instruction3()
//{
//    SDL_Event events;
//
//    bool mouseDown = 0, mousePressed = 0;
//    bool skill_0 = 0, skill_1 = 0, skill_2 = 0;
//    while(SDL_PollEvent(&events)) {
//        switch (events.type) {
//
//        case SDL_MOUSEBUTTONDOWN:
//            mouseDown = mousePressed = 1;
//            break;
//
//        case SDL_MOUSEBUTTONUP:
//            mouseDown = 0;
//            break;
//
//        case SDL_KEYDOWN:
//            switch(events.key.keysym.sym) {
//            case (SDLK_1):
//                skill_0 = 1;
//                break;
//
//            case (SDLK_2):
//                skill_1 = 1;
//                break;
//
//            case (SDLK_3):
//                skill_2 = 1;
//                break;
//
//            case (SDLK_ESCAPE):
//                if (state == GAMESTATE::START)
//                    state = GAMESTATE::PAUSE;
//            }
//        }
//
//        b->update(1, 1, effect_obs, static_obs, tileSet);
//    }
//
//    if (skill_2) {
//        b->useSkill_2(2);
//        Mix_PlayChannel(-1, skill1_sfx, 0);
//
//            decreaseHP_Enemy(e, 100);
//            if (e->isDead()) {
//                e->setDieType(1);
//                e->setNumSprite(4);
//                e->setCurSprite(0);
//                deadZombies.push_back(enemeo[getMinDis[i].second]);
//            }
//        }
//        else
//            skill_2 = 0;
//    }
//    window.render(500, 200, "An phim '3' de dung chieu thu ba");
//    window.render(600, 200, "Press '3' to use skill 3");
//    window.render(0, 600, "SKIP", font32, white);
//    if (mouseDown) {
//        int mouseX, mouseY;
//        SDL_GetMouseState(&mouseX, &mouseY);
//
//        if (skill_2 && mouseX >= 500 && mouseY <= 200) {
//            instate++;
//            return 1;
//        }
//    }
//
//    return 0;
//}
//
//bool instructionScreen()
//{
//
//    b = new Ball;
//    b->setX(SCREEN_WIDTH / 2);
//    b->setY(SCREEN_HEIGHT / 2);
//    for( int i = 0; i < 3600; ++i )
//    {
//        SDL_Rect rect = {tileSet[i]->getBox().x - camera.x, tileSet[i]->getBox().y - camera.y, TILE_WIDTH, TILE_HEIGHT};
//        window.render(mapTiles, gTileClips[tileSet[i]->getType()], rect, 0, 0);
//    }
//
//    window.render(ballTex, b->getRect(), 0, 0);
//
//    if (instate == 0)
//        while(!instruction1());
//
//    else if (instate == 1)
//        while(!instruction2());
//    else if (instate == 2)
//        while(!instruction3());
//    else {
//        return 0;
//    }
//
//    return 1;
//}


void instructionScreen()
{
    window.render(blackTex, 0, 0, 750, 750);
    window.render(skill_Tex[0], 120, 200, 100, 100);
    window.render(120 + 100, 200, "Kich hoat mot qua cau nang luong xoay quanh qua bong de giet chet ke dich", font32, white);
    window.render(laserTex, 120, 400, 100, 100);
    window.render(120 + 100, 400, "Ban mot vien dan xuyen qua ke dich", font32, white);
    window.render(skill_Tex[2], 120, 600, 100, 100);
    window.render(120 + 100, 600, "Giat chet 4 ke dich gan nhat", font32, white);
    SDL_Rect backRect = {0, 0, 100, 50};
    window.render(backButton, 0, 0, 100, 50);

    SDL_Event events;
    while(SDL_PollEvent(&events)) {
        if (events.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), backRect)) {
//                prevState = GAMESTATE::INS;
                state = prevState;
            }
        }
    }
}
void pauseScreen()
{
    SDL_Rect menuRect = {SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 60, 120, 120};
    SDL_Rect quitRect = {menuRect.x - 60 * 3, menuRect.y, 120, 120};
    SDL_Rect playRect = {menuRect.x + 60 * 3, menuRect.y, 120, 120};
    SDL_Rect settingRect = {0, 600, 80, 80};
    SDL_Event events;
    SDL_Rect blurRect = {0, 0, 750, 750};
    window.render(blur, blurRect);
    window.render(menuTex, menuRect);
    window.render(quitTex, quitRect);
    window.render(playTex, playRect);

    while(SDL_PollEvent(&events)) {
        switch (events.type) {
        case (SDL_KEYDOWN):
            if (events.key.keysym.sym == SDLK_ESCAPE) {
                state = GAMESTATE::START;
                return;
            }
            break;

        case (SDL_MOUSEBUTTONDOWN):
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            Vector2f Point = Vector2f(mouseX, mouseY);
            if (mathFunc::checkPointInside(Point, menuRect))
                state = GAMESTATE::MENU;
            else if (mathFunc::checkPointInside(Point, quitRect))
                state = GAMESTATE::QUIT;
            else if (mathFunc::checkPointInside(Point, playRect))
                state = GAMESTATE::START;
            else if (mathFunc::checkPointInside(Point, settingRect))
                state = GAMESTATE::CONFIG;
        }
    }
}

void menu_Screen()
{
//    Mix_Reserve

    bool isQuit = 0;
    SDL_Event events;
    bool mouseDown = 0;
    while(SDL_PollEvent(&events)) {
        switch(events.type) {
        case SDL_QUIT:
            isQuit = 1;
        case SDL_MOUSEBUTTONDOWN:
            mouseDown = 1;
        }
    }

//    SDL_Rect startRect;
//    startRect.w = 200;
//    startRect.h = 92;
//    startRect.x = (SCREEN_WIDTH - startRect.w) / 2;
//    startRect.y = (SCREEN_HEIGHT - startRect.h) / 2 - 100;
//    SDL_Rect configRect = startRect;
//    configRect.y += 200;
    SDL_Rect menuRect = {0, 0, 750, 750};
    SDL_Rect startRect = {(750 - 200) / 2, 750 / 2 - 100, 200, 92};
    SDL_Rect configRect = {startRect.x, startRect.y + 130, 200, 92};

    SDL_Rect insRect = {50, 450, 200, 100};

    window.render(menuScreen, menuRect, 0, 0);
    window.render(startButton, startRect, 0, 0);
    window.render(configButton, configRect, 0, 0);

    window.render(200, 100, "ZOMBIE KILLER", font64, white);
    window.render(50, 450, "INSTRUCTION", font48, white);
    window.render(200, 600, "High Score: ", font48, white);
    sort(high_score.rbegin(), high_score.rend());

    if (high_score.size()) {
        string highStr = to_string(high_score[0]);
        window.render(400, 650, highStr.c_str(), font48, white);
    }

    if (mouseDown) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), startRect)) {
            state = GAMESTATE::START;
            Mix_PlayMusic(music, -1);
        }

        if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), configRect)) {
            prevState = GAMESTATE::MENU;
            state = GAMESTATE::CONFIG;
//            Mix_PlayMusic(bg_music, -1);
        }

        if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), insRect)) {
            prevState = GAMESTATE::MENU;
            state = GAMESTATE::Itr;
        }
    }
}

double RatioMusic = 1, RatioSFX = 1, RatioMode = 0;
void configScreen()
{
    SDL_Rect blurRect = {0, 0, 750, 750};
    window.render(blur, blurRect, 0, 0);
    window.render(SCREEN_WIDTH / 2 - 70, 80, "SETTINGS", font48, white);
    window.render(120, 200, "Music", font32, white);

    SDL_Rect configBar1 = {240, 200, 375, 28};
    window.render(configBarTex, configBar1, 0, 0);

    SDL_Rect configBar2 = configBar1;
    configBar2.y += 100;
    window.render(120, 300, "SFX", font32, white);
    window.render(configBarTex, configBar2, 0, 0);

    SDL_Rect configBar3 = configBar2;
    configBar3.y += 100;
    window.render(120, 400, "MODE", font32, white);
    window.render(configBarTex, configBar3, 0, 0);

    SDL_Rect backRect = {0, 0, 100, 50};
    window.render(backButton, backRect, 0, 0);

    window.render(configBar1.x, configBar3.y + 40, "EASY", font16, white);
    window.render(configBar1.x + 155, configBar3.y + 40, "MEDIUM", font16, white);
    window.render(configBar3.x + 355, configBar3.y + 40, "HARD", font16, white);

    bool mouseDown = 0, mousePressed = 0;
    SDL_Event events;
    while(SDL_PollEvent(&events)) {
        switch(events.type) {
        case (SDL_MOUSEBUTTONDOWN):
            mouseDown = 1;
        case (SDL_MOUSEBUTTONUP):
            mousePressed = 1;
        }
    }

    SDL_Rect inMusicTex = {configBar1.x + 5, configBar1.y + 5, 364, 20};
    SDL_Rect inMusicDest = {0, 0, 364, 20};

    SDL_Rect inSFXTex = {configBar2.x + 5, configBar2.y + 5, 364, 20};
    SDL_Rect inSFXDest = {0, 0, 364, 20};

    SDL_Rect inModeTex = {configBar3.x + 5, configBar3.y + 5, 364, 20};
    SDL_Rect inModeDest = {0, 0, 364, 20};

    if (mouseDown || mousePressed) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), backRect)) {
            state = prevState;
        }
        else
        if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), configBar1)) {
            RatioMusic = (mouseX - 240) * 1.0 / configBar1.w;
            Mix_VolumeMusic(128 * RatioMusic);
//            cout << (128 * RatioMusic) << "\n";
        }
        else
        if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), configBar2)) {
            RatioSFX = (mouseX - 240) * 1.0 / configBar2.w;
            Mix_VolumeChunk(skill0_sfx, 128 * RatioSFX);
            Mix_VolumeChunk(skill1_sfx, 128 * RatioSFX);
        }
        else if (mathFunc::checkPointInside(Vector2f(mouseX, mouseY), configBar3)) {
            double curRatio = (mouseX - 240) * 1.0 / configBar3.w;
            RatioMode = (curRatio <= 0.25 ? 0 : (curRatio <= 0.5 ? 0.5 : (curRatio <= 0.75 ? 0.5 : 1)));
        }
    }

    inMusicDest.w *= 1.0 * RatioMusic;
    inMusicTex.w *=  1.0 * RatioMusic;

    inSFXDest.w *= 1.0 * RatioSFX;
    inSFXTex.w *= 1.0 * RatioSFX;

    inModeDest.w *= 1.0 * RatioMode;
    inModeTex.w *= 1.0 * RatioMode;

    if (RatioMode == 0) gameMode = GAMEMODE::EASY;
    else if (RatioMode == 0.5) gameMode = GAMEMODE::MEDIUM;
    else gameMode = GAMEMODE::HARD;

    window.render(intensityTex, inMusicDest, inMusicTex);
    window.render(intensityTex, inSFXDest, inSFXTex);
    window.render(intensityTex, inModeDest, inModeTex);
}

void graphics()
{

    window.Show();
}

void game()
{

    while(state != GAMESTATE::QUIT) {
        switch(state) {
        case (GAMESTATE::START):
            update();
            break;

        case (GAMESTATE::CONFIG):
            configScreen();
            break;

        case (GAMESTATE::MENU):
            menu_Screen();
            break;

        case (GAMESTATE::PAUSE):
            pauseScreen();
            break;

        case (GAMESTATE::DIED):
            dieScreen();
            break;

        case (Itr):
            instructionScreen();
            break;
        }

        graphics();
    }


//        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
//        if( avgFPS > 2000000 )
//        {
//            avgFPS = 0;
//        }
//
//        ++countedFrames;
//        cout << avgFPS << "\n";

}

int main(int argc, char* argv[])
{
    srand(time(nullptr));

    Mix_PlayMusic(bg_music, -1);
    if (skill0_sfx == nullptr) {
        printf("%s\n",Mix_GetError());
        return 0;
    }

    if( !setTiles( tileSet ) )
	{
		printf( "Failed to load tile set!\n" );
		return 0;
	}

    b = new Ball;

    zombie[0] = window.loadTexture("zombie1.png");
    zombie[1] = window.loadTexture("zombie2.png");
    zombie[2] = window.loadTexture("zombie3.png");
    zombie[3] = window.loadTexture("zombie4.png");
    shockwaveTex[0] = window.loadTexture("shockwave1.png");
    shockwaveTex[1] = window.loadTexture("shockwave2.png");
    shockwaveTex[2] = window.loadTexture("shockwave1.png");
    shockwaveTex[3] = window.loadTexture("shockwave2.png");
    shockwaveTex[4] = window.loadTexture("shockwave1.png");

    simpleDead[0] = window.loadTexture("simpleDie1.png");
    simpleDead[1] = window.loadTexture("simpleDie2.png");
    simpleDead[2] = window.loadTexture("simpleDie3.png");
    simpleDead[3] = window.loadTexture("simpleDie4.png");
    simpleDead[4] = window.loadTexture("simpleDie5.png");

    skill_Tex[0] = window.loadTexture("skill0.png");
    skill_Tex[2] = window.loadTexture("shockwave2.png");

    window.setOpacity(bg_art, 25);
    mirror = {mirror1, mirror2};
    obsTex.push_back(vector<SDL_Texture*> {box});
    obsTex.push_back(mirror);
//    randomObstacles();
//    randomChaseEnemy(100, 100, 20, 20);
    levelOne();
//    levelTwo();

    game();

//    settingScreen();
    window.Quit();

    return 0;
}
