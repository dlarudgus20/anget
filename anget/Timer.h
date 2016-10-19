#pragma once

#include <functional>
#include <list>

class Timer
{
public:
    static Timer& get();

    void runTick();

private:
    struct TimerEntry
    {
        std::function<void()> fn;
        int timeout;
        int repeat;
    };
};
