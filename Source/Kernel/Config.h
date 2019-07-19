#ifndef _KERNEL_CONFIG_H_
#define _KERNEL_CONFIG_H_

/*
    Memory structure
*/

// Virtual
#define KERNEL_VIRTUAL_STACK 0x0007FFFC
#define KERNEL_VIRTUAL_CODE  0x00080000

// Interrupts
#define KERNEL_ISR 0x00090000

// Shared
#define SHARED_CODE  0x0009C000 // FIXME : 98k to 9Ek tested (Page 152)
#define SHARED_STACK (SHARED_CODE - 0x100)
#define SHARED_PAGE  (SHARED_CODE / 0x1000)

// Base
#define KERNEL_BASE  0x00100000
#define KERNEL_ENTRY 0x00101a10
#define KERNEL_STACK 0x007BFFFC
#define KERNEL_LIMIT 0x00800000

// Memory
#define MEMORY_MAP               0x007C0000
#define MEMORY_DIRECTORIES       0x00800000
#define MEMORY_TABLES            0x00C00000
#define MEMORY_LIMIT             0x01000000
#define MEMORY_DIRECTORIES_COUNT ((MEMORY_TABLES - MEMORY_DIRECTORIES) / 0x1000)
#define MEMORY_TABLES_COUNT      ((MEMORY_LIMIT - MEMORY_TABLES) / 0x1000)

// Video
#define VIDEO_BASE         0xE8000000
#define VIDEO_LIMIT        0xE9000000
#define VIDEO_TABLES_COUNT ((VIDEO_LIMIT - VIDEO_BASE) / 0x1000)

// SVGA
#define SVGA_BASE         0xFE000000
#define SVGA_LIMIT        0xFF000000
#define SVGA_TABLES_COUNT ((VIDEO_LIMIT - VIDEO_BASE) / 0x1000)

// Heap
#define HEAP_BASE         0xC0000000
#define HEAP_SIZE         0x01000000 // x 16 Mo
#define HEAP_LIMIT        0xC1000000



/*
    Debugging
*/

#define TRACE   1
#define DEBUG   2
#define INFO    3
#define WARNING 4
#define ERROR   5

// Kernel
#define DEBUG_TASKING 0
#define DEBUG_MEMORY  ERROR
#define DEBUG_STRING  ERROR
#define DEBUG_API     TRACE
#define DEBUG_FILES   TRACE

// Screen
#define DEBUG_REFRESHES 0



/*
    Settings
*/
#define FRENQUENCY_DIVIDER (DEBUG_TASKING ? 100 : 1)


#endif