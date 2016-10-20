#include <array>

#include "Player.h"
#include "Map.h"
#include "Effect.h"

Player::Player()
    : Object('@')
{
    destroyable_ = true;
    hp_ = maxHp_ = 100;
    mp_ = maxMp_ = 10;

    attackable_ = true;
    atk_ = 999999999;

    moneyEarnable_ = true;
}

bool Player::attack()
{
    Object* target = nullptr;

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue;

            if (getMap()->isValid(getX() + dx, getY() + dy))
            {
                auto& obj = getMap()->get(getX() + dx, getY() + dy);
                if (obj && isEnemy(obj.get()) && obj->isDestroyable())
                {
                    target = obj.get();
                }
            }
        }
    }
    if (target == nullptr)
        return false;

    Effect eff;
    eff.hp = -getAtk();
    target->getEffect(eff);
    if (target->isDead())
    {
        exp_ += target->getMaxExp();
    }

    return true;
}

bool Player::isEnemy(Object * other)
{
    return true;
}

bool Player::collapse(Object* other)
{
    return Object::collapse(other);
}
