#include <System/Utilities/Random.h>
#include <System/Utilities/Time/Timer.h>

u32 RandomStream::Read(void* buffer, u32 count)
{
    u8* bufferBytes = (u8*)buffer;

    for (u32 i = 0; i < count; i++)
    {
        next = next * 1103515245 + 12345;
        bufferBytes[i] = (u8)((next / 65536) % 32768);
    }

    return count;
}