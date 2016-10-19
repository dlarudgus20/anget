#pragma once

#include "Object.h"

class Player : public Object
{
public:
    Player();

private:
    virtual bool collapse(Object* other) override;
};
