#pragma once

#include "Object.h"

class MoneyObject : public Object
{
public:
    static const char image = '$';

    explicit MoneyObject(int money);

    int getMoney() const { return money_; }

    virtual bool picked(Object* by, Effect& eff) override;

private:
    int money_;
};