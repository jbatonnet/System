#ifndef _KERNEL_THREAD_H_
#define _KERNEL_THREAD_H_

#include <System/Base/Types.h>
#include <System/Base/String.h>
#include <System/Base/Functions.h>

#include <System/Runtime/Threading/Thread.h>
#include <System/Runtime/Threading/Process.h>
#include <System/Runtime/Threading/Dispatcher.h>

class Task;

class KernelThread : public System::Runtime::Thread
{
    friend class Task;

private:
    u32 id;
    string name;
    Task* task;
    System::Runtime::Process* process;
    System::Runtime::Dispatcher* dispatcher;


public:
    KernelThread(Task* task, const string& name = "");
    KernelThread(const Action<>& function, const string& name = "");

    // Accessors
    virtual u32 GetId() const override { return id; }
    virtual string GetName() const override { return name; }
    virtual System::Runtime::Process* GetProcess() const override { return process; }
    virtual System::Runtime::Dispatcher* GetDispatcher() const override { return dispatcher; }
    virtual void SetDispatcher(System::Runtime::Dispatcher* value) override { dispatcher = value; }

    // Methods
    virtual void Start() override;
    virtual void Kill() override;

    // Static
    static void SetCurrent(KernelThread* thread);
};

#endif