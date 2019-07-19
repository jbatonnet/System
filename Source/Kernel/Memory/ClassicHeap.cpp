#include "Heap.h"

#include <System/Debugging/Log.h>
#include <System/Runtime/Debugging/Debugger.h>

#define HEAP_BASE_SIZE   0x10000
#define HEAP_EXPAND_SIZE 0x100000

#define HEAP_INDEX_SIZE  256
#define HEAP_MAGIC       0x13371337

using namespace System::Runtime;

struct BlockHeader
{
    u32 Magic;
    bool Hole;
    u32 Size;
};
struct BlockFooter
{
    u32 Magic;
    BlockHeader* Header;
};

namespace { Spinlock spinlock; }

static char* hex = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

s32 BlockHeaderComparer(void* header1, void* header2)
{
	return ((BlockHeader*)header1)->Size - ((BlockHeader*)header2)->Size;
}
void Heap_Expand(ClassicHeap* heap, u32 size)
{
#if DEBUG_MEMORY <= DEBUG
	char message[] = "Heap_Expand(0x00000000)\n";

	message[sizeof(message) - 11] = hex[(size / 0x10000000) % 0x10];
	message[sizeof(message) - 10] = hex[(size / 0x1000000) % 0x10];
	message[sizeof(message) - 9] = hex[(size / 0x100000) % 0x10];
	message[sizeof(message) - 8] = hex[(size / 0x10000) % 0x10];
	message[sizeof(message) - 7] = hex[(size / 0x1000) % 0x10];
	message[sizeof(message) - 6] = hex[(size / 0x100) % 0x10];
	message[sizeof(message) - 5] = hex[(size / 0x10) % 0x10];
	message[sizeof(message) - 4] = hex[(size / 0x1) % 0x10];

    Log::WriteLine(Log::Trace, (const char*)message);
#endif

	//Debug::Assert(size > (u32)heap->End - (u32)heap->Start);
	//Debug::Assert(size <= (u32)heap->Max - (u32)heap->Start, "Expanding over the limit");

	// Find last hole
	BlockFooter* footer = (BlockFooter*)((u32)heap->End - sizeof(BlockFooter));
	BlockHeader* header = footer->Header;

	//WriteLine("Last hole (before)");
	//WriteLine("- Header: { Address: %x, Magic: %x, Size: %x }", header, header->Magic, header->Size);
	//WriteLine("- Footer: { Address: %x, Magic: %x }", footer, footer->Magic);

	// Expand last hole and the heap
	heap->End = (void*)((u32)heap + size);

	footer = (BlockFooter*)((u32)heap->End - sizeof(BlockFooter));
	footer->Header = (BlockHeader*)header;
	footer->Magic = HEAP_MAGIC;

	header->Size = (u32)footer - (u32)header - sizeof(BlockHeader);

	//WriteLine("Last hole (after)");
	//WriteLine("- Header: { Address: %x, Magic: %x, Size: %x }", header, header->Magic, header->Size);
	//WriteLine("- Footer: { Address: %x, Magic: %x }", footer, footer->Magic);
}
u32 Heap_FindHole(ClassicHeap* heap, u32 size)
{
	/*for (u32 i = 0; i < heap->Index.Size; i++)
	{
	WriteLine("- Hole: { Address: %x, Size: %x }", (BlockHeader*)heap->Index.Array[i], ((BlockHeader*)heap->Index.Array[i])->Size);
	if (!((BlockHeader*)heap->Index.Array[i])->Size)
	loop
	}*/

	for (u32 i = 0; i < heap->Index.Size; i++)
		if (((BlockHeader*)heap->Index.Array[i])->Size >= size)
			return i;
	return -1;
}

ClassicHeap::ClassicHeap(u32 size, bool kernelMode, bool readOnly)
{
    void* end = (void*)((u32)this + HEAP_BASE_SIZE);
    void* max = (void*)((u32)this + size);

	void** index = (void**)((u32)this + sizeof(ClassicHeap));
	BlockHeader* header = (BlockHeader*)((u32)index + HEAP_INDEX_SIZE * sizeof(void*));
	BlockFooter* footer = (BlockFooter*)((u32)end - sizeof(BlockFooter));

	// Heap initialization
	this->Start = header;
	this->End = end;
	this->Max = max;
	this->KernelMode = kernelMode;
	this->ReadOnly = readOnly;

	header->Size = (u32)footer - (u32)header - sizeof(BlockHeader);
	header->Hole = true;
	header->Magic = HEAP_MAGIC;

	footer->Header = header;
	footer->Magic = HEAP_MAGIC;

	// Index initialization
	this->Index = OrderedArray_Place(index, HEAP_INDEX_SIZE, BlockHeaderComparer);
	OrderedArray_Add(this->Index, header);
}

void* ClassicHeap::Allocate(u32 size)
{
	if (size > 0x100000)
		Log::WriteLine(Log::Warning, "Heap_Allocate: Big allocation");
	if (size > 0x1000000)
		Debugger::Break();

	spinlock.Lock();

#if _DEBUG_MEMORY
	{
		//Write("Heap_Allocate(0x%x, %d)\n", heap, size);

		/*char* message = "Heap_Allocate(0x0000)\r\n";
		message[16] = hex[(size / 0x1000) % 0x10];
		message[17] = hex[(size / 0x100) % 0x10];
		message[18] = hex[(size / 0x10) % 0x10];
		message[19] = hex[(size / 0x1) % 0x10];

		if (Console::BaseStream)
		Console::BaseStream->Write(message, 23);*/
	}
#endif

	// Automatically expand the heap
	s32 holeId = Heap_FindHole(this, size);
	while (holeId < 0 && (u32)End < (u32)Max)
	{
		Heap_Expand(this, (u32)End - (u32)Start + HEAP_EXPAND_SIZE);
		holeId = Heap_FindHole(this, size);

		//Log::WriteLine(Log::Trace, "Expanding heap !");
	}
	if (holeId < 0)
	{
		spinlock.Unlock();

		Log::WriteLine(Log::Error, "Not enough memory in the heap !!");
		return null;
	}

	BlockHeader* header = (BlockHeader*)Index.Array[holeId];
	BlockFooter* footer = (BlockFooter*)((u32)header + sizeof(BlockHeader) + header->Size);

#if _DEBUG_MEMORY
	//WriteLine("Hole before");
	//WriteLine("- Header: { Address: %x, Magic: %x, Size: %x }", header, header->Magic, header->Size);
	//WriteLine("- Footer: { Address: %x, Magic: %x, Header: %x }", footer, footer->Magic, footer->Header);
#endif

	// If the hole can't be split in 2, just increase the requested size
	if (header->Size - size <= sizeof(BlockHeader) + sizeof(BlockFooter))
		size += header->Size - size;

	// Remove the old hole
	OrderedArray_RemoveAt(Index, holeId);

	// Add the second hole
	if (header->Size - size > 0)
	{
		BlockHeader* subHeader = (BlockHeader*)((u32)header + sizeof(BlockHeader) + size + sizeof(BlockFooter));
		subHeader->Hole = true;
		subHeader->Size = header->Size - size - sizeof(BlockHeader) - sizeof(BlockFooter);
		subHeader->Magic = HEAP_MAGIC;

		BlockFooter* subFooter = (BlockFooter*)((u32)subHeader + sizeof(BlockHeader) + subHeader->Size);
		subFooter->Header = subHeader;
		subFooter->Magic = HEAP_MAGIC;

		OrderedArray_Add(Index, subHeader);

#if _DEBUG_MEMORY
		//WriteLine("New hole");
		//WriteLine("- Header: { Address: %x, Magic: %x, Size: %x }", subHeader, subHeader->Magic, subHeader->Size);
		//WriteLine("- Footer: { Address: %x, Magic: %x, Header: %x }", subFooter, subFooter->Magic, footer->Header);
#endif
	}

	// Replace it with our data
	header->Hole = false;
	header->Size = size;
	header->Magic = HEAP_MAGIC;

	footer = (BlockFooter*)((u32)header + sizeof(BlockHeader) + size);
	footer->Header = header;
	footer->Magic = HEAP_MAGIC;

#if _DEBUG_MEMORY
	//WriteLine("Hole after");
	//WriteLine("- Header: { Address: %x, Magic: %x, Size: %x }", header, header->Magic, header->Size);
	//WriteLine("- Footer: { Address: %x, Magic: %x, Header: %x }", footer, footer->Magic, footer->Header);
#endif

	spinlock.Unlock();

	return (void*)((u32)header + sizeof(BlockHeader));
}
void ClassicHeap::Free(void* block)
{
	if (!block)
		return;

	spinlock.Lock();

	BlockHeader* header = (BlockHeader*)((u32)block - sizeof(BlockHeader));
	if (header->Magic != HEAP_MAGIC)
	{
		spinlock.Unlock();
		return; // throw error
	}

	BlockFooter* footer = (BlockFooter*)((u32)header + header->Size + sizeof(BlockHeader));
	if (footer->Magic != HEAP_MAGIC)
	{
		spinlock.Unlock();
		return; // throw error
	}

#if _DEBUG_MEMORY
	//WriteLine("Heap_Free(%x, %x)", heap, block);

	{
		char* message = "Heap_Free(0x0000)\r\n";
		message[12] = hex[(header->Size / 0x1000) % 0x10];
		message[13] = hex[(header->Size / 0x100) % 0x10];
		message[14] = hex[(header->Size / 0x10) % 0x10];
		message[15] = hex[(header->Size / 0x1) % 0x10];

		if (Serial::BaseStream)
			Serial::BaseStream->Write(message, 19);
	}

#endif

#if _DEBUG_MEMORY
	//WriteLine("Free hole");
	//WriteLine("- Header: { Address: %x, Magic: %x, Size: %x }", header, header->Magic, header->Size);
	//WriteLine("- Footer: { Address: %x, Magic: %x, Header: %x }", footer, footer->Magic, footer->Header);
#endif

	// Left unification
	BlockFooter* prevFooter = (BlockFooter*)((u32)header - sizeof(BlockFooter));
	if (prevFooter->Magic == HEAP_MAGIC && prevFooter->Header->Hole)
	{
#if _DEBUG_MEMORY
		//WriteLine("Previous hole");
		//WriteLine("- Header: { Address: %x, Magic: %x, Size: %x }", prevFooter->Header, prevFooter->Header->Magic, prevFooter->Header->Size);
		//WriteLine("- Footer: { Address: %x, Magic: %x, Header: %x }", prevFooter, prevFooter->Magic, prevFooter->Header);
#endif

		for (int i = 0; i < Index.Size; i++)
			if (Index.Array[i] == prevFooter->Header)
			{
				OrderedArray_RemoveAt(Index, i);
				break;
			}

		prevFooter->Header->Size += header->Size + sizeof(BlockFooter) + sizeof(BlockHeader);
		header = prevFooter->Header;
		footer->Header = header;
	}

	// Right unification
	BlockHeader* nextHeader = (BlockHeader*)((u32)footer + sizeof(BlockFooter));
	if (nextHeader->Magic == HEAP_MAGIC && nextHeader->Hole)
	{
#if _DEBUG_MEMORY
		//WriteLine("Next hole");
		//WriteLine("- Header: { Address: %x, Magic: %x, Size: %x }", nextHeader, nextHeader->Magic, nextHeader->Size);
#endif

		for (int i = 0; i < Index.Size; i++)
			if (Index.Array[i] == nextHeader)
			{
				OrderedArray_RemoveAt(Index, i);
				break;
			}

		header->Size += nextHeader->Size + sizeof(BlockFooter) + sizeof(BlockHeader);
		footer = (BlockFooter*)((u32)header + header->Size + sizeof(BlockHeader));
		footer->Header = header;
	}

	header->Hole = true;

	OrderedArray_Add(Index, header);

	spinlock.Unlock();
}

u32 ClassicHeap::GetTotalMemory()
{
	return (u32)End - (u32)Start;
}
u32 ClassicHeap::GetFreeMomory()
{
	u32 memory = 0;

	for (u32 i = 0; i < Index.Size; i++)
	{
		BlockHeader* block = (BlockHeader*)Index.Array[i];

		if (block->Hole)
			memory += block->Size;
	}

	return memory;
}