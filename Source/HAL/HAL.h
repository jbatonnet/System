#ifndef _HAL_H_
#define _HAL_H_

#include <HAL/Types.h>
#include <HAL/Interrupts.h>
#include <HAL/IO.h>

extern void HAL_Load();
extern void HAL_Unload();
extern u32 HAL_Test(u32 value);

#endif