#include <utility>

#include "Timer.h"

Timer& Timer::get()
{
    static Timer obj;
    return obj;
}

void Timer::addEntry(std::function<void()> fn, unsigned time, int repeat)
{
    entryList_.push_back({ std::move(fn), tick_ + time, time, repeat });
}

void Timer::runTick()
{
    ++tick_;

    for (auto it = entryList_.begin(); it != entryList_.end(); )
    {
        auto& entry = *it;

        if (entry.timeout <= tick_)
        {
            entry.fn();
            if (entry.repeat != -1)
            {
                if (entry.repeat == 0)
                {
                    entryList_.erase(it++);
                    continue;
                }

                --entry.repeat;
                entry.timeout += entry.time;
            }
        }

        ++it;
    }
}
