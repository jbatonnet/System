#ifndef _IO_H_
#define _IO_H_

#include <HAL/Types.h>

extern u8 IO_Read8(u16 port);
extern u16 IO_Read16(u16 port);
extern u32 IO_Read32(u16 port);
extern void IO_Write8(u16 port, u8 value);
extern void IO_Write16(u16 port, u16 value);
extern void IO_Write32(u16 port, u32 value);

#endif