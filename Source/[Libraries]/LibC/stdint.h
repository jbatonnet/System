#ifndef _LIBC_STDINT_H_
#define _LIBC_STDINT_H_

#ifdef __cplusplus
extern "C"
{
#endif

// Macros

#define INT8_MIN   (-INT8_MAX - 1)
#define INT8_MAX   0x7f
#define UINT8_MAX  0xff
#define INT16_MIN  (-INT16_MAX - 1)
#define INT16_MAX  0x7fff
#define UINT16_MAX 0xffff
#define INT32_MIN  (-INT32_MAX - 1)
#define INT32_MAX  0x7fffffff
#define UINT32_MAX 0xffffffff
#define INT64_MIN  (-INT64_MAX - 1)
#define INT64_MAX  0x7fffffffffffffff
#define UINT64_MAX 0xffffffffffffffff 

#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST8_MAX   INT8_MAX
#define UINT_LEAST8_MAX  UINT8_MAX
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST16_MAX  INT16_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST32_MAX  INT32_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define INT_LEAST64_MIN  INT64_MIN
#define INT_LEAST64_MAX  INT64_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define INT_FAST8_MIN   INT32_MIN
#define INT_FAST8_MAX   INT32_MAX
#define UINT_FAST8_MAX  UINT32_MAX
#define INT_FAST16_MIN  INT32_MIN
#define INT_FAST16_MAX  INT32_MAX
#define UINT_FAST16_MAX UINT32_MAX
#define INT_FAST32_MIN  INT32_MIN
#define INT_FAST32_MAX  INT32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define INT_FAST64_MIN  INT64_MIN
#define INT_FAST64_MAX  INT64_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define INTMAX_MIN  INT64_MIN
#define INTMAX_MAX  INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define INTPTR_MIN  INT32_MIN
#define INTPTR_MAX  INT32_MAX
#define UINTPTR_MAX UINT32_MAX

#define INT8_C(x)   (x)
#define INT16_C(x)  (x)
#define INT32_C(x)  ((x) + (INT32_MAX - INT32_MAX))
#define INT64_C(x)  ((x) + (INT64_MAX - INT64_MAX))
#define UINT8_C(x)  (x)
#define UINT16_C(x) (x)
#define UINT32_C(x) ((x) + (UINT32_MAX - UINT32_MAX))
#define UINT64_C(x) ((x) + (UINT64_MAX - UINT64_MAX))

#define INTMAX_C(x) ((x) + (INT64_MAX - INT64_MAX))
#define UINTMAX_C(x) ((x) + (UINT64_MAX - UINT64_MAX))

#define SIZE_MAX       UINT32_MAX
#define PTRDIFF_MIN    INT32_MIN
#define PTRDIFF_MAX    INT32_MAX
#define SIG_ATOMIC_MIN INT32_MIN
#define SIG_ATOMIC_MAX INT32_MAX
#define WCHAR_MIN      0
#define WCHAR_MAX      UINT16_MAX
#define WINT_MIN       0
#define WINT_MAX       UINT16_MAX

// Types

typedef char               int8_t;
typedef short              int16_t;
typedef long               int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t   int_least8_t;
typedef int16_t  int_least16_t;
typedef int32_t  int_least32_t;
typedef int64_t  int_least64_t;
typedef uint8_t  uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int32_t  int_fast8_t;
typedef int32_t  int_fast16_t;
typedef int32_t  int_fast32_t;
typedef int64_t  int_fast64_t;
typedef uint32_t uint_fast8_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef int64_t  intmax_t;
typedef uint64_t uintmax_t;

typedef int32_t  intptr_t;
typedef uint32_t uintptr_t;

#ifdef __cplusplus
}
#endif

#endif