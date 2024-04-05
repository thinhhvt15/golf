
#include "Ellipse.h"

Ellipse::Ellipse()
{

}

bool checkCollision(Ellipse* E, Ball* b)
{
    Linear AB(b->pos, E->pos);
    float delta = SDL_powf(AB.A * AB.B * E->dx * E->dx, 2) -
                (AB.A * AB.A * E->dx * E->dx + E->dy * E->dy) * (E->dx * E->dx * AB.b * AB.b - E->dx * E->dx * E->dy * E->dy);

    float a = AB.A * AB.A * E->dx * E->dx + E->dy * E->dy;
    float b = AB.A * AB.B * E->dx * E->dx;

    float x1 = (-b + SDL_sqrtf(delta)) / a;
    float x2 = (-b - SDL_sqrtf(delta)) / a;

    float y1 = x1 * AB.A + AB.B;
    float y2 = x2 * AB.A + AB.B;

    float dis1 = distance(b->pos, {x1, y1}) + distance(E->pos, {x1, y1});
    float dis2 = distance(b->pos, {x2, y2}) + distance(E->pos, {x2, y2});

}
