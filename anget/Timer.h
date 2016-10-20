#pragma once

#include <functional>
#include <list>


class Timer
{
public:
    static Timer& get();

    void addEntry(std::function<void()> fn, unsigned time, int repeat);

    void runTick();

private:
    struct TimerEntry
    {
        std::function<void()> fn;
        unsigned timeout;
        unsigned time;
        int repeat;
    };

    std::list<TimerEntry> entryList_;
    unsigned tick_ = 0;
};
