#include <HAL/Interrupts.h>

#include "Controllers/PIC.h"
#include "CPU/IDT.h"
#include "CPU/GDT.h"

#include <Kernel/Config.h>

#define INTERRUPT_MAX_CHAIN 4
#define INTERRUPT_ISR_SIZE  128 // 45 bytes - 2014-02-08

bool interrupt_enabled = false;
InterruptHandler interrupt_handlers[256 * INTERRUPT_MAX_CHAIN] = { 0 };
char* interrupt_interrupts = (char*)KERNEL_ISR;//[256 * INTERRUPT_ISR_SIZE];
bool interrupt_interrupting = false;

u8 errorCode[0x20] = { 0, 0, 0, 0,
                          0, 0, 0, 0,
                          1, 0, 1, 1,
                          1, 1, 1, 0,
                          0, 1, 0, 0,
                          0, 0, 0, 0 };

void  _declspec(naked) Interrupt_DefaultISR()
{
    _asm pushad

    _asm mov al, 0x20
    _asm out 0x20, al
    //IRQ_EOI(0);

    _asm popad
    _asm iretd
}

void Interrupt_InterruptServiceRoutine(u32 index)
{
    interrupt_interrupting = true;

    for (int i = 0; i < INTERRUPT_MAX_CHAIN; i++)
    {
        if (!interrupt_handlers[index * INTERRUPT_MAX_CHAIN + i])
            break;
        
        interrupt_handlers[index * INTERRUPT_MAX_CHAIN + i]();
        _asm mov ebp, esp
        _asm add ebp, 4
    }

    PIC_EOI(index - INTERRUPT_REQUEST);

    interrupt_interrupting = false;
}
void Interrupt_Initialize()
{
    char *isrStart, *isrEnd, *isrError0, *isrError1, *isrError2;
    u32* isrIndex;

    // Interrupt handler
    _asm
    {
        jmp isr_end

        isr:
            push eax

            mov eax, MEMORY_DIRECTORIES
            mov cr3, eax

            mov eax, [esp + 4]
            mov [esp - 44], eax

            pop eax

        error0:
            add esp, 4

            pushad
            push es
            push ds
            push fs
            push gs

            mov bx, GDT_KERNEL_DATA_SEGMENT
            mov ds, bx
            mov es, bx
            mov fs, bx
            mov gs, bx

        error1:
            sub esp, 4

        index:
            push 0xFF
            mov eax, [Interrupt_InterruptServiceRoutine]
            call eax

        error2:
            add esp, 8

            pop gs
            pop fs
            pop ds
            pop es

            //popad
            //iret

            mov eax, SHARED_CODE
            jmp eax

        isr_end:
            mov eax, isr
            mov [isrStart], eax
            mov eax, index
            inc eax
            mov [isrIndex], eax
            mov eax, isr_end
            mov [isrEnd], eax

            mov eax, error0
            add eax, 2
            mov [isrError0], eax
            mov eax, error1
            add eax, 2
            mov [isrError1], eax
            mov eax, error2
            add eax, 2
            mov [isrError2], eax
    }

    // Copy the default ISR
    for (u8 i = 0x00; i < 0xFF; i++)
    {
        *isrIndex = i;
        for (int j = 0; j < isrEnd - isrStart; j++)
            interrupt_interrupts[i * INTERRUPT_ISR_SIZE + j] = isrStart[j];

        // Stack correction
        bool error = i < 0x20 && errorCode[i];
        interrupt_interrupts[i * INTERRUPT_ISR_SIZE + (isrError0 - isrStart)] = error ? 4 : 0;
        interrupt_interrupts[i * INTERRUPT_ISR_SIZE + (isrError1 - isrStart)] = error ? 4 : 0;
        interrupt_interrupts[i * INTERRUPT_ISR_SIZE + (isrError2 - isrStart)] = error ? 8 : 4;
    }

    // Install the ISR
    for (u8 i = 0x00; i < 0x7F; i++)
        IDT_InstallIR(i, IDT_DESC_PRESENT | IDT_DESC_BIT32, GDT_KERNEL_CODE_SEGMENT, (IDT_InterruptHandler)(interrupt_interrupts + i * INTERRUPT_ISR_SIZE));
    for (u8 i = 0x80; i < 0xFF; i++)
        IDT_InstallIR(i, IDT_DESC_PRESENT | IDT_DESC_BIT32 | IDT_DESC_RING3, GDT_KERNEL_CODE_SEGMENT, (IDT_InterruptHandler)(interrupt_interrupts + i * INTERRUPT_ISR_SIZE));

    char *iprStart, *iprEnd;

    // Interrupt pager
    _asm
    {
        jmp ipr_end

        ipr:
            mov eax, MEMORY_DIRECTORIES
            mov ebx, eax
            sub ebx, MEMORY_DIRECTORIES
            jz ipr_def

            mov esi, esp
            mov edi, SHARED_STACK
            mov ecx, 0x10
            rep movsd

            mov esp, SHARED_STACK
            mov cr3, eax

            popad
            mov esp, SHARED_STACK + 0x20
            iretd

        ipr_def:
            popad
            iretd

        ipr_end:
            mov eax, ipr
            mov [iprStart], eax
            mov eax, ipr_end
            mov [iprEnd], eax
    }

    // Install the IPR
    for (int i = 0; i < iprEnd - iprStart; i++)
        *(u8*)(SHARED_CODE + i) = iprStart[i];
}

void Interrupt_AddHandler(u8 index, InterruptHandler handler)
{
    //Interrupt_Disable();

    for (u32 i = 0; i < INTERRUPT_MAX_CHAIN; i++)
        if (!interrupt_handlers[index * INTERRUPT_MAX_CHAIN + i])
        {
            interrupt_handlers[index * INTERRUPT_MAX_CHAIN + i] = handler;
            break;
        }
    
    //Interrupt_Enable();
}
void Interrupt_AddExceptionHandler(u8 index, InterruptHandler handler)
{
    Interrupt_AddHandler(INTERRUPT_EXCEPTION + index, handler);
}
void Interrupt_AddRequestHandler(u8 index, InterruptHandler handler)
{
    Interrupt_AddHandler(INTERRUPT_REQUEST + index, handler);
}
void Interrupt_AddVirtualHandler(u8 index, InterruptHandler handler)
{
    Interrupt_AddHandler(INTERRUPT_VIRTUAL + index, handler);
}
void Interrupt_AddKernelHandler(u8 index, InterruptHandler handler)
{
    Interrupt_AddHandler(INTERRUPT_KERNEL + index, handler);
}
void Interrupt_AddSystemHandler(InterruptHandler handler)
{
    Interrupt_AddHandler(INTERRUPT_SYSTEM, handler);
}

void Interrupt_Enable()
{
    if (!interrupt_enabled)
        _asm sti
    interrupt_enabled = true;
}
void Interrupt_Disable()
{
    if (interrupt_enabled)
        _asm cli
    interrupt_enabled = false;
}
