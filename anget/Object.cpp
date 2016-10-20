#include <stdexcept>
#include <algorithm>
#include <utility>
#include "conlib.h"

#include "Object.h"
#include "Map.h"
#include "Effect.h"
#include "Timer.h"

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
        gotoxy(x + 45, y + dy);
        printclr(21);
        gotoxy(x, y + dy);
        printf("HP  ");
        printbar(getHp(), getMaxHp());
        printf(" %d/%d", getHp(), getMaxHp());
        dy += 1;

        gotoxy(x + 45, y + dy);
        printclr(21);
        gotoxy(x, y + dy);
        printf("MP  ");
        printbar(getMp(), getMaxMp());
        printf(" %d/%d", getMp(), getMaxMp());
        dy += 1;
    }

    if (expEarnable_)
    {
        gotoxy(x + 46, y + dy);
        printclr(21);
        gotoxy(x, y + dy);
        printf("EXP ");
        printbar(getExp(), getMaxExp());
        printf(" %d/%d", getExp(), getMaxExp());
        dy += 1;
    }

    if (moneyEarnable_)
    {
        gotoxy(x + 6, y + dy);
        printclr(11);
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

        if (other->collapse(this))
            return false;
    }

    auto ptr = map_->displace(x_, y_);
    map_->place(ptr , x_ + dx, y_ + dy);
    return true;
}

void Object::getEffect(const Effect & eff)
{
    if (destroyable_)
    {
        hp_ = range(0, hp_ + eff.hp, maxHp_);
    }

    if (moneyEarnable_)
    {
        money_ = std::max(0, money_ + eff.money);
    }

    if (destroyable_ && hp_ == 0)
    {
        dead_ = die();
    }
}

bool Object::picked(Object* by, Effect& eff)
{
    return false;
}

bool Object::die()
{
    objch_ = 'X';

    std::weak_ptr<Object> wptr = shared_from_this();
    Timer::get().addEntry([wptr] {
        auto ptr = wptr.lock();
        if (ptr)
        {
            ptr->map_->displace(ptr->x_, ptr->y_);
        }
    }, 50, 1);

    return true;
}

bool Object::isEnemy(Object * other)
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
            return true;
        }
    }

    return false;
}
