#include <Kernel/Runtime/Threading/Process.h>

#include <Kernel/Memory/PMM.h>
#include <Kernel/Memory/VMM.h>
#include <HAL/Utilities.h>

using namespace System::Runtime;

namespace
{
    u32 _id = 0;
    List<KernelProcess*> _processes;
    KernelProcess* _current = null;
}

KernelProcess::KernelProcess(PageDirectory* directory, const string& name) : id (_id++), directory(directory), name(name)
{
    _processes.Add(this);

    // New directory
    //PageDirectory* directory = VMM_GetDirectory();
    //PageTable* sharedTable = VMM_GetTable();

    // Shared stack
    /*PageTableEntry* tableEntry = &sharedTable->Entries[SHARED_PAGE - 1];
    AddFlag(*tableEntry, PTE_PRESENT);
    SetFrame(tableEntry, (void*)((SHARED_PAGE - 1) * 0x1000));

    // Shared code
    tableEntry = &sharedTable->Entries[SHARED_PAGE];
    AddFlag(*tableEntry, PTE_PRESENT);
    SetFrame(tableEntry, (void*)(SHARED_PAGE * 0x1000));

    // Code space
    for (u32 page = 0; page < 256; page++)
    {
        void* physicalMemory = PMM_AllocateBlock();

        PageTableEntry* tableEntry = &sharedTable->Entries[0x100 + page];
        AddFlag(*tableEntry, PTE_PRESENT);
        AddFlag(*tableEntry, PTE_WRITABLE);
        AddFlag(*tableEntry, PTE_USERMODE);
        SetFrame(tableEntry, physicalMemory);
    }*/
}

void KernelProcess::Start()
{
}
void KernelProcess::Kill()
{
}

Process* Process::GetCurrent()
{
    return _current;
}
void KernelProcess::SetCurrent(KernelProcess* process)
{
    _current = process;
}