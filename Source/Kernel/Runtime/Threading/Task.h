#ifndef _KERNEL_TASK_H_
#define _KERNEL_TASK_H_

#include <System/Base/Types.h>
#include <Kernel/Memory/VMM.h>
#include <Kernel/Config.h>

#define INTERRUPT_TASK_SWITCH INTERRUPT_KERNEL
#define INTERRUPT_TASK_END    (INTERRUPT_TASK_SWITCH + 1)

struct RegistersState
{
    union { u32 eax; union { u16 ax; struct { u8 ah; u8 al; }; }; };
    union { u32 ecx; union { u16 cx; struct { u8 ch; u8 cl; }; }; };
    union { u32 edx; union { u16 dx; struct { u8 dh; u8 dl; }; }; };
    union { u32 ebx; union { u16 bx; struct { u8 bh; u8 bl; }; }; };

    u32 eip;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;

    u32 cs;
    u32 ds;
    u32 es;
    u32 fs;
    u32 gs;
    u32 ss;

    u32 eflags;

    u32 int_no;
    u32 err_code;
    u32 useresp;
};

enum class TaskSynchronizationCommand : u8
{
    BeginCritical,
    EndCritical,

    InitMutex,
    ReleaseMutex,
    LockMutex,
    UnlockMutex,
    WaitMutex,
    WaitMutexTimeout,

    InitSignal,
    ReleaseSignal,
    SendSignal,
    WaitSignal,
    WaitSignalTimeout
};

enum class TaskType : u8
{
    Kernel,
    User,
    Virtual
};
enum class TaskState : u8
{
    Paused,
    Running,
    Ended
};
enum class TaskMode : u8
{
    Normal,
    Critical,

    LockMutex,
    LockMutexTimeout,
    WaitMutex,
    WaitMutexTimeout,

    WaitSignal,
    WaitSignalTimeout,

    WaitAPI,
};

union TaskModeData
{
    struct
    {
        u32 Id;
    } Mutex;
    struct
    {
        u32 Id;
        u64 Tick;
    } Signal;
};

namespace System
{
    namespace Runtime
    {
        class Thread;
    }
}

class Task
{
    friend class KernelThread;

    // FIXME: Dirty way to do this
    friend void API_InterruptHandler(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers);
    friend void API_HandleInterrupts();
    friend void StatsThread();

public:
    static Task *First, *Kernel, *Current;

private:
    static u32 _id;
    Task();

public:
    u32 id;

protected:
    TaskType     type;
    TaskState    state;
    TaskMode     mode;
    TaskModeData data;

    Task* next;
    u64   tick;

    RegistersState cpu;
    u8 fpu[512];

    PageDirectory* directory;
    KernelThread* thread;

    void* heap;
    void* stack;
    void* code;

public:
    bool virtualInterrupt;
    //u64 lastSwitch, totalTime;

    Task(TaskType type, void* pointer, void* stack = null, void* heap = null, PageDirectory* directory = (PageDirectory*)MEMORY_DIRECTORIES);

    void Run();
    void Kill();

    // Static
    static void PreInitialize();
    static void Initialize();
    static void PostInitialize();
    static void Suspend(u64 milliseconds);
    static void Switch();
    static void BeginCritical();
    static void EndCritical();
	static bool IsInterrupt();

    // Friends
    friend void Interrupt_TaskSwitch(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers);
    friend void Interrupt_VirtualHandler(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers);
    friend void Interrupt_VirtualMonitor(InterruptHandlerParameters parameters, u32 irq, u32 gpf, InterruptHandlerRegisters registers);
    friend void Interrupt_Synchronization(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers);

    friend void Task_Save(u32 prefixSize);
    friend void Task_Restore(u32 prefixSize);
};

#endif