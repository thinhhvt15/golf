#ifndef OBSTACLEBUILDER_H_INCLUDED
#define OBSTACLEBUILDER_H_INCLUDED

#include "Obstacle.h"
#include "Math.h"

class obsBuilder
{
public:
    std::vector<Obstacle*> createStraightLineObs(int num, Vector2f curPos, int dir, int type);
    std::vector<Obstacle*> createDiagonalLineObs(int num, Vector2f curPos, int dir, int type);
    void addObs(std::vector<Obstacle*> obs) {buildVec.push_back(obs);}
    std::vector<std::vector<Obstacle*>> getVec() {return buildVec;}
private:
    Vector2f scaleTypes[3] = {Vector2f(50.f, 50.f), Vector2f(80.f, 15.f)};
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, -1, 0, 1};
    std::vector<std::vector<Obstacle*>> buildVec;
};

#endif // OBSTACLEBUILDER_H_INCLUDED
