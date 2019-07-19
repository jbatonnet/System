#include "PE.h"

#include <System/System.h>

#include <HAL/Utilities.h>
#include <Kernel/Memory/PMM.h>
#include <Kernel/Memory/VMM.h>
#include <Kernel/Config.h>

using namespace System::IO;
using namespace System::Runtime;

Executable* PEExecutable::Load(const string& path)
{
    return Load(File::OpenStream(path));
}
Executable* PEExecutable::Load(File* file)
{
    return file ? Load(file->GetStream()) : null;
}
Executable* PEExecutable::Load(Stream* stream)
{
    if (!stream)
        return null;

    DataStream* data = new DataStream(stream);

    // MZ tag
    string mzTag = data->ReadString(2);
    if (mzTag != "MZ")
    {
        delete data;
        return null;
    }

    PEExecutable* executable = new PEExecutable();

    // DOS header
    Console::WriteLine("dosHeader - 0002");
    data->SetPosition(0);
    executable->dosHeader = Memory::Allocate<PE_DosHeader>();
    data->Read(executable->dosHeader);

    //Console::WriteLine("  PeHeader: {0}", (u32)data->Position);

    // PE header
    //Console::WriteLine("peHeader - {0:X4}", (u32)data->Position);
    data->SetPosition(executable->dosHeader->PeHeader);
    executable->peHeader = Memory::Allocate<PE_PeHeader>();
    data->Read(executable->peHeader);

    Console::WriteLine("  FileHeader.SectionsCount: {0}", executable->peHeader->FileHeader.SectionsCount);

    // Sections
    u32 sectionsTable = executable->dosHeader->PeHeader + sizeof(PE_PeHeader) - sizeof(PE_PeOptionalHeader) + executable->peHeader->FileHeader.OptionalHeaderSize;
    for (u32 i = 0; i < executable->peHeader->FileHeader.SectionsCount; i++)
    {
        data->SetPosition(sectionsTable + i * sizeof(PE_PeSection));
        //Console::WriteLine("peSection - {0:X4}", (u32)data->Position);

        PE_PeSection* peSection = Memory::Allocate<PE_PeSection>();
        data->Read(peSection);

        Console::WriteLine("  Name: {0}", peSection->Name);
        Console::WriteLine("  VirtualSize: {0:X8}", peSection->VirtualSize);
        Console::WriteLine("  PhysicalAddress: {0:X8}", peSection->PhysicalAddress);
        Console::WriteLine("  VirtualAddress: {0:X8}", peSection->VirtualAddress);

        //executable->sections.Add(section);
    }

    Console::WriteLine("Done");
    for (;;);

    return executable;
}

Process* PEExecutable::CreateProcess()
{
    #pragma region Memory stuff

    #define USER_CODE   0x00100000 //  1 Mo
    #define KERNEL_CODE 0x02000000 // 32 Mo
    #define CODE_SIZE   0x00020000
    #define SHARED_SIZE 0x00100000 //  1 Mo

    PageDirectory* userDirectory = VMM_GetDirectory();
    PageDirectory* kernelDirectory = (PageDirectory*)MEMORY_DIRECTORIES;
    Memory::Copy<PageDirectory>(kernelDirectory, userDirectory);

    // Add shared space
    PageTable* userSharedTable = VMM_GetTable();
    Memory::Copy<PageTable>((void*)MEMORY_TABLES, userSharedTable);

    PageDirectoryEntry* userDirectoryEntry = &userDirectory->Entries[0];
    AddFlag(*userDirectoryEntry, PTE_PRESENT);
AddFlag(*userDirectoryEntry, PTE_WRITABLE);
AddFlag(*userDirectoryEntry, PTE_USERMODE);
    SetFrame(userDirectoryEntry, userSharedTable);

    for (u32 pageIndex = 0; pageIndex < SHARED_SIZE / 0x1000; pageIndex++)
    {
        PageTableEntry* userSharedTableEntry = &userSharedTable->Entries[pageIndex];
        AddFlag(*userSharedTableEntry, PTE_PRESENT);
AddFlag(*userSharedTableEntry, PTE_WRITABLE);
AddFlag(*userSharedTableEntry, PTE_USERMODE);
        SetFrame(userSharedTableEntry, (void*)(pageIndex * 0x1000));
    }

    /*PageTableEntry* userSharedTableEntry = &userSharedTable->Entries[SHARED_PAGE - 1];
    AddFlag(*userSharedTableEntry, PTE_PRESENT);
AddFlag(*userSharedTableEntry, PTE_WRITABLE);
AddFlag(*userSharedTableEntry, PTE_USERMODE);
    SetFrame(userSharedTableEntry, (void*)((SHARED_PAGE - 1) * 0x1000));
    userSharedTableEntry = &userSharedTable->Entries[SHARED_PAGE];
    AddFlag(*userSharedTableEntry, PTE_PRESENT);
AddFlag(*userSharedTableEntry, PTE_WRITABLE);
AddFlag(*userSharedTableEntry, PTE_USERMODE);
    SetFrame(userSharedTableEntry, (void*)(SHARED_PAGE * 0x1000));*/

    // Allocate code space
    PageTable* userCodeTable = userSharedTable;
    PageTable* kernelCodeTable = VMM_GetTable();

    PageDirectoryEntry* kernelDirectoryEntry = &kernelDirectory->Entries[KERNEL_CODE / 0x400000];
    AddFlag(*kernelDirectoryEntry, PTE_PRESENT);
    AddFlag(*kernelDirectoryEntry, PTE_WRITABLE);
AddFlag(*kernelDirectoryEntry, PTE_USERMODE);
    SetFrame(kernelDirectoryEntry, kernelCodeTable);

    for (u32 pageIndex = 0; pageIndex < CODE_SIZE / 0x1000; pageIndex++)
    {
        void* physicalMemory = PMM_AllocateBlock();

        PageTableEntry* userCodeTableEntry = &userCodeTable->Entries[USER_CODE / 0x1000 + pageIndex];
        AddFlag(*userCodeTableEntry, PTE_PRESENT);
        AddFlag(*userCodeTableEntry, PTE_WRITABLE);
        AddFlag(*userCodeTableEntry, PTE_USERMODE);
        SetFrame(userCodeTableEntry, physicalMemory);

        PageTableEntry* kernelCodeTableEntry = &kernelCodeTable->Entries[(KERNEL_CODE % 0x400000) / 0x1000 + pageIndex];
        AddFlag(*kernelCodeTableEntry, PTE_PRESENT);
        AddFlag(*kernelCodeTableEntry, PTE_WRITABLE);
AddFlag(*kernelCodeTableEntry, PTE_USERMODE);
        SetFrame(kernelCodeTableEntry, physicalMemory);
    }

    // Allocate heap space
    /*for (u32 tableIndex = HEAP_BASE / 0x400000; tableIndex < HEAP_LIMIT / 0x400000; tableIndex++)
    {
        PageTable* heapTable = VMM_GetTable();
        Memory::Clear<PageTable>(heapTable);

        for (u32 pageIndex = 0; pageIndex < 1024; pageIndex++)
        {
            PageTableEntry* tableEntry = &heapTable->Entries[pageIndex];
            AddFlag(*tableEntry, PTE_PRESENT);
            AddFlag(*tableEntry, PTE_WRITABLE);
            AddFlag(*tableEntry, PTE_USERMODE);
            SetFrame(tableEntry, (void*)(tableIndex * 0x400000 + pageIndex * 0x1000));
        }

        PageDirectoryEntry* directoryEntry = &userDirectory->Entries[tableIndex];
        AddFlag(*directoryEntry, PDE_PRESENT);
        AddFlag(*directoryEntry, PDE_WRITABLE);
        AddFlag(*directoryEntry, PDE_USERMODE);
        SetFrame(directoryEntry, heapTable);
    }*/

    // Refresh TLB
    _asm
    {
        mov eax, cr3
        mov cr3, eax
    }

    #pragma endregion

    // Setup the code space

    // Setup the stack


    //Task* task = new Task(TaskType::User, (void*)peHeader->OptionalHeader.AddressOfEntryPoint, 

    //Process* process = new Process(userDirectory, "UserProcess");
    //Thread* thread = new Thread("UserThread");

    return null;
}