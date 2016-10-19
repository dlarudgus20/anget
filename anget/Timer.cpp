#include "Timer.h"

Timer& Timer::get()
{
    static Timer obj;
    return obj;
}
