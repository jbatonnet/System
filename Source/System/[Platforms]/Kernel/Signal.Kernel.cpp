#ifdef KERNEL

#include <System/Runtime/Threading/Signal.h>

#include <Kernel/Interrupts.h>
#include <Kernel/Runtime/Threading/Task.h>

#include <System/Debugging/Serial.h>
#include <System/Utilities/Time/Timer.h>
//#include <Kernel/Runtime/Threading/Thread.h>

using namespace System::Runtime;

Signal::Signal() : id(-1)
{
}

void Signal::Initialize()
{
    u32 function = (u8)TaskSynchronizationCommand::InitSignal;
    u32 id = 0;

    _asm
    {
        mov eax, [function]

        int INTERRUPT_KERNEL + KERNEL_INTERRUPT_TASKSYNCHRONIZATION

        mov [id], eax
    }

    this->id = id;

    //Debug::Assert(id != -1, "Signal::Initialize() : No more free signals");
}

void Signal::Send()
{
    Task::BeginCritical();
    if (id == -1) ((Signal*)this)->Initialize();
    Task::EndCritical();

#if DEBUG_TASKING
    Serial::WriteLine("[{0}] T{1} : Signal::Send()", (u32)Timer::Ticks, Task::Current->id);
#endif

    u32 function = (u8)TaskSynchronizationCommand::SendSignal;
    u32 id = this->id;
    u32 result = 0;

    _asm
    {
        mov eax, [function]
        mov ebx, [id]

        int INTERRUPT_KERNEL + KERNEL_INTERRUPT_TASKSYNCHRONIZATION

        mov [result], eax
    }

    //Debug::Assert(result != -1, "Signal::Send() : Error sending signal");
}
bool Signal::Wait(u32 timeout) const
{
    Task::BeginCritical();
    if (id == -1) ((Signal*)this)->Initialize();
    Task::EndCritical();
    
#if DEBUG_TASKING
    Serial::WriteLine("[{0}] T{1} : Signal::Wait({2})", (u32)Timer::Ticks, Task::Current->id, timeout);
#endif

    u32 function = timeout ? (u8)TaskSynchronizationCommand::WaitSignalTimeout : (u8)TaskSynchronizationCommand::WaitSignal;
    u32 id = this->id;
    u32 result = 0;

    _asm
    {
        mov eax, [function]
        mov ebx, [id]
        mov ecx, [timeout]

        int INTERRUPT_KERNEL + KERNEL_INTERRUPT_TASKSYNCHRONIZATION

        mov [result], eax
    }

    //Debug::Assert(result != -1, "Signal::Wait() : Error waiting for signal");
    return true;
}

#endif