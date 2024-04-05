#include "obstacleBuilder.h"
#include "Common_Function.h"

std::vector<Obstacle*> obsBuilder::createStraightLineObs(int num, Vector2f curPos, int dir, int type)
{
    std::vector<Obstacle*> vecObs;
    float W = scaleTypes[type].x, H = scaleTypes[type].y;
    float curX = curPos.x, curY = curPos.y;
    for (int i = 1; i <= num; i++) {
        curX += dx[dir] * W;
        curY += dy[dir] * H;

        if (curX > SCREEN_WIDTH || curX < 0) break;
        if (curY > SCREEN_HEIGHT || curY < 0) break;
        Obstacle* obs = new Obstacle(type, Vector2f(curX, curY));
        vecObs.push_back(obs);
    }

    return vecObs;
}

std::vector<Obstacle*> obsBuilder::createDiagonalLineObs(int num, Vector2f curPos, int dir, int type)
{
    std::vector<Obstacle*> vecObs;
    float W = scaleTypes[type].x, H = scaleTypes[type].y;
    float curX = curPos.x, curY = curPos.y;
    for (int i = 1; i <= num; i++) {
        curX += dx[dir] * W + dx[dir] * (W / 4);
        curY += dy[dir] * H + dy[dir] * (W / 4);

        if (curX > SCREEN_WIDTH || curX < 0) break;
        if (curY > SCREEN_HEIGHT || curY < 0) break;
        Obstacle* obs = new Obstacle(type, Vector2f(curX, curY));
        vecObs.push_back(obs);
    }

    return vecObs;
}
