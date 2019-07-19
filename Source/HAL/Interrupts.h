#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include <HAL/HAL.h>

#define interrupt _declspec(naked)

#define INTERRUPT_EXCEPTION 0x00
#define INTERRUPT_REQUEST   0x20
#define INTERRUPT_VIRTUAL   0x30
#define INTERRUPT_KERNEL    0x50
#define INTERRUPT_SYSTEM    0x80

struct InterruptHandlerParameters
{
    u32 isrEcx;
    u32 isrEbp;
    u32 isrRet;
};
struct InterruptHandlerRegisters
{
    u32 gs, fs, es, ds;
    union { u32 edi; u16 di; };
    union { u32 esi; u16 si; };
    union { u32 ebp; u16 bp; };
    union { u32 esp; u16 sp; };
    union { u32 ebx; union { u16 bx; struct { u8 bl; u8 bh; }; }; };
    union { u32 edx; union { u16 dx; struct { u8 dl; u8 dh; }; }; };
    union { u32 ecx; union { u16 cx; struct { u8 cl; u8 ch; }; }; };
    union { u32 eax; union { u16 ax; struct { u8 al; u8 ah; }; }; };
    union { u32 eip; u16 ip; };
    u32 cs;
    union { u32 eflags; u16 flags; };

    struct
    {
        union { u32 esp; u16 sp; };
        u32 ss;
    } u;
    struct
    {
        u32 es, ds, fs, gs;
    } v;
};

typedef void (*InterruptHandler)(void);

extern bool interrupt_interrupting;
extern void Interrupt_Initialize();

extern void Interrupt_AddHandler(u8 index, InterruptHandler handler);
extern void Interrupt_AddExceptionHandler(u8 index, InterruptHandler handler);
extern void Interrupt_AddRequestHandler(u8 index, InterruptHandler handler);
extern void Interrupt_AddVirtualHandler(u8 index, InterruptHandler handler);
extern void Interrupt_AddKernelHandler(u8 index, InterruptHandler handler);
extern void Interrupt_AddSystemHandler(InterruptHandler handler);

extern void Interrupt_Enable();
extern void Interrupt_Disable();

#endif