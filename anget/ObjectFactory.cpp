#include "ObjectFactory.h"

#include "WallObject.h"
#include "MoneyObject.h"
#include "Slime.h"

Object::sptr ObjectFactory::fromLetter(char ch)
{
    switch (ch)
    {
        case WallObject::image:
            return std::make_shared<WallObject>();
        case MoneyObject::image:
            return std::make_shared<MoneyObject>(10);
        case Slime::image:
            return std::make_shared<Slime>();
        default:
            return std::make_shared<Object>(ch);
    }
}
