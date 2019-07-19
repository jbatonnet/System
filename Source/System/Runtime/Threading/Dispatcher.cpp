#include <System/Runtime/Threading/Dispatcher.h>
#include <System/Runtime/Threading/Spinlock.h>

#include <System/Debugging/Log.h>
#include <System/Runtime/Debugging/Debugger.h>

#define DISPATCHER_BUFFER_SIZE 65

using namespace System::Runtime;

Dispatcher::Dispatcher() : bufferIndex(0), frameBuffer1(DISPATCHER_BUFFER_SIZE), frameBuffer2(DISPATCHER_BUFFER_SIZE)
{
}

void Dispatcher::Invoke(BaseFrame* frame)
{
    lock (invokeLock)
    {
        List<BaseFrame*>* frameBuffer = bufferIndex ? &frameBuffer1 : &frameBuffer2;
        frameBuffer->Add(frame);
    }
}
void Dispatcher::Flush()
{
    lock (flushLock)
    {
        bufferIndex = !bufferIndex;
        List<BaseFrame*>* frameBuffer = bufferIndex ? &frameBuffer2 : &frameBuffer1;

        for (u32 i = 0; i < frameBuffer->Count; i++)
        {
            BaseFrame* frame = frameBuffer->At(i);
            frame->Process();
            delete frame;
        }

        frameBuffer->Clear();
    }
}

Dispatcher* Dispatcher::GetCurrent()
{
    Thread* thread = Thread::GetCurrent();
    if (!thread)
        return null;

    return thread->Dispatcher;
}