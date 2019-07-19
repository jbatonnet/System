#ifndef _SYSTEM_RANDOM_H_
#define _SYSTEM_RANDOM_H_

#include <System/Common.h>
#include <System/IO/Streams/Stream.h>
#include <System/Utilities/Time/Timer.h>

class RandomStream : public System::IO::Stream
{
private:
    u32 next;

public:
    RandomStream(u32 seed) : next(seed) { }

    u32 Read(void* buffer, u32 count);
    void Write(void* buffer, u32 count) { }
};

/// <summary>
/// A class used to generate random values
/// </summary>
class Random
{
private:
    static Random random;

    u32 next;
    RandomStream stream;

public:
    /// <summary>
    /// Creates a new random number generator
    /// </summary>
    Random() : next(Timer::Time()), stream(next) { }
    /// <summary>
    /// Creates a new random number generator
    /// </summary>
    /// <param name="seed">The seed used for this generator</param>
    Random(u32 seed) : next(seed), stream(seed) { }

    /// <summary>
    /// Generate a random value of the specified type
    /// </summary>
    /// <returns>An instance of the specified type with random content</returns>
    template<typename T> T Generate()
    {
        T result;

        //stream.Read(&result, sizeof(T));
        for (u32 i = 0; i < sizeof(T); i++)
        {
            next = next * 1103515245 + 12345;
            ((u8*)&result)[i] = (u8)((next / 65536) % 32768);
        }

        return result;
    }
};

#endif