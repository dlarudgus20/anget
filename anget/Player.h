#pragma once

#include "Object.h"

class Player : public Object
{
public:
    Player();

    bool attack();

private:
    virtual bool isEnemy(Object* other) override;
    virtual bool collapse(Object* other) override;
};
