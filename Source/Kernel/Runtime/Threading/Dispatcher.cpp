#include <System/Runtime/Threading/Dispatcher.h>
#include <System/Runtime/Threading/Spinlock.h>

#include <System/Debugging/Log.h>
#include <System/Runtime/Debugging/Debugger.h>

#include <HAL/Interrupts.h>
#include <Kernel/Runtime/Threading/Dispatcher.h>

using namespace System::Runtime;

Dispatcher interruptDispatcher;

Dispatcher* Dispatcher::GetCurrent()
{
    if (interrupt_interrupting)
        return &interruptDispatcher;

    Thread* thread = Thread::GetCurrent();
    if (!thread)
        return null;

    return thread->Dispatcher;
}