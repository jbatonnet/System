#include <Kernel/Runtime/Threading/Thread.h>
#include <Kernel/Runtime/Threading/Task.h>

#include <System/Runtime/Threading/Process.h>
#include <System/Runtime/Threading/Dispatcher.h>
#include <System/Utilities/Time/Timer.h>
#include <System/Debugging/Console.h>

using namespace System::Runtime;

namespace
{
    u32 _id = 0;
    KernelThread* _current = null;
}

KernelThread::KernelThread(Task* task, const string& name) : id(_id++), task(task), name(name), dispatcher(null)
{
}
KernelThread::KernelThread(const Action<>& function, const string& name) : id(_id++), name(name), dispatcher(null)
{
    void* stack = Memory::Allocate(0x4000);
    task = new Task(Task::Current->type, function.GetPointer(), (void*)((u32)stack + 0x4000 - 4), Task::Current->heap, Task::Current->directory);
    task->thread = this;

    // FIXME: Forbid GetPointer() !!!, Should run a task with action
    //Process::Current->Threads.Add(this);

    //Console::WriteLine("[{0}] T{1} : Thread {2}", (u32)Timer::Time(), task->id, name);
}

void KernelThread::Start()
{
    task->Run();
}
void KernelThread::Kill()
{
    task->Kill();
}

Thread* Thread::Create(const Action<>& function, const string& name)
{
    return new KernelThread(function, name);
}
Thread* Thread::Start(const Action<>& function, const string& name)
{
    Thread* thread = new KernelThread(function, name);
    thread->Start();
    return thread;
}

Thread* Thread::GetCurrent()
{
    return _current;
}
void KernelThread::SetCurrent(KernelThread* thread)
{
    _current = thread;
}