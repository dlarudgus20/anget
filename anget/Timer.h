#pragma once

#include <functional>
#include <list>


class Timer
{
public:
    static Timer& get();

    void addEntry(std::function<void()> fn, unsigned time, unsigned repeat = 0);

    void runTick(unsigned dt = 1);

private:
    struct TimerEntry
    {
        std::function<void()> fn;
        unsigned timeout;
        unsigned time;
        unsigned repeat;
    };

    std::list<TimerEntry> entryList_;
    unsigned tick_ = 0;
};
