#ifndef _LIBC_STDDEF_H_
#define _LIBC_STDDEF_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Macros

#define offsetof(s, m) ((size_t)&(((s*)0)->m))
#define NULL 0

// Types

typedef int ptrdiff_t;
typedef unsigned int size_t;

#ifdef __cplusplus
}
#endif

#endif