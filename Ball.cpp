#include "Ball.h"

//bool touchesWall( SDL_Rect box, Tile* tiles[] )
//{
//    //Go through the tiles
//    for( int i = 0; i < TOTAL_TILES; ++i )
//    {
//        //If the tile is a wall type tile
//        if( ( tiles[ i ]->getType() >= TILE_CENTER ) && ( tiles[ i ]->getType() <= TILE_TOPLEFT ) )
//        {
//            //If the collision box touches the wall tile
//            if( checkCollision( box, tiles[ i ]->getBox() ) )
//            {
//                return true;
//            }
//        }
//    }
//
//    //If no wall tiles were touched
//    return false;
//}

Ball::Ball()
{
    pos = Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100);
    scale = Vector2f(17.f, 17.f);
    r = scale.x / 2.f;
    cir = {pos.x, pos.y, r};
    ball = nullptr;
    hole = nullptr;
    ball_clicked = 0;
    dead = 0;
    initialTime = 0;
    currentTime = 0;
}

bool Ball::checkSquareCollision(Obstacle* squareObs)
{
    bool ok = 1;
    if (getBallPosX() + getW() <= squareObs->getX()) ok = 0;
    if (getBallPosX() >= squareObs->getX() + squareObs->getW()) ok = 0;
    if (getBallPosY() + getH() <= squareObs->getY()) ok = 0;
    if (getBallPosY() >= squareObs->getY() + squareObs->getH()) ok = 0;

    if (ok) return 1;

    return 0;
}

bool Ball::checkCircleCollision(Obstacle* circleObs)
{
    Vector2f i1(circleObs->getX() + circleObs->getW() / 2.f, circleObs->getY() + circleObs->getH() / 2.f);
    Vector2f i2(pos.x + scale.x / 2.f, pos.y + scale.y / 2.f);

    if ( (r + circleObs->get_r()) * (r + circleObs->get_r()) > (i1.x - i2.x) * (i1.x - i2.x) + (i1.y - i2.y) * (i1.y - i2.y) )
        return 1;

    return 0;
}
bool Ball::checkCollision(std::vector<Obstacle*>& obs)
{
    bool ok = 1;
    for (Obstacle* e : obs) {
        if (e->getTypeObs() == 0) {
            if (checkSquareCollision(e)) return 1;
        }
        else if (e->getTypeObs() == 2) {
            if (checkCircleCollision(e)) return 1;
        }
    }

    return 0;
}

void Ball::handleMirror(Obstacle* e)
{

//
//            Linear i12(i2, Vector2f(i2.x + velocityX, i2.y + velocityY)); // duong thang qua vi tri bong cu va moi
//            Linear iO(velocityX, velocityY, i1); // duong thang qua tam guong vuong goc voi dt tren
//
//            Vector2f intersect = findIntersection(i12, iO); // giao diem
//            Vector2f vecMid = Vector2f(1, iO.A * (i1.x + 1) + iO.B - i1.y);
//            Vector2f vec1 = Vector2f(i2.x - i1.x, i2.y - i1.y);
//            Vector2f vec2 = Vector2f(i2.x + velocityX - i1.x, i2.y + velocityY - i1.y);
//
//            int sign = getSign(dot(vecMid, vec1));
//
//            float b = (i2.x - iO.A * iO.B + iO.A * i2.y);
//            float a = 1 + iO.A * iO.A;
//            float c = i2.x * i2.x + iO.B * iO.B + i2.y * i2.y - SDL_powf(scale.x / 2.f, 2) - 2 * iO.B * i2.y;
//
//            if (b != b || a != a || c != c) {
//                ok = 0;
//                continue;
//            }
//
//            std::cout << b << " " << a << " " << c << "\n";
//            float delta = b * b - a * c;
//
//            if (delta <= 0) {
//                ok = 0;
//                continue;
//            }
//
//            float x1 = (-b + SDL_sqrtf(delta)) / a; float y1 = x1 * iO.A + iO.B;
//            float x2 = (-b - SDL_sqrtf(delta)) / a; float y2 = x2 * iO.A + iO.B;
//
//            float S1 = 3.1415 * SDL_powf(scale.x / 2.f, 2);
//            float alp = asin(distance(Vector2f(x1, y1), Vector2f(x2, y2))) * 2 * 180 / 3.1415;
//            float S2 = S1 * alp / 360 - 0.5 * SDL_powf(scale.x, 2) * sin(alp * 3.1415 / 180);
//
//            if (getSign(dot(vecMid, vec2)) == sign)
//                S2 = S1 - S2;
//
//            if (S2 != S2 || S1 != S1) {
//                ok = 0;
//                continue;
//            }
//            setRatio(S2 / S1);
//            std::cout << ratioE << "\n";
//
//
//            ok = 0;
}
void Ball::handleEffect(std::vector<Obstacle*>& effect_obs)
{
    for (Obstacle* e : effect_obs) {
        if (e->getTypeObs() == 1)  {
            Vector2f i1(e->getX() + e->getW() / 2.f, e->getY() + e->getH() / 2.f); // tam guong
            Vector2f i2(pos.x + scale.x / 2.f + camera.x, pos.y + scale.y / 2.f + camera.y); // tam qua bong

//            i1.print();
//            std::cout << pos.x << ": " << camera.x << ": " << pos.y << ": " << camera.y << "\n";
//            effect_obs[e->getPar()]->getPos().print();
            if ( e->isOpen() && (e->get_r() - r) * (e->get_r() - r)  >= mathFunc::distance(i1, i2)) {

                setBallPosX(effect_obs[e->getPar()]->getX() + e->get_r());
                setBallPosY(effect_obs[e->getPar()]->getY() + e->get_r());

                pos.x -= camera.x;
                pos.y -= camera.y;
//                setCamera(camera);


                double x = SDL_GetTicks();
                effect_obs[e->getPar()]->setOpen(false);
                e->setOpen(false);

                effect_obs[e->getPar()]->setInitTime(x);
                e->setInitTime(x);
            }

            currentTime = SDL_GetTicks();

            if (currentTime - e->getInitTime() >= 1000)
                e->setOpen(true);

        }
    }
}

void Ball::update(bool mouseDown, bool mousePressed, std::vector<Obstacle*>& effect_obs,
                    std::vector<Obstacle*>& static_obs, Tile *tiles[])
{
//    updateCoolDown();
//    std::cout << pos.x << " " << pos.y << "\n";
    if (mouseDown) {
        int mouseX = 0, mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (pos.x <= mouseX && mouseX <= pos.x + 17 && pos.y <= mouseY && mouseY <= pos.y + 17) {
            setBall_clicked(true);
            setInitialMouseX(mouseX);
            setInitialMouseY(mouseY);
//            std::cout << ballClicked() << "\n";

        }
    }

    if (mouseDown == 0) {
        int mouseX = 0, mouseY = 0;

        if (!ballClicked()) return;

        SDL_GetMouseState(&mouseX, &mouseY);

        velocityX = (mouseX - 375) / -150.f;
        velocityY = (mouseY - 375) / -150.f;

        setBallPosX(getBallPosX() + velocityX);
//        std::cout << velocityX << " " << velocityY << "\n";
//        std::cout << checkCollision(obs) << "\n";
        handleEffect(effect_obs);
        if (getBallPosX() < 0 || getBallPosX() + getW() > SCREEN_WIDTH || checkCollision(static_obs))
            setBallPosX(getBallPosX() - velocityX);

        setBallPosY(getBallPosY() + velocityY);

        if (getBallPosY() < 0 || getBallPosY() + getH() > SCREEN_HEIGHT || checkCollision(static_obs))
            setBallPosY(getBallPosY() - velocityY);


        if (abs(getInitialMouseX() - getBallPosX()) == 0) setAngle(0);
        else {
            setAngle(atan(abs(getInitialMouseY() - getBallPosY()) / abs(getInitialMouseX() - getBallPosX())) * 180 / 3.1451);
            if (getBallPosX() >= SCREEN_WIDTH / 2 && getBallPosY() <= SCREEN_HEIGHT / 2) setAngle(180 - angle);
            else if (getBallPosX() <= SCREEN_WIDTH / 2 && getBallPosY() >= SCREEN_HEIGHT / 2) setAngle(360 - angle);
            else if (getBallPosX() >= SCREEN_WIDTH / 2 && getBallPosY() >= SCREEN_HEIGHT / 2) setAngle(180 + angle);
        }


//        std::cout << angle << "\n";
//
//        if (getBallPosY() < 17) setBallPosY(17);
//        if (getBallPosY() > 717) setBallPosY(717);
    }
}

void Ball::useSkill_0(int i)
{
    if (SDL_GetTicks() - initSkill[i] >= coolDown[i] || initSkill[i] == 0)
        skill[0] = 1;

    circleBoom->set_r(circleBoom->get_r() + 1);
    if (circleBoom->get_r() > 100) {
        circleBoom->setStatus(0);
        circleBoom->set_r(0);
        skill[0] = 0;

        initSkill[i] = SDL_GetTicks();
    }
}

void Ball::useSkill_1(const double& initFreezeTime, int i)
{
    if (SDL_GetTicks() - initSkill[i] >= coolDown[i]) {
        skill[1] = 1;
    }

    if (SDL_GetTicks() - initFreezeTime >= 3000) {
        skill[1] = 0;
        initSkill[i] = SDL_GetTicks();
    }
}

void Ball::useSkill_2(int i)
{
    skill[2] = 0;
    if (SDL_GetTicks() - initSkill[i] >= coolDown[i] || initSkill[i] == 0) {
        skill[2] = 1;
        initSkill[i] = SDL_GetTicks();
    }
}

void Ball::updateCoolDown()
{
    for (int i = 0; i < 3; i++) {
        if (getInitSkill(i) == 0) continue;
        coolDownTime[i] = coolDown[i] - (SDL_GetTicks() - initSkill[i]);
        if (coolDownTime[i] < 0) coolDownTime[i] = 0;
    }
}

void Ball::setCamera( SDL_Rect& camera )
{
	camera.x = ( pos.x + scale.x / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( pos.y + scale.y / 2 ) - SCREEN_HEIGHT / 2;

	//std::cout << pos.x + camera.x << " " << pos.y + camera.y << "\n";
	if( camera.x < 0 )
	{
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}
