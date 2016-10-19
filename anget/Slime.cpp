#include "Slime.h"

Slime::Slime()
    : Object(image)
{
    destroyable_ = true;
    hp_ = maxHp_ = 10;
    mp_ = maxMp_ = 1;

    attackable_ = true;
    atk_ = 1;
}
