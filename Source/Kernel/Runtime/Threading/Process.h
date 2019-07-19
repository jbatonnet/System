#ifndef _KERNEL_PROCESS_H_
#define _KERNEL_PROCESS_H_

#include <System/Common.h>
#include <System/Structures/Collections/List.h>
#include <System/Runtime/Threading/Process.h>
#include <System/Runtime/Threading/Thread.h>

#include <Kernel/Memory/VMM.h>

class KernelProcess : public System::Runtime::Process
{
private:
    u32 id;
    string name;
    List<System::Runtime::Thread*> threads;

    PageDirectory* directory;
    void* kernelMapping;

public:
    KernelProcess(PageDirectory* directory, const string& name = "");

    virtual const Collection<System::Runtime::Thread*>& GetThreads() const override { return threads; }
    virtual void Start() override;
    virtual void Kill() override;

    // Static
    static void SetCurrent(KernelProcess* process);
};

#endif