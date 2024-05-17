#include "Math.h"

Vector2f mathFunc::findIntersection(Linear c, Linear d)
{
    double x = -(c.B - d.B) / (c.A - c.B);
    double y = x * c.A + c.B;

    return {x, y};
}

bool mathFunc::checkCollision(Circle a, Circle b)
{
    Vector2f i1(a.x, a.y);
    Vector2f i2(b.x, b.y);

    if ( (a.r + b.r) * (a.r + b.r) > distance(i1, i2) )
        return 1;

    return 0;
}

bool mathFunc::checkCollision(Circle a, SDL_Rect b)
{
    //Closest point on collision box
    int cX, cY;

    //Find closest x offset
    if( a.x < b.x )
    {
        cX = b.x;
    }
    else if( a.x > b.x + b.w )
    {
        cX = b.x + b.w;
    }
    else
    {
        cX = a.x;
    }

    //Find closest y offset
    if( a.y < b.y )
    {
        cY = b.y;
    }
    else if( a.y > b.y + b.h )
    {
        cY = b.y + b.h;
    }
    else
    {
        cY = a.y;
    }

    //If the closest point is inside the circle
    if( distance(Vector2f(a.x, a.y), Vector2f(cX, cY)) < a.r * a.r )
    {
        //This box and the circle have collided
        return true;
    }

    //If the shapes have not collided
    return false;
}

bool mathFunc::checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

      //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool mathFunc::checkPointInside(Vector2f p, SDL_Rect a)
{
    return (a.x <= p.x && p.x <= a.x + a.w && a.y <= p.y && p.y <= a.y + a.h);
}

double mathFunc::distance(Vector2f c, Vector2f d)
{
    return SDL_pow(c.x - d.x, 2) + SDL_pow(c.y - d.y, 2);
}

double mathFunc::distance(Vector2f c, Linear d)
{
    return SDL_pow(SDL_fabsf(d.A * c.x - c.y + d.B), 2) / (d.A * d.A + 1);
}

double mathFunc::cross(Vector2f c, Vector2f d)
{
    return c.x * d.y - c.y * d.x;
}

double mathFunc::dot(Vector2f c, Vector2f d)
{
    return c.x * c.y + d.x * d.y;
}

int mathFunc::getSign(double x)
{
    if (x == 0.f) return 0;
    return (x < 0 ? -1 : 1);
}
