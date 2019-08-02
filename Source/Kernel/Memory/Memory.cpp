#include <Kernel/Memory/Memory.h>
#include <System/Memory/Memory.h>

#include <Kernel/Memory/PMM.h>
#include <Kernel/Memory/VMM.h>
#include <Kernel/Memory/Heap.h>

typedef ClassicHeap MyHeap;

void Memory_Initialize(MultibootInfo* bootInfo)
{
    PMM_Initialize(bootInfo);
    VMM_Initialize();

    for (u32 i = HEAP_BASE; i < HEAP_BASE + HEAP_SIZE; i += 0x1000)
    {
        void* physical = PMM_AllocateBlock();
        VMM_MapPage(physical, (void*)i);
    }

	new ((void*)HEAP_BASE) MyHeap(HEAP_SIZE, true, false);
}
void* Memory_Translate(void* address, Task* fromTask, Task* toTask)
{
    /*PageDirectoryEntry& directoryEntry = from->Entries[address / 0x0];
    PageTable* table = (PageTable*)(directoryEntry & 0xFFFF0000);
    PageTableEntry& tableEntry = table->Entries[address / 0x0 % 0x0];

    void* physical = (void*)tableEntry;*/

    if ((u32)address > 0xC0000000)
        return address;
    else
        return (void*)((u32)address + 0x02000000 - 0x00100000);
}

void* operator new(u32 size)
{
    return Memory::Allocate(size, 0);
}
void* operator new[](u32 size)
{
    return Memory::Allocate(size, 0);
}
void operator delete(void* pointer)
{
    if (pointer)
        Memory::Free(pointer);
}
void operator delete(void* pointer, u32)
{
	if (pointer)
        Memory::Free(pointer);
}
void operator delete[](void* pointer)
{
    if (pointer)
        Memory::Free(pointer);
}
void operator delete[](void* pointer, u32)
{
	if (pointer)
		Memory::Free(pointer);
}

void* Memory::Allocate(u32 size, s16 value)
{
    void* address = ((MyHeap*)HEAP_BASE)->Allocate(size);
    if (value >= 0 && value <= 0xFF)
        Memory::Clear(address, size);

    return address;
}
void Memory::Free(void* address)
{
    ((MyHeap*)HEAP_BASE)->Free(address);
}

extern "C" void* memset(void* ptr, int value, size_t num)
{
    Memory::Clear(ptr, num, value); // FIXME
    //Memory::Set(ptr, value, num);
    return ptr;
}
extern "C" void* memcpy(void* dst, const void* src, size_t num)
{
    Memory::Copy((void*)src, dst, num);
    return dst;
}