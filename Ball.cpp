#include "Ball.h"

Ball::Ball()
{
    pos = Vector2f(450.f / 2, 750.f / 2);
    scale = Vector2f(17.f, 17.f);
    r = scale.x / 2.f;
    ball = nullptr;
    hole = nullptr;
}

bool Ball::checkCollision(std::vector<Obstacle*>& obs)
{
    for (Obstacle* e : obs) {
        bool ok = 1;
//        std::cout << e->getX() << " " << e->getY() << " " << e->getW() << " " << e->getH() << " " << getBallPosX() << " " << getBallPosY() << "\n";
//        std::cout << e->getTypeObs() << "\n";
        if (e->getTypeObs() == 0) {
            if (getBallPosX() + getW() <= e->getX()) ok = 0;
            if (getBallPosX() >= e->getX() + e->getW()) ok = 0;
            if (getBallPosY() + getH() <= e->getY()) ok = 0;
            if (getBallPosY() >= e->getY() + e->getH()) ok = 0;
        }
        else if (e->getTypeObs() == e->typeOb::MIRROR) {
//            Vector2f i1(e->getX() + e->getW() / 2.f, e->getY() + e->getH() / 2.f);
//            Vector2f i2(pos.x + scale.x / 2.f, pos.y + scale.y / 2.f);

            Vector2f i1(e->getX() + e->getW() / 2.f, e->getY() + e->getH() / 2.f);
            Vector2f i2(pos.x + scale.x / 2.f, pos.y + scale.y / 2.f);

            ok = 0;
            if ( (r + e->get_r()) * (r + e->get_r()) > (i1.x - i2.x) * (i1.x - i2.x) + (i1.y - i2.y) * (i1.y - i2.y) )
                ok = 1;
        }
        else {

        }

        if (ok) return 1;
    }

    return 0;
}

void Ball::update(bool mouseDown, bool mousePressed, std::vector<Obstacle*>& obs)
{
    if (mouseDown) {
        int mouseX = 0, mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (pos.x <= mouseX && mouseX <= pos.x + 17 && pos.y <= mouseY && mouseY <= pos.y + 17) {
            setBall_clicked(true);
            setInitialMouseX(mouseX);
            setInitialMouseY(mouseY);
        }
    }

    if (mouseDown == 0) {
        int mouseX = 0, mouseY = 0;

        if (!ballClicked()) return;
        SDL_GetMouseState(&mouseX, &mouseY);

        velocityX = (mouseX - getInitialMouseX()) / -50.f;
        velocityY = (mouseY - getInitialMouseY()) / -50.f;

        setBallPosX(getBallPosX() + velocityX);

//        std::cout << checkCollision(obs) << "\n";
        if (getBallPosX() < 0 || getBallPosX() + getW() > SCREEN_WIDTH || checkCollision(obs))
            setBallPosX(getBallPosX() - velocityX);

        setBallPosY(getBallPosY() + velocityY);

        if (getBallPosY() < 0 || getBallPosY() + getH() > SCREEN_HEIGHT || checkCollision(obs))
            setBallPosY(getBallPosY() - velocityY);
//
//        if (getBallPosY() < 17) setBallPosY(17);
//        if (getBallPosY() > 717) setBallPosY(717);
    }

}

