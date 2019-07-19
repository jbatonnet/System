#include <HAL/Utilities.h>
#include <System/Memory/Memory.h>

#include "PMM.h"
#include "VMM.h"
#include "Memory.h"
#include "../Config.h"

#include "../Devices/Screen/Screen.h"

PageDirectory* directories = (PageDirectory*)MEMORY_DIRECTORIES;
PageTable* tables = (PageTable*)MEMORY_TABLES;

u8 directoriesMap[MEMORY_DIRECTORIES_COUNT / 8] = { 0 };
u8 tablesMap[MEMORY_TABLES_COUNT / 8] = { 0 };

PageDirectory* currentDirectory = 0;
void* currentPDBR = 0;

bool VMM_AllocPage(PageTableEntry* page)
{
    void* block = PMM_AllocateBlock();
    if (!block)
        return false;

    SetFrame(page, block);
    AddFlag(*page, PTE_PRESENT);

    return true;
}
void VMM_FreePage(PageTableEntry* page)
{
    void* address = GetFrame(*page);
    if (address)
        PMM_FreeBlock(address);
    RemoveFlag(*page, PTE_PRESENT);
}

inline PageTableEntry* VMM_FindTableEntry(PageTable* table, VirtualAddress address)
{
    if (!table)
        return null;
    return &table->Entries[PAGE_TABLE_INDEX(address)];
}
inline PageDirectoryEntry* VMM_FindDirectoryEntry(PageDirectory* directory, VirtualAddress address)
{
    if (!directory)
        return null;
    return &directory->Entries[PAGE_TABLE_INDEX(address)]; // FIXME: Directory ??
}

PageDirectory* VMM_GetDirectory()
{
    PageDirectory* directory = null;

    for (u32 i = 0; i < MEMORY_DIRECTORIES_COUNT; i++)
        if (!(directoriesMap[i / 8] & (1 << (i % 8))))
        {
            directoriesMap[i / 8] |= 1 << (i % 8);
            directory = &directories[i];
            break;
        }

    if (directory)
        Memory::Clear<PageDirectory>(directory);

    return directory;
}
PageTable* VMM_GetTable()
{
    PageTable* table = null;

    for (u32 i = 0; i < MEMORY_TABLES_COUNT; i++)
        if (!(tablesMap[i / 8] & (1 << (i % 8))))
        {
            tablesMap[i / 8] |= 1 << (i % 8);
            table = &tables[i];
            break;
        }

    if (table)
        Memory::Clear<PageTable>(table);

    return table;
}

bool VMM_SetDirectory(PageDirectory* directory)
{
    if (!directory)
        return false;

    currentDirectory = directory;
    currentPDBR = &currentDirectory->Entries;
    PMM_LoadPDBR(currentPDBR);
    return true;
}
void VMM_FlushTLB(void* address)
{
    _asm
    {
        cli
        invlpg address
        sti
    }
}
void VMM_MapPage(void* physicalAddress, void* virtualAddress)
{
    PageDirectoryEntry* entry = &currentDirectory->Entries[PAGE_DIRECTORY_INDEX((u32)virtualAddress)];

    if (!IsFlag(*entry, PDE_PRESENT))
    {
        PageTable* table = (PageTable*)VMM_GetTable();
        if (!table)
            return; // Out of memory

        Memory::Clear<PageTable>(table);

        AddFlag(*entry, PDE_PRESENT);
        AddFlag(*entry, PDE_WRITABLE);
        AddFlag(*entry, PDE_USERMODE); // FIXME: Only for testing purpose
        SetFrame(entry, table);
    }

    PageTable* table = (PageTable*)PAGE_PHYSICAL_ADDRESS(entry);
    PageTableEntry* page = &table->Entries[PAGE_TABLE_INDEX((u32)virtualAddress)];

    SetFrame(page, physicalAddress);
    AddFlag(*page, PTE_PRESENT);
    AddFlag(*page, PTE_WRITABLE);
    AddFlag(*page, PTE_USERMODE); // FIXME: Only for testing purpose

    VMM_FlushTLB(virtualAddress);
}
void VMM_Flush()
{
    _asm
    {
        mov eax, cr3
        mov cr3, eax
    }
}

void VMM_Initialize()
{
    Memory::Clear<PageDirectory>(directories, MEMORY_DIRECTORIES_COUNT);
    Memory::Clear<PageTable>(tables, MEMORY_TABLES_COUNT);

    PageDirectory* kernelDirectory = VMM_GetDirectory();

    // Initialize kernel space (0 - 16 Mo)
    for (u32 tableIndex = 0; tableIndex < MEMORY_LIMIT / 0x400000; tableIndex++)
    {
        PageTable* kernelTable = VMM_GetTable();

        for (u32 pageIndex = 0; pageIndex < 1024; pageIndex++)
        {
            PageTableEntry* tableEntry = &kernelTable->Entries[pageIndex];
            AddFlag(*tableEntry, PTE_PRESENT);
            AddFlag(*tableEntry, PTE_WRITABLE);
            AddFlag(*tableEntry, PTE_USERMODE); // FIXME: Only for testing purpose
            SetFrame(tableEntry, (void*)(tableIndex * 0x400000 + pageIndex * 0x1000));
        }

        PageDirectoryEntry* directoryEntry = &kernelDirectory->Entries[tableIndex];
        AddFlag(*directoryEntry, PDE_PRESENT);
        AddFlag(*directoryEntry, PDE_WRITABLE);
        AddFlag(*directoryEntry, PDE_USERMODE); // FIXME: Only for testing purpose
        SetFrame(directoryEntry, kernelTable);
    }

    // Initialize video space (0xE8000000)
    for (u32 tableIndex = VIDEO_BASE / 0x400000; tableIndex < VIDEO_LIMIT / 0x400000; tableIndex++)
    {
        PageTable* kernelTable = VMM_GetTable();

        for (u32 pageIndex = 0; pageIndex < 1024; pageIndex++)
        {
            PageTableEntry* tableEntry = &kernelTable->Entries[pageIndex];
            AddFlag(*tableEntry, PTE_PRESENT);
            AddFlag(*tableEntry, PTE_WRITABLE);
            AddFlag(*tableEntry, PTE_USERMODE); // FIXME: Only for testing purpose
            SetFrame(tableEntry, (void*)(tableIndex * 0x400000 + pageIndex * 0x1000));
        }

        PageDirectoryEntry* directoryEntry = &kernelDirectory->Entries[tableIndex];
        AddFlag(*directoryEntry, PDE_PRESENT);
        AddFlag(*directoryEntry, PDE_WRITABLE);
        AddFlag(*directoryEntry, PDE_USERMODE); // FIXME: Only for testing purpose
        SetFrame(directoryEntry, kernelTable);
    }

	// Initialize SVGA space (0xFE000000)
	for (u32 tableIndex = SVGA_BASE / 0x400000; tableIndex < SVGA_LIMIT / 0x400000; tableIndex++)
	{
		PageTable* kernelTable = VMM_GetTable();

		for (u32 pageIndex = 0; pageIndex < 1024; pageIndex++)
		{
			PageTableEntry* tableEntry = &kernelTable->Entries[pageIndex];
			AddFlag(*tableEntry, PTE_PRESENT);
			AddFlag(*tableEntry, PTE_WRITABLE);
			AddFlag(*tableEntry, PTE_USERMODE); // FIXME: Only for testing purpose
			SetFrame(tableEntry, (void*)(tableIndex * 0x400000 + pageIndex * 0x1000));
		}

		PageDirectoryEntry* directoryEntry = &kernelDirectory->Entries[tableIndex];
		AddFlag(*directoryEntry, PDE_PRESENT);
		AddFlag(*directoryEntry, PDE_WRITABLE);
		AddFlag(*directoryEntry, PDE_USERMODE); // FIXME: Only for testing purpose
		SetFrame(directoryEntry, kernelTable);
	}
	
	// Initialize heap space (0xC0000000 - ...)
    for (u32 tableIndex = HEAP_BASE / 0x400000; tableIndex < HEAP_LIMIT / 0x400000; tableIndex++)
    {
        PageTable* heapTable = VMM_GetTable();

        for (u32 pageIndex = 0; pageIndex < 1024; pageIndex++)
        {
            PageTableEntry* tableEntry = &heapTable->Entries[pageIndex];
            AddFlag(*tableEntry, PTE_PRESENT);
            AddFlag(*tableEntry, PTE_WRITABLE);
            AddFlag(*tableEntry, PTE_USERMODE); // FIXME: Only for testing purpose
            SetFrame(tableEntry, (void*)(tableIndex * 0x400000 + pageIndex * 0x1000));
        }

        PageDirectoryEntry* directoryEntry = &kernelDirectory->Entries[tableIndex];
        AddFlag(*directoryEntry, PDE_PRESENT);
        AddFlag(*directoryEntry, PDE_WRITABLE);
        AddFlag(*directoryEntry, PDE_USERMODE); // FIXME: Only for testing purpose
        SetFrame(directoryEntry, heapTable);
    }

    // Enable our paging
    currentPDBR = &kernelDirectory->Entries;
    VMM_SetDirectory(kernelDirectory);
    PMM_EnablePaging(true);
}





MemoryMapping::MemoryMapping()
{
    Memory::Clear<MemoryDirectory>(&reversedPageDirectory);

    pageDirectory = VMM_GetDirectory();
    Memory::Clear<PageDirectory>(pageDirectory);
}
MemoryMapping::MemoryMapping(PageDirectory* pageDirectory) : pageDirectory(pageDirectory)
{
    Memory::Clear<MemoryDirectory>(&reversedPageDirectory);
}

void MemoryMapping::Map(void* physicalAddress, void* virtualAddress, bool writable, bool userMode)
{
    if ((u32)physicalAddress % 0x1000) return;
    if ((u32)virtualAddress % 0x1000) return;

    #pragma region Virtual to Physical mapping

    PageDirectoryEntry* pageDirectoryEntry = &pageDirectory->Entries[(u32)virtualAddress / 0x400000];
    PageTable* pageTable = (PageTable*)GetFrame(*pageDirectoryEntry);
    if (!pageTable)
    {
        pageTable = VMM_GetTable();
        Memory::Clear<PageTable>(pageTable);

        AddFlag(*pageDirectoryEntry, PDE_PRESENT);
        if (writable) AddFlag(*pageDirectoryEntry, PDE_WRITABLE);
        if (userMode) AddFlag(*pageDirectoryEntry, PDE_USERMODE);
        SetFrame(pageDirectoryEntry, pageTable);
    }

    PageTableEntry* pageTableEntry = &pageTable->Entries[((u32)virtualAddress % 0x400000) / 0x1000];
    AddFlag(*pageTableEntry, PTE_PRESENT);
    if (writable) AddFlag(*pageTableEntry, PTE_WRITABLE);
    if (userMode) AddFlag(*pageTableEntry, PTE_USERMODE);
    SetFrame(pageTableEntry, physicalAddress);

    #pragma endregion
    #pragma region Physical to Virtual mapping

    MemoryPage* page = reversedPageDirectory.Pages[(u32)physicalAddress / 0x400000];
    if (!page)
        reversedPageDirectory.Pages[(u32)physicalAddress / 0x400000] = page = Memory::Allocate<MemoryPage>(1, 0);
    page->Blocks[((u32)physicalAddress % 0x400000) / 0x1000] = virtualAddress;

    #pragma endregion
}
void MemoryMapping::Map(void* physicalAddress, void* virtualAddress, u32 size, bool writable, bool userMode)
{
    if ((u32)physicalAddress % 0x1000) return;
    if ((u32)virtualAddress % 0x1000) return;
    if (size % 0x1000) return;

    for (u32 i = 0; i < size / 0x1000; i++)
        Map((void*)((u32)physicalAddress + i * 0x1000), (void*)((u32)virtualAddress + i * 0x1000), writable, userMode);
}
void MemoryMapping::Allocate(void* virtualAddress, u32 size, bool writable, bool userMode)
{
    if ((u32)virtualAddress % 0x1000) return;
    if (size % 0x1000) return;

    for (u32 i = 0; i < size / 0x1000; i++)
        Map(PMM_AllocateBlock(), (void*)((u32)virtualAddress + i * 0x1000), writable, userMode);
}

void* MemoryMapping::GetPhysicalAddress(void* virtualAddress)
{
    PageDirectoryEntry* pageDirectoryEntry = &pageDirectory->Entries[(u32)virtualAddress / 0x400000];
    if (!IsFlag(*pageDirectoryEntry, PDE_PRESENT))
        return null;
    
    PageTable* pageTable = (PageTable*)GetFrame(*pageDirectoryEntry);
    PageTableEntry* pageTableEntry = &pageTable->Entries[(u32)virtualAddress / 0x1000];
    if (!IsFlag(*pageTableEntry, PTE_PRESENT))
        return null;

    return GetFrame(*pageTableEntry);
}
void* MemoryMapping::GetVirtualAddress(void* physicalAddress)
{
    MemoryPage* page = reversedPageDirectory.Pages[(u32)physicalAddress / 0x400000];
    if (!page)
        return null;

    return page->Blocks[(u32)physicalAddress / 0x1000];
}
