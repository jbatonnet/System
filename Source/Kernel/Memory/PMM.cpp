#include "PMM.h"

#include <Kernel/Kernel.h>
#include <Kernel/Config.h>

u32 memorySize = 0;
u32* memoryMap = (u32*)MEMORY_MAP;

u32 freeBlocks = 0;
u32 totalBlocks = 0;

inline void MMap_Set(u32 bit)
{
    memoryMap[bit / 32] |= (1 << (bit % 32));
}
inline void MMap_Unset(u32 bit)
{
    memoryMap[bit / 32] &= ~(1 << (bit % 32));
}
inline bool MMap_Test(u32 bit)
{
    return memoryMap[bit / 32] & (1 << (bit % 32));
}

void PMM_Initialize(MultibootInfo* bootInfo)
{
    memorySize = 1024 + bootInfo->MemoryLo + bootInfo->MemoryHi;
    Memory::Clear(memoryMap, 0x20000, 0xFF);

    // Detect memory regions
    MemoryRegion* region = (MemoryRegion*)bootInfo->MemoryMapAddress;
    for (; (u32)region < bootInfo->MemoryMapAddress + bootInfo->MemoryMapLength; region = (MemoryRegion*)((u32)region + region->Size + sizeof(u32)))
    {
        if (region->Type != 1)
            continue;

        u32 address = region->AddressLo / PMM_BLOCK_SIZE;
        u32 length = region->LengthLo / PMM_BLOCK_SIZE;

        //WriteLine("Region: { Address: 0x%x, Length: 0x%x }", address * PMM_BLOCK_SIZE, length * PMM_BLOCK_SIZE);

        for (u32 j = 0; j < length; j++)
        {
            MMap_Unset(address + j);
            totalBlocks++;
        }
    }
    freeBlocks = totalBlocks;
    //loop

    // Lock 0 - 1 Mo
    for (u32 i = 0; i < 0x100; i++)
    {
        if (!MMap_Test(i))
            freeBlocks--;

        MMap_Set(i);
    }

    // Lock 1 - 16 Mo
    for (u32 i = 0x100; i < 0x1000; i++)
    {
        if (MMap_Test(i))
        {
            Write("ERROR: Trying to lock an unavailable memory block : 0x%x\n", i * 0x1000);
            loop
        }

        freeBlocks--;
        MMap_Set(i);
    }
}
void PMM_EnablePaging(bool b)
{
    _asm
    {
        mov	eax, cr0
        cmp [b], 1
        je	enable
        jmp disable
enable:
        or eax, 0x80000000
        mov	cr0, eax
        jmp done
disable:
        and eax, 0x7FFFFFFF
        mov	cr0, eax
done:
    }

}
void PMM_LoadPDBR(void* pbdr)
{
    _asm
    {
        mov	eax, [pbdr]
        mov	cr3, eax
    }
}

u32 PMM_GetTotalMemory()
{
    return totalBlocks * PMM_BLOCK_SIZE;
}
u32 PMM_GetFreeMemory()
{
    return freeBlocks * PMM_BLOCK_SIZE;
}

void* PMM_AllocateBlock()
{
    if (freeBlocks == 0)
        return null;

    // Find free memory
    for (int i = 0; i < totalBlocks; i++)
        if (!MMap_Test(i))
        {
            MMap_Set(i);
            freeBlocks--;
            return (void*)(i * PMM_BLOCK_SIZE);
        }

    return null;
}
void* PMM_AllocateBlock(u32 count)
{
    u32 start = 0;
    u32 total = 0;

    if (freeBlocks < count)
        return null;

    // Find contiguous memory
    for (int i = 0; i < totalBlocks; i++)
    {
        if (!MMap_Test(i))
            total++;
        else
        {
            start = i + 1;
            total = 0;
        }

        if (total == count)
        {
            for (int j = start; j < start + count; j++)
                MMap_Set(j);
            freeBlocks -= count;
            return (void*)(start * PMM_BLOCK_SIZE);
        }
    }

    return null;
}

void PMM_FreeBlock(void* block)
{
    u32 bit = (u32)block / PMM_BLOCK_SIZE;
    MMap_Unset(bit);
    freeBlocks++;
}
void PMM_FreeBlock(void* block, u32 count)
{
    u32 bit = (u32)block / PMM_BLOCK_SIZE;
    for (int i = bit; i < bit + count; i++)
        MMap_Unset(i);
    freeBlocks += count;
}