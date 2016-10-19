#include "ObjectFactory.h"

#include "WallObject.h"
#include "MoneyObject.h"

Object::sptr ObjectFactory::fromLetter(char ch)
{
    switch (ch)
    {
        case WallObject::image:
            return std::make_shared<WallObject>();
        case MoneyObject::image:
            return std::make_shared<MoneyObject>(10);
        default:
            return std::make_shared<Object>(ch);
    }
}
