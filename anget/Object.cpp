#include <stdexcept>
#include <algorithm>
#include "conlib.h"
#include <utility>
#include "conlib.h"

#include "Object.h"
#include "Map.h"
#include "Effect.h"

Object::Object(char ch, std::string name)
    : objch_(ch), name_(std::move(name))
{
}

int Object::printinfo(int x, int y)
{
    int dy = 0;

    gotoxy(x, y + dy);
    printf("%s", name_.c_str());
    dy += 1;

    if (destroyable_)
    {
        gotoxy(x, y + dy);
        printf("HP  ");
        printbar(getHp(), getMaxHp());
        printf(" %d/%d", getHp(), getMaxHp());
        dy += 1;

        gotoxy(x, y + dy);
        printf("MP  ");
        printbar(getMp(), getMaxMp());
        printf(" %d/%d", getMp(), getMaxMp());
        dy += 1;
    }

    if (expEarnable_)
    {
        gotoxy(x, y + dy);
        printf("EXP ");
        printbar(getExp(), getMaxExp());
        printf(" %d/%d", getExp(), getMaxExp());
        dy += 1;
    }

    if (moneyEarnable_)
    {
        gotoxy(x, y + dy);
        printf("Money %d$", getMoney());
        dy += 1;
    }

    return dy;
}

bool Object::move(int dx, int dy)
{
    if (dx == 0 && dy == 0)
        return true;

    if (dx > 1)
    {
        for (; dx >= 1; --dx)
            if (!move(1, 0))
                return false;
        return true;
    }
    else if (dx < -1)
    {
        for (; dx <= -1; ++dx)
            if (!move(-1, 0))
                return false;
        return true;
    }

    if (dy > 1)
    {
        for (; dy >= 1; --dy)
            if (!move(0, 1))
                return false;
        return true;
    }
    else if (dy < -1)
    {
        for (; dy <= -1; ++dy)
            if (!move(0, 1))
                return false;
        return true;
    }

    auto other = map_->get(x_ + dx, y_ + dy);
    if (other)
    {
        if (!collapse(other.get()))
            return false;
    }

    auto ptr = map_->displace(x_, y_);
    map_->place(ptr , x_ + dx, y_ + dy);
    return true;
}

bool Object::getHit(Object* from, int damage)
{
    if (!destroyable_)
        throw std::logic_error("try to hit the undestroyable");
    if (!from->attackable_)
        throw std::logic_error("the unattackable tries to hit");

    hp_ = std::max(hp_ - damage, 0);
    return (hp_ == 0);
}

bool Object::giveHit(Object* to)
{
    if (!to->destroyable_)
        throw std::logic_error("try to hit the undestroyable");
    if (!attackable_)
        throw std::logic_error("the unattackable tries to hit");

    return to->getHit(this, atk_);
}

bool Object::picked(Object* by, Effect& eff)
{
    return false;
}

bool Object::collapse(Object* other)
{
    if (other->isPickable())
    {
        Effect eff;
        if (other->picked(this, eff))
        {
            money_ += eff.money;
            return true;
        }
    }

    return false;
}
