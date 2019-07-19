#if X86

#include <Kernel/Runtime/Threading/Task.h>
#include <Kernel/Memory/Memory.h>
#include <Kernel/Interrupts.h>

#include <System/Utilities/Time/Timer.h>
#include <Kernel/Runtime/Threading/Process.h>
#include <Kernel/Runtime/Threading/Thread.h>

#include <System/Debugging/Console.h>
#include <System/Debugging/Serial.h>
#include <Kernel/Devices/Screen/Screen.h>
#include <Kernel/Devices/Drivers/Keyboard/Keyboard.h>

#include <HAL/x86/CPU/TSS.h>
#include <HAL/Interrupts.h>

using namespace System::Runtime;

#pragma optimize("", off)

u32 Task::_id = 1;
Task *Task::First = null,
     *Task::Kernel = null,
     *Task::Current = null;

char* virtualCodes = (char*)KERNEL_VIRTUAL_CODE;
u16* virtualStack = (u16*)KERNEL_VIRTUAL_STACK;

bool operand32, address32;
u32 _es;
__declspec(align(0x10)) u8 _fpu[512];

/*
    TODO
    - Save and load SSE registers (fxsave)
*/

// Mutexes
#define MUTEX_MAX_COUNT 256 
struct MutexValue
{
    u32 Owner;
    u32 Locker;
};
MutexValue mutexes[MUTEX_MAX_COUNT] = { 0 };

// Signals
#define SIGNAL_MAX_COUNT 256
struct SignalStruct
{
    u32 Owner;
    u64 Sent;
};
SignalStruct signals[SIGNAL_MAX_COUNT] = { 0 };

#define DumpTask(word) Write("[%d] T%d : ", (u32)Timer::Ticks, Task::Current->id); \
                       task = Task::First; \
                       do \
                       { \
                           Write("T%d%s(%d) ", task->id, task->state == TaskState::Paused ? "P" : \
                                                         task->mode == TaskMode::LockMutex ? "L" : \
                                                         task->mode == TaskMode::WaitSignal ? "S" : \
                                                         task->mode == TaskMode::WaitAPI ? "A" : "", task->tick); \
                           task = task->next; \
                       } \
                       while (task); \
                       Writee("(%s)\n", word);

void Interrupt_Clock()
{
    Timer::Ticks++;
}
void Interrupt_TaskSwitch(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)
{
    if (Task::Current->mode == TaskMode::Critical)
        return;

    Task_Save(sizeof(parameters) / 4 + 1);
    Task::Switch();
    Task_Restore(sizeof(parameters) / 4 + 1);
}
void Interrupt_VirtualHandler(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)
{
    Task_Save(sizeof(parameters) / 4 + 1 + 1);
    Task::Current->cpu.esp -= 12;

    // Set up new stack
    virtualStack = (u16*)0x7FFFC;
    *virtualStack-- = 0xFFFF; // eflags
    *virtualStack-- = 0xFFFF; // cs
    *virtualStack-- = 0xFFFF; // ip

    // Switch to virtual task
    Task::Current->type = TaskType::Virtual;
    Task_Restore(sizeof(parameters) / 4 + 1 + 1);
    _asm mov ebp, esp
    _asm add ebp, 4

    // Change current stack
    u32 virtualCode = (u32)virtualCodes + (irq - INTERRUPT_VIRTUAL) * 0x10;
    registers.ds     = registers.es = registers.fs = registers.gs = 0;            // ds, es, fs, gs
    registers.cs     = (virtualCode >> 4) & 0xF000;                               // cs
    registers.eip    = virtualCode & 0xFFFF;                                      // ip
    registers.eflags = 0x20002;                                                   // flags (if disabled for now)
    registers.u.ss   = ((u32)virtualStack >> 4) & 0xF000;                      // ss
    registers.u.esp  = (u32)virtualStack & 0xFFFF;                             // sp
    registers.v.ds   = registers.v.es = registers.v.fs = registers.v.gs = 0x9000; // ds, es, fs, gs

    TSS_SetStack((u32*)&registers + 21);
}
void Interrupt_VirtualMonitor(InterruptHandlerParameters parameters, u32 irq, u32 gpf, InterruptHandlerRegisters registers)
{
    operand32 = address32 = false;

    // Conversion to linear addresses
    u16* stack = (u16*)(registers.u.esp + (registers.u.ss << 4));
    u8*  code  = (u8*)(registers.eip + (registers.cs << 4));
    u16* ivt   = (u16*)0;

    // 32 bits operand
    if (*code == 0x66)
    {
        operand32 = true;
        code++;
        registers.eip++;
    }

    // 32 bits address
    if (*code == 0x67)
    {
        address32 = true;
        code++;
        registers.eip++;
    }

    switch (code[0])
    {
        case 0xCD: // int
            //WriteLine("int %x", code[1]);

            // Set up new stack
            registers.u.esp -= 6;
            *stack-- = ((u32)code + 2) & 0xFFFF; // ip
            *stack-- = registers.cs;                // cs
            *stack   = registers.eflags;            // eflags

            // Handle virtual interrupt flag
            if (false && Task::Current->virtualInterrupt)
                *stack |= 1 << 9;
            else
                *stack &= ~(1 << 9);
            Task::Current->virtualInterrupt = false;

            // Jump directly to ivt
            registers.cs  = ivt[code[1] * 2 + 1];
            registers.eip = ivt[code[1] * 2];
            break;

        case 0xCF: // iret
            stack++;
            //WriteLine("iret");

            // Back to protected mode
            if (stack[8] == 0xFFFF && stack[9] == 0xFFFF && stack[10] == 0xFFFF)
            {
                _es = registers.v.es << 4;
                Task_Save(sizeof(parameters) / 4 + 2 + 5);
                Task::Current->type = TaskType::Kernel;
                Task_Restore(sizeof(parameters) / 4 + 2 + 5);
                _asm mov ebp, esp
                _asm add ebp, 20

                registers.esi = registers.esi & 0xFFFF | _es & 0xFFFF0000;
                registers.edi = registers.edi & 0xFFFF | _es & 0xFFFF0000;

                break;
            }

            registers.eip    = stack[2];
            registers.cs     = stack[1];
            registers.eflags = (1 << 17) | stack[0]; // (1 << 9)

            Task::Current->virtualInterrupt = (stack[0] & (1 << 9)) != 0;
            registers.u.esp += 6;
            break;

         case 0xFA: // cli
            Task::Current->virtualInterrupt = false;
            registers.eip++;
            break;

         case 0xFB: // sti
            Task::Current->virtualInterrupt = true;
            registers.eip++;
            break;

        default:
            Write("V86: Invalid OPCode %x\n", code[0]);
            for (;;);
            break;
    }
}
void Interrupt_Synchronization(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)
{
    u8 function = registers.eax;
    u32 i;

    switch (function)
    {
        #pragma region Criticals

        case TaskSynchronizationCommand::BeginCritical:
            Task::Current->mode = TaskMode::Critical;
            break;

        case TaskSynchronizationCommand::EndCritical:
            Task::Current->mode = TaskMode::Normal;
            break;

        #pragma endregion
        #pragma region Mutexes

        case TaskSynchronizationCommand::InitMutex:
            for (i = 0; i < MUTEX_MAX_COUNT; i++)
                if (!mutexes[i].Owner)
                    break;

            if (i == MUTEX_MAX_COUNT)
                registers.eax = -1;
            else
            {
                mutexes[i].Owner = Task::Current->id + 1;
                mutexes[i].Locker = 0;
                registers.eax = i == MUTEX_MAX_COUNT ? -1 : i;

#if DEBUG_TASKING
                Write("[%d] T%d : InitMutex %d\n", (u32)Timer::Ticks, Task::Current->id, i);
#endif
            }

            break;

        case TaskSynchronizationCommand::ReleaseMutex:
            i = registers.ebx;

            if (i >= MUTEX_MAX_COUNT || mutexes[i].Owner != Task::Current->id + 1)
                registers.eax = -1;
            else
            {
                mutexes[i].Owner = 0;
                mutexes[i].Locker = 0;

#if DEBUG_TASKING
                Write("[%d] T%d : ReleaseMutex %d\n", (u32)Timer::Ticks, Task::Current->id, i);
#endif
            }

            break;

        case TaskSynchronizationCommand::LockMutex:
            i = registers.ebx;
            //WriteLine("> Lock M%d from T%d", i, Task::Current->id);

            if (i >= MUTEX_MAX_COUNT)
                registers.eax = -1;
            else if (mutexes[i].Locker)
            {
                //Serial::WriteLine("> Mutex already locked");
                //Write("> Mutex already locked, switching from T%d to T", Task::Current->id);

                Task::Current->mode = TaskMode::LockMutex;
                Task::Current->data.Mutex.Id = i;

#if DEBUG_TASKING
                Write("[%d] T%d : LockMutex %d -> Waiting\n", (u32)Timer::Ticks, Task::Current->id, i);
#endif

                Task_Save(sizeof(parameters) / 4 + 5);
                Task::Switch();
                Task_Restore(sizeof(parameters) / 4 + 5);

                _asm mov ebp, esp
                _asm add ebp, 16
            }
            else
            {
                mutexes[i].Locker = Task::Current->id + 1;

#if DEBUG_TASKING
                Write("[%d] T%d : LockMutex %d\n", (u32)Timer::Ticks, Task::Current->id, i);
#endif
            }

            break;

        case TaskSynchronizationCommand::UnlockMutex:
            i = registers.ebx;
            //WriteLine("> Unlock M%d from T%d", i, Task::Current->id);

            if (i >= MUTEX_MAX_COUNT)// || mutexes[i].Locker != Task::Current->id + 1)
                registers.eax = -1;
            else
            {
                mutexes[i].Locker = 0;

#if DEBUG_TASKING
                Write("[%d] T%d : UnlockMutex %d\n", (u32)Timer::Ticks, Task::Current->id, i);
#endif
            }

            break;

        case TaskSynchronizationCommand::WaitMutex:
            i = registers.ebx;

            if (i >= MUTEX_MAX_COUNT)
                registers.eax = -1;
            else if (mutexes[i].Locker)
            {
                Task::Current->mode = TaskMode::WaitMutex;
                Task::Current->data.Mutex.Id = i;
            }

            break;

        case TaskSynchronizationCommand::WaitMutexTimeout:
            break;

        #pragma endregion
        #pragma region Signals

        case TaskSynchronizationCommand::InitSignal:
            for (i = 0; i < SIGNAL_MAX_COUNT; i++)
                if (!signals[i].Owner)
                    break;

            if (i == SIGNAL_MAX_COUNT)
                registers.eax = -1;
            else
            {
                signals[i].Owner = Task::Current->id + 1;
                signals[i].Sent = 0;
                registers.eax = i;
            }

            break;

        case TaskSynchronizationCommand::ReleaseSignal:
            i = registers.ebx;

            if (i >= SIGNAL_MAX_COUNT || signals[i].Owner != Task::Current->id + 1)
                registers.eax = -1;
            else
                mutexes[i].Owner = 0;
            break;

        case TaskSynchronizationCommand::SendSignal:
            i = registers.ebx;
            //i = 0;

            if (i >= SIGNAL_MAX_COUNT || !signals[i].Owner) // signals[i].Owner != Task::Current->id + 1)
                registers.eax = -1;
            else
            {
#if DEBUG_TASKING
                Write("[%d] T%d : SendSignal %d\n", (u32)Timer::Ticks, Task::Current->id, i);
#endif
                signals[i].Sent = Timer::Ticks;

                /*Task_Save(sizeof(parameters) / 4 + 5);
                Task::Switch();
                Task_Restore(sizeof(parameters) / 4 + 5);

                _asm mov ebp, esp
                _asm add ebp, 16*/
            }

            break;

        case TaskSynchronizationCommand::WaitSignal:
            i = registers.ebx;
            //i = 0;

            if (i >= SIGNAL_MAX_COUNT || !signals[i].Owner)
                registers.eax = -1;
            else
            {
#if DEBUG_TASKING
                Write("[%d] T%d : WaitSignal %d -> Waiting\n", (u32)Timer::Ticks, Task::Current->id, i);
#endif
                Task::Current->mode = TaskMode::WaitSignal;
                Task::Current->data.Signal.Id = i;
                Task::Current->data.Signal.Tick = Timer::Ticks;

                /*Task_Save(sizeof(parameters) / 4 + 5);
                Task::Switch();
                Task_Restore(sizeof(parameters) / 4 + 5);

                _asm mov ebp, esp
                _asm add ebp, 16*/
            }

            break;

        case TaskSynchronizationCommand::WaitSignalTimeout:
            break;

        #pragma endregion
    }
}

void Task::PreInitialize()
{
    Current = First = Kernel = new Task();

    Kernel->id = 0;
    Kernel->type = TaskType::Kernel;
    Kernel->mode = TaskMode::Normal;
    Kernel->state = TaskState::Running;
    Kernel->next = null;
    Kernel->tick = 0;

    Interrupt_AddRequestHandler(0x00, Interrupt_Clock);
    Interrupt_AddKernelHandler(KERNEL_INTERRUPT_TASKSYNCHRONIZATION, (InterruptHandler)Interrupt_Synchronization);
}
void Task::Initialize()
{
    Kernel->heap =  (void*)HEAP_BASE;
    Kernel->stack = (void*)KERNEL_STACK;
    Kernel->code =  (void*)KERNEL_BASE;
    Kernel->directory = (PageDirectory*)MEMORY_DIRECTORIES;

    Interrupt_AddRequestHandler(0x00, (InterruptHandler)Interrupt_TaskSwitch);
    Interrupt_AddKernelHandler(KERNEL_INTERRUPT_TASKSWITCH, (InterruptHandler)Interrupt_TaskSwitch);
    Interrupt_AddKernelHandler(KERNEL_INTERRUPT_TASKSYNCHRONIZATION, (InterruptHandler)Interrupt_TaskSwitch);
    Interrupt_AddSystemHandler((InterruptHandler)Interrupt_TaskSwitch);

    mutexes[0].Owner = 1;
    // V86
    for (int i = 0; i < 0x20; i++)
    {
        virtualCodes[i * 0x10 + 0] = 0xCD; // int
        virtualCodes[i * 0x10 + 1] = i;
        virtualCodes[i * 0x10 + 2] = 0x60; // pusha
        virtualCodes[i * 0x10 + 3] = 0xCF; // iret
        Interrupt_AddVirtualHandler(i, (InterruptHandler)Interrupt_VirtualHandler);
    }
    Interrupt_AddExceptionHandler(0x0D, (InterruptHandler)Interrupt_VirtualMonitor);

    // Thread
    Kernel->thread = new KernelThread(Kernel, "Main");
    KernelThread::SetCurrent(Kernel->thread);

    // Process
    KernelProcess* process = new KernelProcess((PageDirectory*)MEMORY_DIRECTORIES, "Kernel");
    KernelProcess::SetCurrent(process);
    //process->Threads.Add(System::Runtime::Thread::Current);
}
void Task::PostInitialize()
{
    Kernel->tick = -1;
}

void Task::Suspend(u64 milliseconds)
{
    Current->tick = Timer::Time() + (milliseconds / FRENQUENCY_DIVIDER);
    _asm int INTERRUPT_KERNEL
}
void Task::Switch()
{
    Task* task;

#if DEBUG_TASKING
    //WriteLine();
    //DumpTask("Before")
#endif

    // Reschedule the task
    if (Task::Current != Task::Kernel && Task::Current->tick <= Timer::Ticks)
        Task::Current->tick = Timer::Ticks + 1;

#if DEBUG_TASKING
    //WriteLine("[%d] T%d : Rescheduled at %d", (u32)Timer::Ticks, Task::Current->id, Task::Current->tick);
#endif

    // Remove the task from this list
    /*if (Task::Current == Task::Kernel);
    else */if (Task::Current == Task::First)
        Task::First = Task::First->next;
    else
    {
        task = Task::First;

        while (task->next != Task::Current)
            task = task->next;

        task->next = Task::Current->next;
    }

#if DEBUG_TASKING
    //DumpTask("Removed")
#endif

    // Insert the task in the list
    if (/*Task::Current == Task::Kernel || */Task::Current->state == TaskState::Ended);
    else if (Task::Current->tick < Task::First->tick)
    {
        Task::Current->next = Task::First;
        Task::First = Task::Current;
    }
    else
    {
        task = Task::First;

        while (task->next && task->next->tick <= Task::Current->tick)
            task = task->next;

        Task::Current->next = task->next;
        task->next = Task::Current;
    }

#if DEBUG_TASKING
    //DumpTask("Inserted")
#endif

    // Find the next task to run
    task = Task::First;
    while (task && task->id && task->tick <= Timer::Ticks)
    {
        if (task->state != TaskState::Running)
            continue;
        if (task->mode == TaskMode::Normal)
            break;

        // LockMutex
        if (task->mode == TaskMode::LockMutex && !mutexes[task->data.Mutex.Id].Locker)
        {
            mutexes[task->data.Mutex.Id].Locker = task->id + 1;
            task->mode = TaskMode::Normal;
            
#if DEBUG_TASKING
            Write("[%d] T%d : LockMutex %d -> Acquired lock\n", (u32)Timer::Ticks, task->id, task->data.Mutex.Id);
#endif
            break;
        }

        // WaitMutex
        if (task->mode == TaskMode::WaitMutex && !mutexes[task->data.Mutex.Id].Locker)
        {
            task->mode = TaskMode::Normal;
            
#if DEBUG_TASKING
            Write("[%d] T%d : WaitMutex %d -> Lock is free\n", (u32)Timer::Ticks, task->id, task->data.Mutex.Id);
#endif
            break;
        }

        // WaitSignal
        if (task->mode == TaskMode::WaitSignal && signals[task->data.Signal.Id].Sent > task->data.Signal.Tick)
        {
            task->mode = TaskMode::Normal;

#if DEBUG_TASKING
            Write("[%d] T%d : WaitSignal %d -> Caught signal\n", (u32)Timer::Ticks, task->id, task->data.Signal.Id);
#endif
            break;
        }

        task = task->next;
    }
    Task::Current = task;

    // If no task were found, use kernel task
    if (!Task::Current || Task::Current->tick > Timer::Ticks)//|| Task::Current->mode != TaskMode::Normal)
        Task::Current = Task::Kernel;

    // Load task's thread and process
    KernelThread::SetCurrent(Task::Current->thread);
    KernelProcess::SetCurrent((KernelProcess*)Task::Current->thread->Process);

#if DEBUG_TASKING
    //DumpTask("After")

    for (u32 i = 0; i < 10000000; i++)
        _asm nop
#endif
}
void Task::BeginCritical()
{
    u32 function = (u8)TaskSynchronizationCommand::BeginCritical;

    _asm mov eax, [function]
    _asm int INTERRUPT_KERNEL + KERNEL_INTERRUPT_TASKSYNCHRONIZATION
}
void Task::EndCritical()
{
    u32 function = (u8)TaskSynchronizationCommand::EndCritical;

    _asm mov eax, [function]
    _asm int INTERRUPT_KERNEL + KERNEL_INTERRUPT_TASKSYNCHRONIZATION
}

bool Task::IsInterrupt()
{
	return interrupt_interrupting;
}

Task::Task() { }
Task::Task(TaskType type, void* pointer, void* stack, void* heap, PageDirectory* directory) : id(_id++), type(type), tick(0), state(TaskState::Paused), mode(TaskMode::Normal), directory(directory)
{
    this->code = pointer;
    this->stack = stack;
    this->heap = heap;

    if (type == TaskType::User)
        this->directory = (PageDirectory*)0x801000;

    switch (type)
    {
        case TaskType::Kernel:
            cpu.cs = 0x08;
            cpu.ss = cpu.ds = 0x10;
            cpu.eflags = 0x00000202;
            break;

        case TaskType::User:
            cpu.cs = 0x18 + 0x03;
            cpu.ss = cpu.ds = 0x20 + 0x03;
            cpu.eflags = 0x00000202;
            break;

        case TaskType::Virtual:
            cpu.cs = ((u32)code >> 4) & 0xF000;
            cpu.ss = ((u32)stack >> 4) & 0xF000;
            cpu.ds = ((u32)heap >> 4) & 0xF000;
            this->code = (void*)((u32)code & 0xFFFF);
            this->stack = (void*)((u32)stack & 0xFFFF);
            cpu.eflags = 0x00020002; // 20202
            virtualInterrupt = false;
            break;
    }

    cpu.eip = (u32)code; //Task_Run;
    cpu.ebp = cpu.esp = (u32)stack;
    cpu.es = cpu.fs = cpu.gs = cpu.ds;

    _asm fxsave _fpu
    Memory::Copy(_fpu, fpu, 512);
}

void Task::Run()
{
    if (state != TaskState::Paused)
        return;

    _asm cli

    next = Task::First;
    Task::First = this;
    state = TaskState::Running;

    //Task::Current->lastSwitch = Timer::Ticks;

    //_asm int INTERRUPT_TASK_SWITCH

    _asm sti
}
void Task::Kill()
{

}

u32 *_esp, _eip, _ebp, _esi, _edi;
u8* _floats;
Task* task;
InterruptHandlerRegisters* registers;

u32 i, j;
u32 temp[256];

void _declspec(naked) Task_Save(u32 prefixSize)
{
    _asm mov [_esp], esp
    _asm mov [_ebp], ebp
    
    // Save float registers
    _esi = (u32)_fpu;
    _edi = (u32)Task::Current->fpu;
    _asm
    {
        fxsave _fpu
        mov esi, _esi
        mov edi, _edi
        mov ecx, 128
        rep movsd
    }

    // Backup interrupt parameters
    j = _esp[1] + 4;
    for (i = 0; i < j; i++)
        temp[i] = _esp[i];

    // Save task registers
    registers = (InterruptHandlerRegisters*)((u32)_esp + j * 4);
    Task::Current->cpu.edi = registers->edi;
    Task::Current->cpu.esi = registers->esi;
    Task::Current->cpu.ebp = registers->ebp;
    Task::Current->cpu.ebx = registers->ebx;
    Task::Current->cpu.edx = registers->edx;
    Task::Current->cpu.ecx = registers->ecx;
    Task::Current->cpu.eax = registers->eax;

    if (Task::Current->type != TaskType::Virtual)
    {
        Task::Current->cpu.gs  = registers->gs;
        Task::Current->cpu.fs  = registers->fs;
        Task::Current->cpu.ds  = registers->ds;
        Task::Current->cpu.es  = registers->es;
        Task::Current->cpu.eip = registers->eip;
        Task::Current->cpu.cs  = registers->cs;
        Task::Current->cpu.eflags = registers->eflags;
    }

    // Save specific registers
    switch (Task::Current->type)
    {
        case TaskType::Kernel:
            Task::Current->cpu.esp = registers->esp + 12;
            _esp += 15;
            _ebp += 15;
            break;

        case TaskType::User:
            Task::Current->cpu.esp = registers->esp + 20;
            Task::Current->cpu.esp = registers->u.esp;
            Task::Current->cpu.ss  = registers->u.ss;
            _esp += 17;
            _ebp += 17;
            break;

        case TaskType::Virtual:
            _esp += 21;
            _ebp += 21;
            break;
    }

    // Restore the stack
    for (i = 0; i < j; i++)
        _esp[i] = temp[i];

    _asm mov esp, [_esp]
    _asm mov ebp, [_ebp]
    _asm ret
}
void _declspec(naked) Task_Restore(u32 prefixSize)
{
    _asm mov [_esp], esp
    _asm mov [_ebp], ebp

    if (Task::Current->id)
        ;//for (;;);

    // Switch tasks for kernel tasks
    if (Task::Current->type == TaskType::Kernel)
    {
        u32 stack = Task::Current->cpu.esp - 0x20;
        _asm mov esp, [stack]
    }

    // Change directory
    // FIXME : This fucking code won't work !!!!!!
    //for(;;);
    *(u32*)(SHARED_CODE + 1) = (u32)Task::Current->directory;

    // Backup interrupt parameters
    j = _esp[1] + 4;
    for (i = 0; i < j; i++)
        temp[i] = _esp[i];
    _asm mov [_esp], esp

    // Stack correction
    switch (Task::Current->type)
    {
        case TaskType::Kernel:  _esp -= 15; _ebp -= 15; break;
        case TaskType::User:    _esp -= 17; _ebp -= 17; break;
        case TaskType::Virtual: _esp -= 21; _ebp -= 21; break;
    }

    // Save task registers
    registers = (InterruptHandlerRegisters*)((u32)_esp + j * 4);
    registers->gs  = Task::Current->cpu.gs;
    registers->fs  = Task::Current->cpu.fs;
    registers->ds  = Task::Current->cpu.ds;
    registers->es  = Task::Current->cpu.es;
    registers->edi = Task::Current->cpu.edi;
    registers->esi = Task::Current->cpu.esi;
    registers->ebp = Task::Current->cpu.ebp;
    registers->ebx = Task::Current->cpu.ebx;
    registers->edx = Task::Current->cpu.edx;
    registers->ecx = Task::Current->cpu.ecx;
    registers->eax = Task::Current->cpu.eax;
    registers->eip = Task::Current->cpu.eip;
    registers->cs  = Task::Current->cpu.cs;
    registers->eflags = Task::Current->cpu.eflags;// | 0x200;

    // Copie des registres spécifiques
    switch (Task::Current->type)
    {
        case TaskType::Kernel:
            registers->esp = Task::Current->cpu.esp + 12;
            break;

        case TaskType::User:
            registers->esp   = Task::Current->cpu.esp + 20;
            registers->u.esp = Task::Current->cpu.esp;
            registers->u.ss  = Task::Current->cpu.ss;
            break;

        case TaskType::Virtual:
            registers->esp   = Task::Current->cpu.esp + 36;
            registers->v.es  = Task::Current->cpu.es;
            registers->v.ds  = Task::Current->cpu.ds;
            registers->v.fs  = Task::Current->cpu.fs;
            registers->v.gs  = Task::Current->cpu.gs;
            registers->u.esp = Task::Current->cpu.esp;
            registers->u.ss  = Task::Current->cpu.ss;
            break;
    }

    // Restore the stack
    for (i = 0; i < j; i++)
        _esp[i] = temp[i];

    // Restore float registers
    _esi = (u32)Task::Current->fpu;
    _edi = (u32)_fpu;
    _asm
    {
        mov esi, _esi
        mov edi, _edi
        mov ecx, 128
        rep movsd
        fxrstor _fpu
    }

    _asm mov esp, [_esp]
    _asm mov ebp, [_ebp]
    _asm ret
}

#pragma optimize("", on)

#endif