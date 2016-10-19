#pragma once

#include "Object.h"

class ObjectFactory
{
public:
    static Object::sptr fromLetter(char ch);
};
