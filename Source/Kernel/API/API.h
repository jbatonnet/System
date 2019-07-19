#ifndef _KERNEL_KERNELOBJECT_H_
#define _KERNEL_KERNELOBJECT_H_

#include <System/Common.h>
#include <HAL/Interrupts.h>

void API_InterruptHandler(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers);
void API_HandleInterrupts();

#endif