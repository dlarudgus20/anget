#include <array>
#include <functional>
#include <stdlib.h>
#include "Slime.h"
#include "Map.h"
#include "Timer.h"
#include "Effect.h"

Slime::Slime()
    : Object(image)
{
    destroyable_ = true;
    hp_ = maxHp_ = 10;
    mp_ = maxMp_ = 1;

    attackable_ = true;
    atk_ = 1;

    Timer::get().addEntry(std::bind(&Slime::onTimer, this), 10);
}

void Slime::onTimer()
{
    std::array<int, 2> ardp[8];
    unsigned count = 0;

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue;

            if (getMap()->isValid(getX() + dx, getY() + dy))
            {
                ardp[count++] = { dx, dy };
            }
        }
    }

    if (count != 0)
    {
        auto& dp = ardp[rand() % count];
        move(dp[0], dp[1]);
    }
}

bool Slime::collapse(Object* other)
{
    if (other->isDestroyable())
    {
        Effect eff;
        eff.hp = -getAtk();
        other->getEffect(eff);
        return other->isDead();
    }

    return Object::collapse(other);
}
