#ifndef _SYSTEM_TIMER_H_
#define _SYSTEM_TIMER_H_

#include <System/Common.h>

/// <summary>
/// A class used to manipulate time
/// </summary>
shared class Timer
{
public:
    static u64 Ticks;

    /// <summary>
    /// Returns the current tick count from the boot of the system    
    /// </summary>
    /// <returns>The current tick count from the boot of the system</returns>
    static u64 Time();

    /// <summary>
    /// Sleeps the specified amount of milliseconds
    /// </summary>
    /// <param name="milliseconds">The number of milliseconds to sleep</param>
    static void Sleep(u64 milliseconds);
};

#endif