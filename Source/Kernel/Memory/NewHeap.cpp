#include "Heap.h"

/*
4k * 4    = 16k
4k * 128  = 512k
4k * 4k   = 16m
4k * 128k = 512m
----
512k
*/

#define HEAP_BLOCK_SIZE_1 4      // 4
#define HEAP_BLOCK_SIZE_2 128    // 128
#define HEAP_BLOCK_SIZE_3 4096   // 4k
#define HEAP_BLOCK_SIZE_4 131072 // 128k

#define HEAP_MASK_1 0x01 // 00000001
#define HEAP_MASK_2 0x03 // 00000011
#define HEAP_MASK_3 0x07 // 00000111
#define HEAP_MASK_4 0x0F // 00001111
#define HEAP_MASK_5 0x1F // 00011111
#define HEAP_MASK_6 0x3F // 00111111
#define HEAP_MASK_7 0x7F // 01111111
#define HEAP_MASK_8 0xFF // 11111111

#define HEAP_BLOCK_MASK_1(shift) (HEAP_MASK_1 << shift)
#define HEAP_BLOCK_MASK_2(shift) (HEAP_MASK_2 << shift)
#define HEAP_BLOCK_MASK_3(shift) (HEAP_MASK_3 << shift)
#define HEAP_BLOCK_MASK_4(shift) (HEAP_MASK_4 << shift)
#define HEAP_BLOCK_MASK_5(shift) (HEAP_MASK_5 << shift)
#define HEAP_BLOCK_MASK_6(shift) (HEAP_MASK_6 << shift)
#define HEAP_BLOCK_MASK_7(shift) (HEAP_MASK_7 << shift)
#define HEAP_BLOCK_MASK_8(shift) (HEAP_MASK_8 << shift)

#define HEAP_MAP_SIZE 4096

struct _Heap
{
    u32 Level1MapCount, Level1Maps[255]; // 128k
    u32 Level2MapCount, Level2Maps[255]; // 4k
    u32 Level3MapCount, Level3Maps[255];
    u32 Level4MapCount, Level4Maps[255];
};

NewHeap::NewHeap()
{
}

void* NewHeap::Allocate(u32 size)
{
	return null;
}
void NewHeap::Free(void* block)
{
}

u32 NewHeap::GetTotalMemory()
{
	return 0;
}
u32 NewHeap::GetFreeMomory()
{
	return 0;
}