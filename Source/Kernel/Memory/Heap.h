#ifndef _KERNEL_OLDHEAP_H_
#define _KERNEL_OLDHEAP_H_

#include <System/Common.h>
#include "../Utilities/Structures/OrderedArray.h"

class Heap
{
public:
	_declspec(property(get = GetTotalMemory)) u32 TotalMemory;
	_declspec(property(get = GetFreeMomory)) u32 FreeMemory;

    virtual void* Allocate(u32 size) = 0;
    virtual void Free(void* block) = 0;

    virtual u32 GetTotalMemory() = 0;
    virtual u32 GetFreeMomory() = 0;
};

class ClassicHeap : public Heap
{
	friend void Heap_Expand(ClassicHeap* heap, u32 size);
	friend u32 Heap_FindHole(ClassicHeap* heap, u32 size);

private:
	OrderedArray/*<BlockHeader*>*/ Index;
	void* Start;
	void* End;
	void* Max;
	bool KernelMode;
	bool ReadOnly;

public:
    ClassicHeap(u32 size, bool kernelMode, bool readOnly);

	void* Allocate(u32 size) override;
	void Free(void* block) override;

	u32 GetTotalMemory() override;
	u32 GetFreeMomory() override;
};

class NewHeap : public Heap
{
private:
	u32 size;

public:
	NewHeap();

    void* Allocate(u32 size) override;
    void Free(void* block) override;

    u32 GetTotalMemory() override;
    u32 GetFreeMomory() override;
};

#endif