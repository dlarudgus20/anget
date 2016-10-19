#include "MoneyObject.h"
#include "Effect.h"

MoneyObject::MoneyObject(int money)
    : Object(image), money_(money)
{
    pickable_ = true;
}

bool MoneyObject::picked(Object* by, Effect& eff)
{
    if (by->isMoneyEarnable())
    {
        eff.money = money_;
        return true;
    }
    else
    {
        return false;
    }
}
