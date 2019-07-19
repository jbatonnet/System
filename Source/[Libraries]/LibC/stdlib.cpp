#include "stdlib.h"

#include <System/Common.h>
#include <System/Memory/Memory.h>

#define MAX_ALLOCATIONS 4096

struct SQLiteAllocation
{
    void* Pointer;
    u32 Size;
} allocations[MAX_ALLOCATIONS] = { 0 };

//double atof(const char* str);
//int atoi(const char * str);
//long int atol(const char * str);
//long long int atoll(const char * str);
//double strtod(const char* str, char** endptr);
//float strtof(const char* str, char** endptr);
//long int strtol(const char* str, char** endptr, int base);
//long double strtold(const char* str, char** endptr);
//long long int strtoll(const char* str, char** endptr, int base);
//unsigned long int strtoul(const char* str, char** endptr, int base);
//unsigned long long int strtoull(const char* str, char** endptr, int base);
//int rand(void);
//void srand(unsigned int seed);
//void* calloc(size_t num, size_t size);
void* malloc(size_t size)
{
    void* pointer = Memory::Allocate(size);

    for (int i = 0; i < MAX_ALLOCATIONS; i++)
        if (!allocations[i].Pointer)
        {
            allocations[i].Pointer = pointer;
            allocations[i].Size = size;

            return pointer;
        }

    Exception::Assert("malloc(OUILLE)");
    loop
    return null;
}
void free(void* pointer)
{
    Memory::Free(pointer);

    for (int i = 0; i < MAX_ALLOCATIONS; i++)
        if (allocations[i].Pointer == pointer)
        {
            allocations[i].Pointer = null;
            allocations[i].Size = 0;

            return;
        }

    Exception::Assert("free(OUILLE)");
    loop
}
void* realloc(void* pointer, size_t size)
{
    for (int i = 0; i < MAX_ALLOCATIONS; i++)
        if (allocations[i].Pointer == pointer)
        {
            if (size > allocations[i].Size)
            {
                pointer = Memory::Allocate(size);
                Memory::Copy(allocations[i].Pointer, pointer, allocations[i].Size);
                Memory::Free(allocations[i].Pointer);

                allocations[i].Pointer = pointer;
                allocations[i].Size = size;
            }

            return pointer;
        }

    Exception::Assert("realloc(OUILLE)");
    loop
    return null;
}
void abort()
{
    Exception::Assert("abort()");
}
//int atexit(void(*func)(void));
//int at_quick_exit(void(*func)(void));
//void exit(int status);
//char* getenv(const char* name);
//void quick_exit(int status);
//int system(const char* command);
//void _Exit(int status);
//void* bsearch(const void* key, const void* base, size_t num, size_t size, int(*compar)(const void*, const void*));
//void qsort(void* base, size_t num, size_t size, int(*compar)(const void*, const void*));
//int abs(int n);
//div_t div(int numer, int denom);
//long int labs(long int n);
//ldiv_t ldiv(long int numer, long int denom);
//long long int llabs(long long int n);
//lldiv_t lldiv(long long int numer, long long int denom);
//int mblen(const char* pmb, size_t max);
//int mbtowc(wchar_t* pwc, const char* pmb, size_t max);
//int wctomb(char* pmb, wchar_t wc);
//size_t mbstowcs(wchar_t* dest, const char* src, size_t max);
//size_t wcstombs(char* dest, const wchar_t* src, size_t max);