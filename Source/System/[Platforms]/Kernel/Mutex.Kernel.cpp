#ifdef KERNEL

#include <System/Runtime/Threading/Mutex.h>

#include <Kernel/Interrupts.h>
#include <Kernel/Runtime/Threading/Task.h>

#include <System/Debugging/Console.h>
#include <System/Debugging/Serial.h>
#include <System/Utilities/Time/Timer.h>
#include <Kernel/Devices/Screen/Screen.h>
//#include <Kernel/Runtime/Threading/Thread.h>

using namespace System::Runtime;

Mutex::Mutex() : locked(false), id(-1)
{
}
Mutex::Mutex(bool locked) : locked(locked), id(-1)
{
    Initialize();
}

void Mutex::Initialize()
{
    //Serial::WriteLine("[T{0}] Mutex::Initialize()", Task::Current->id);

    u32 function = (u8)TaskSynchronizationCommand::InitMutex;
    u32 id = 0;

    _asm
    {
        mov eax, [function]

        int INTERRUPT_KERNEL + KERNEL_INTERRUPT_TASKSYNCHRONIZATION

        mov [id], eax
    }

    this->id = id;

    //Serial::WriteLine("[T{0}] -> Got id {1}", Task::Current->id, id);
    Exception::Assert(id != -1, "Mutex::Initialize() : No more free mutexes");

    if (locked)
        Lock();
}

bool Mutex::Lock(u32 timeout)
{
    Task::BeginCritical();
    if (id == -1) Initialize();
    Task::EndCritical();

#if DEBUG_TASKING
    Serial::WriteLine("[T{0}] Mutex::Lock()", Task::Current->id);
#endif

    u32 function = (u8)TaskSynchronizationCommand::LockMutex;
    u32 id = this->id;
    u32 result = 0;

    _asm
    {
        mov eax, [function]
        mov ebx, [id]

        int INTERRUPT_KERNEL + KERNEL_INTERRUPT_TASKSYNCHRONIZATION

        mov [result], eax
    }

    //Debug::Assert(result != -1, "Error locking mutex");

#if DEBUG_TASKING
    Serial::WriteLine("[T{0}] Mutex locked", Task::Current->id);
#endif

    locked = true;
}
void Mutex::Unlock()
{
    Task::BeginCritical();
    if (id == -1) Initialize();
    Task::EndCritical();

#if DEBUG_TASKING
    Serial::WriteLine("[T{0}] Mutex::Unlock()", Task::Current->id);
#endif

    u32 function = (u8)TaskSynchronizationCommand::UnlockMutex;
    u32 id = this->id;
    u32 result = 0;

    _asm
    {
        mov eax, [function]
        mov ebx, [id]

        int INTERRUPT_KERNEL + KERNEL_INTERRUPT_TASKSYNCHRONIZATION

        mov [result], eax
    }

    //Debug::Assert(result != -1, "Error unlocking mutex");

#if DEBUG_TASKING
    Serial::WriteLine("[T{0}] Mutex unlocked", Task::Current->id);
#endif

    locked = false;
}

#endif