#ifndef _KERNEL_VMM_H_
#define _KERNEL_VMM_H_

#include <HAL/HAL.h>

// Page tables
#define PTE_PRESENT       (1 << 0)
#define PTE_WRITABLE      (1 << 1)
#define PTE_USERMODE      (1 << 2)
#define PTE_WRITETHROUGH  (1 << 3)
#define PTE_NOT_CACHEABLE (1 << 4)
#define PTE_ACCESSED      (1 << 5)
#define PTE_DIRTY         (1 << 6)
#define PTE_PAT           (1 << 7)
#define PTE_CPU_GLOBAL    (1 << 8)
#define PTE_LV4_GLOBAL    (1 << 9)

typedef u32 PageTableEntry;
struct PageTable
{
    PageTableEntry Entries[1024];
};

// Page directories
#define PDE_PRESENT    (1 << 0)
#define PDE_WRITABLE   (1 << 1)
#define PDE_USERMODE   (1 << 2)
#define PDE_PWT        (1 << 3)
#define PDE_PCD        (1 << 4)
#define PDE_ACCESSED   (1 << 5)
#define PDE_DIRTY      (1 << 6)
#define PDE_4MB        (1 << 7)
#define PDE_CPU_GLOBAL (1 << 8)
#define PDE_LV4_GLOBAL (1 << 9)

typedef u32 PageDirectoryEntry;
struct PageDirectory
{
    PageDirectoryEntry Entries[1024];
};

#define FRAME_MASK 0xFFFFF000

inline void SetFrame(u32* entry, void* address)
{
    *entry = (*entry & ~FRAME_MASK) | (u32)address;
}
inline void* GetFrame(u32 entry)
{
    return (void*)(entry & FRAME_MASK);
}

typedef u32 VirtualAddress;

#define PAGE_DIRECTORY_INDEX(address) (((address) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(address) (((address) >> 12) & 0x3ff)
#define PAGE_PHYSICAL_ADDRESS(address) (*address & ~0xfff)

void VMM_MapPage(void* physicalAddress, void* virtualAddress);
void VMM_Initialize();
void VMM_InitializeVideo(void* address);
void VMM_FlushTLB(void* address);
void VMM_Flush();

PageDirectory* VMM_GetDirectory();
PageTable* VMM_GetTable();

extern PageDirectory* currentDirectory;


class MemoryMapping
{
    struct MemoryPage
    {
        void* Blocks[1024];
    };
    struct MemoryDirectory
    {
        MemoryPage* Pages[1024];
    };

private:
    MemoryDirectory reversedPageDirectory;
    
    u32 memoryBlockCount;

public:
    PageDirectory* pageDirectory;

    MemoryMapping();
    MemoryMapping(PageDirectory* pageDirectory);
    MemoryMapping(MemoryMapping* other);

    void Map(void* physicalAddress, void* virtualAddress, bool writable = true, bool userMode = true);
    void Map(void* physicalAddress, void* virtualAddress, u32 size, bool writable = true, bool userMode = true);
    void Allocate(void* virtualAddress, u32 size, bool writable = true, bool userMode = true);

    inline void* GetPhysicalAddress(void* virtualAddress);
    inline void* GetVirtualAddress(void* virtualAddress);
};



#endif