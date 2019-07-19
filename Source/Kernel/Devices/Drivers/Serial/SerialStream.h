#ifndef _KERNEL_SERIALSTREAM_H_
#define _KERNEL_SERIALSTREAM_H_

#include <System/IO/Streams/Stream.h>
#include <System/Runtime/Threading/Spinlock.h>

class SerialStream : public System::IO::Stream
{
    friend class SerialDevice;

private:
    SerialDevice* device;
    System::Runtime::Spinlock spinLock;

    SerialStream(SerialDevice* device);

public:
    virtual u32 Read(void* buffer, u32 count);
    virtual void Write(void* buffer, u32 count);
};

#endif