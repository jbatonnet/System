#ifndef _LIBC_STRING_H_
#define _LIBC_STRING_H_

#include "stddef.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Functions

void* memchr(const void* ptr, int value, size_t num);
int memcmp(const void* ptr1, const void* ptr2, size_t num);
void* memcpy(void* v_dst, const void* v_src, size_t c);
void* memmove(void* v_dst, const void* v_src, size_t c);
void* memset(void* ptr, int value, size_t num);
char* strcat(char* destination, const char* source);
char* strchr(const char* str, int character);
int strcmp(const char* str1, const char* str2);
int strcoll(const char* str1, const char* str2);
char* strcpy(char* destination, const char* source);
size_t strcspn(const char* str1, const char* str2);
char* strerror(int errnum);
size_t strlen(const char* str);
char* strncat(char* destination, const char* source, size_t num);
int strncmp(const char* s1, const char* s2, size_t n);
char* strncpy(char* destination, const char* source, size_t num);
char* strpbrk(const char* str1, const char* str2);
char* strrchr(const char* str, int character);
size_t strspn(const char* str1, const char* str2);
char* strstr(const char* str1, const char* str2);
char* strtok(char* str, const char* delimiters);
size_t strxfrm(char* destination, const char* source, size_t num);

#ifdef __cplusplus
}
#endif

#endif