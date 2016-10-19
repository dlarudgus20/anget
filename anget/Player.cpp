#include "Player.h"
#include "Effect.h"

Player::Player()
    : Object('@')
{
    destroyable_ = true;
    hp_ = maxHp_ = 100;
    mp_ = maxMp_ = 10;

    attackable_ = true;
    atk_ = 1;

    moneyEarnable_ = true;
}

bool Player::collapse(Object* other)
{
    return Object::collapse(other);
}
