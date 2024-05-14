#include "skill.h"

Skill::Skill()
{
    typeSkill = 0;
    activated = 1;
}

Skill::Skill(int type, int r_)
{
    typeSkill = type;
    activated = 1;
    r = r_;
}
