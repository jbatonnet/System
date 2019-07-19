#ifndef _KERNEL_PMM_H_
#define _KERNEL_PMM_H_

#include <System/Base/Types.h>
#include <Kernel/Multiboot.h>

#define PMM_BLOCK_SIZE 4096
#define MEMMAP_BLOCKS_PER_BYTE 8

struct MemoryRegion
{
    u32 Size;
    u32 AddressLo, AddressHi;
    u32 LengthLo, LengthHi;
    u32 Type;
};

void PMM_Initialize(MultibootInfo* bootInfo);
void PMM_EnablePaging(bool enable);
void PMM_LoadPDBR(void* pbdr);

void* PMM_AllocateBlock();
void* PMM_AllocateBlock(u32 count);

void PMM_FreeBlock(void* block);
void PMM_FreeBlock(void* block, u32 count);

u32 PMM_GetTotalMemory();
u32 PMM_GetFreeMemory();

#endif