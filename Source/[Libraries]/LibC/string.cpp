#include "string.h"

#pragma function(memchr, memchr, memcmp, memcpy, memmove, memset, strcat, strchr, strcmp, strcoll, strcpy, strcspn, strerror, strlen, strncat, strncmp, strncpy, strpbrk, strrchr, strspn, strstr, strtok, strxfrm)

//const void* memchr(const void* ptr, int value, size_t num);
//void* memchr(void* ptr, int value, size_t num);
//int memcmp(const void* ptr1, const void* ptr2, size_t num);
void* memcpy(void *v_dst, const void* v_src, size_t c)
{
    const char* src = (const char*)v_src;
    char* dst = (char*)v_dst;

    /* Simple, byte oriented memcpy. */
    while (c--)
        *dst++ = *src++;

    return v_dst;
}
void* memmove(void* v_dst, const void* v_src, size_t c)
{
    const char* src = (const char*)v_src;
    char *dst = (char*)v_dst;

    if (!c)
        return v_dst;

    /* Use memcpy when source is higher than dest */
    if (v_dst <= v_src)
        return memcpy(v_dst, v_src, c);

    /* copy backwards, from end to beginning */
    src += c;
    dst += c;

    /* Simple, byte oriented memmove. */
    while (c--)
        *--dst = *--src;

    return v_dst;
}
//void* memset(void* ptr, int value, size_t num);
//char* strcat(char* destination, const char* source);
//char* strchr(const char* str, int character);
//int strcmp(const char* str1, const char* str2);
//int strcoll(const char* str1, const char* str2);
//char* strcpy(char* destination, const char* source);
//size_t strcspn(const char* str1, const char* str2);
//char* strerror(int errnum);
//size_t strlen(const char* str);
//char* strncat(char* destination, const char* source, size_t num);
int strncmp(const char* s1, const char* s2, size_t n)
{
    while (n--)
        if (*s1++ != *s2++)
            return *(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1);
    return 0;
}
//char* strncpy(char* destination, const char* source, size_t num);
//char* strpbrk(const char* str1, const char* str2);
//char* strrchr(const char* str, int character);
//size_t strspn(const char * str1, const char * str2);
//char* strstr(const char* str1, const char* str2);
//char* strtok(char* str, const char* delimiters);
//size_t strxfrm(char* destination, const char* source, size_t num);