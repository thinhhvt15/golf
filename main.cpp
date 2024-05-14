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

SDL_Texture* cross = window.loadTexture("cross.png");
SDL_Texture* blur = window.loadTexture("blur.png");
SDL_Texture* quitTex = window.loadTexture("Quit.png");
SDL_Texture* menuTex = window.loadTexture("MenuTex.png");
SDL_Texture* playTex = window.loadTexture("PlayButton.png");
SDL_Texture* healthBarTex = window.loadTexture("healthBar.png");
SDL_Texture* mapTiles = window.loadTexture("mapTile.png");

TTF_Font* font32 = TTF_OpenFont("font.ttf", 32);
TTF_Font* font16 = TTF_OpenFont("font.ttf", 16);

SDL_Rect gTileClips[ TOTAL_TILES ];
Tile* tileSet[ 2000 ];
vector<SDL_Texture*> mirror;
vector<vector<SDL_Texture*>> obsTex;
vector<Obstacle*> obs, static_obs, effect_obs;
vector<Enemies*> enemeo;
vector<Enemies*> deadZombies;
vector<SDL_Texture*> zombie(4);
vector<SDL_Texture*> shockwaveTex(5);
vector<SDL_Texture*> simpleDead(5);
MENUu menuS;

SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};
bool pauseState = 0;
//GameMap game_map;

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

                map >> tileType;
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

bool skill_0 = 0, skill_2;
bool freeze = 0;
double initTimeFreeze = 0, initCBoom = 0, initThunder = 0;
bool isProtected = 0;

void update()
{
    SDL_Event events;
    int mouseDown = 0, mousePressed = 0;
    bool inHole = 0;
    bool ingameStart = 0;
    double initTime, curTime;

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

            case (SDLK_f):
                freeze = 1;
                initTimeFreeze = SDL_GetTicks();
                break;

            case (SDLK_2):
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

    if (!initTime)
        initTime = SDL_GetTicks();
    else {
        curTime = SDL_GetTicks();
//        if (enemeo.size() == 0)
        spawnZombies(initTime, curTime, dir[ranNum].x, dir[ranNum].y, dir[ranNum].w, dir[ranNum].h);
    }

    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    b->setCamera(camera);
//    b->setCir(b->getX(), b->getY(), b->getW() / 2);
//    cout << b->getCir().r << "\n";

    if (b->ballClicked())
        ingameStart = 1;

    if (ingameStart) {
        for (Enemies* e : enemeo)
            e->update1(b, static_obs, effect_obs, enemeo, camera);
    }

    for( int i = 0; i < 1600; ++i )
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

    if (freeze) {
        SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        window.render(freezeTex, rect, 0, 0);
        b->useSkill_1(initTimeFreeze, 1);
        if (b->getSkill(1) == 0)
            freeze = 0;
    }

    if (skill_2) {
        b->useSkill_2(2);
        if (b->getSkill(2)) {
            int d = 0;
            vector<pair<double, int>> getMinDis;
            for (Enemies* enem : enemeo)
                getMinDis.push_back({ mathFunc::distance(Vector2f(enem->getX(), enem->getY()), Vector2f(b->getX(), b->getY())), d++ });

            sort(getMinDis.begin(), getMinDis.end());
            for (int i = 0; i < min(4, (int)getMinDis.size()); i++) {
                if (getMinDis[i].first > 400 * 400) break;
                enemeo[getMinDis[i].second]->setDead(1);
                enemeo[getMinDis[i].second]->setDieType(1);
                enemeo[getMinDis[i].second]->setNumSprite(4);
                enemeo[getMinDis[i].second]->setCurSprite(0);
            }
        }
        else
            skill_2 = 0;
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
            enem->setDead(1);
            enem->setDieType(0);
            enem->setCurSprite(0);
            enem->setNumSprite(5);
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
        if (b->isDead())
            break;

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

        if (mathFunc::distance(e->getPos(), b->getPos()) <= 50 * 50)
            cout << "";

        window.render(zombie.at(e->getCurSprite()), rect, 0, e->getFlip());

        for (int i = 0; i < e->getAmmoList().size(); i++) {
            auto vec = e->getAmmoList();
            if (vec.empty()) break;
            rect = e->getAmmoList().at(i)->getRect();
            rect.x -= camera.x;
            rect.y -= camera.y;
            if (mathFunc::checkCollision(b->getRect(), rect)) {
                vec.erase(vec.begin() + i);
                e->setAmmoList(vec);
                if (!isProtected) {
                    b->setHP(b->getHP() - 10);
//                    cout << "1\n";
                }

                if (b->getHP() <= 0) {
                    b->setDead(1);
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

    for (int i = 0; i < 3; i++) {
//        cout << b->getCoolDownTime(i) << "\n"
//        window.renderCenter(x, SCREEN_HEIGHT - 30, "1", font16, black);
        string coolDownTime = to_string(b->getCoolDownTime(i) / 1000.0);
//        cout << coolDownTime << "\n";
        int cnt = 0, j;
        bool ok = 0;
        for (j = 0; j < (int)coolDownTime.size(); j++) {
            if (cnt == 2) break;
            if (ok)
                cnt++;
            if (coolDownTime[j] == '.')
                ok = 1;
        }

//        cout << coolDownTime << "\n";
        string str = coolDownTime.substr(0, j);
//        cout << str << "\n";
        window.render(x += 100, SCREEN_HEIGHT - 30, str.c_str(), font16, white);
    }

    window.Show();
    b->updateCoolDown();
}

void pauseScreen()
{
    SDL_Event events;
    while(SDL_PollEvent(&events)) {
        switch (events.type) {
        case (SDL_KEYDOWN):
            if (events.key.keysym.sym == SDLK_ESCAPE) {
                state = GAMESTATE::START;
                return;
            }
        }
    }
    SDL_Rect menuRect = {SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 60, 120, 120};
    SDL_Rect quitRect = {menuRect.x - 60 * 3, menuRect.y, 120, 120};
    SDL_Rect playRect = {menuRect.x + 60 * 3, menuRect.y, 120, 120};

    SDL_Rect blurRect = {0, 0, 750, 750};
    window.render(blur, blurRect);
    window.render(menuTex, menuRect);
    window.render(quitTex, quitRect);
    window.render(playTex, playRect);

    window.Show();


}

void settingScreen()
{
//    SDL_Rect
    ;
}

void menu_Screen()
{
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

        menuS.update(mouseDown);
    }
}

void graphics()
{
    SDL_Rect menuRect = {0, 0, 750, 750};
    SDL_Rect startRect = {(750 - 200) / 2, 750 / 2 - 100, 200, 92};
    SDL_Rect configRect = {startRect.x, startRect.y + 130, 200, 92};

    if (state == GAMESTATE::MENU) {
        window.render(menuScreen, menuRect, 0, 0);
        window.render(startButton, startRect, 0, 0);
        window.render(configButton, configRect, 0, 0);
    }

    if (state == GAMESTATE::CONFIG) {
        window.render(buttonTex, settings.getRect());
        SDL_Rect rect = {0, 0, 600, 600};
        window.render(settingTex, rect, 0, 0);
    }

    window.Show();
}

void game()
{

    while(!isQuit) {
        switch(state) {
        case (GAMESTATE::START):
            update();
            break;

        case (GAMESTATE::CONFIG):
            settingScreen();
            break;

        case (GAMESTATE::MENU):
            menu_Screen();
            break;

        case (GAMESTATE::PAUSE):
            pauseScreen();
            break;
        }

        if (state != GAMESTATE::START)
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
//    if (!window.init()) return 0;
//    if (!window.createRenderer()) return 0;

//    window.render(0, 240, "LEFT CLICK TO START", font32, white);
//    window.Show();
//    SDL_Delay(5000);
//    return 0;
    if( !setTiles( tileSet ) )
	{
		printf( "Failed to load tile set!\n" );
		return 0;
	}

	window.renderCenter(20, SCREEN_HEIGHT - 40, "1000000000", font16, white);
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

    window.setOpacity(bg_art, 25);
    mirror = {mirror1, mirror2};
    obsTex.push_back(vector<SDL_Texture*> {box});
    obsTex.push_back(mirror);
//    randomObstacles();
//    randomChaseEnemy(100, 100, 20, 20);
    levelOne();
//    levelTwo();

    game();

    settingScreen();
    window.Quit();

    return 0;
}
