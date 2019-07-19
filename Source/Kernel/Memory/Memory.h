#ifndef _KERNEL_MEMORY_H_
#define _KERNEL_MEMORY_H_

#include <System/Base/Types.h>
#include <Kernel/Multiboot.h>
#include <Kernel/Config.h>
#include <Kernel/Runtime/Threading/Task.h>

#define KERNEL_CODE_SIZE  0x00100000 // 1 Mo
#define KERNEL_STACK_SIZE 0x00100000

#define KERNEL_HEAP_PAGETABLES (KERNEL_HEAP_SIZE / PMM_BLOCK_SIZE / 1024)

void Memory_Initialize(MultibootInfo* bootInfo);
void* Memory_Translate(void* address, Task* fromTask, Task* toTask);

#endif