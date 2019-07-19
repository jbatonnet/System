#include <System/Utilities/Time/Timer.h>
#include <Kernel/Runtime/Threading/Task.h>

u64 Timer::Ticks = 0;

u64 Timer::Time()
{
    return Ticks;
}

void Timer::Sleep(u64 milliseconds)
{
    Task::Suspend(milliseconds);
}