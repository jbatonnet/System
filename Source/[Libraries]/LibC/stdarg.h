#ifndef _LIBC_STDARG_H_
#define _LIBC_STDARG_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Macros

#define va_start(list, param) (list = (((va_list)&param) + sizeof(param)))
#define va_arg(list, type)    (*(type *)((list += sizeof(type)) - sizeof(type)))
//#define va_end
//#define va_copy

// Types

typedef uint8_t* va_list;

#ifdef __cplusplus
}
#endif

#endif