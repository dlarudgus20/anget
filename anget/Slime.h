#pragma once

#include "Object.h"

class Slime : public Object
{
public:
    static const char image = '%';

    Slime();

private:
    void onTimer();

    virtual bool collapse(Object* other) override;
};
