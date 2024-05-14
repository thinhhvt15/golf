#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

#include "math.h"
#include "BaseObject.h"

class Skill : public BaseObject
{
public:
    Skill();
    Skill(int type, int r_);
    ~Skill();
    bool getStatus() {return activated;}
    void setStatus(bool x) {activated = x;}

private:
    bool activated = 0;
    int typeSkill = 0;
};

#endif // SKILL_H_INCLUDED
