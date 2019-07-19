#if !defined(_IDT_H_) && defined(X86)
#define _IDT_H_

#include <HAL/HAL.h>

// Maximum number of interrupt handlers
#define IDT_MAX_INTERRUPTS 256

#define IDT_DESC_BIT16   0x06
#define IDT_DESC_BIT32   0x0E
#define IDT_DESC_RING1   0x40
#define IDT_DESC_RING2   0x20
#define IDT_DESC_RING3   0x60
#define IDT_DESC_PRESENT 0x80

// Interrupt handler w/o error code
typedef void (*IDT_InterruptHandler)(void);

typedef struct IDT_Descriptor
{
    u16 HandlerLo; // Interrupt routine

    u16 GDTSelector;
    u8	 Reserved; // TODO: Skip this byte

    u8	 Flags;

    u16 HandlerHi;
} IDT_Descriptor;

typedef struct IDT_Data
{
    u16 Limit;
    u32 Base;
} IDT_Data;

void IDT_Install();

IDT_Descriptor* IDT_GetIR(u32 i);
void IDT_InstallIR(u32 i, u16 flags, u16 sel, IDT_InterruptHandler irq);

void IDT_Initialize();

#endif