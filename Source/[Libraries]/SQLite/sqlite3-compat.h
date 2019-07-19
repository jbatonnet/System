#ifndef _SQLITE3_COMPAT_H_
#define _SQLITE3_COMPAT_H_

#define SQLITE_OS_OTHER 1
#define SQLITE_OMIT_DATETIME_FUNCS 1
#define SQLITE_OMIT_LOCALTIME 1
#define SQLITE_WITHOUT_MSIZE 1
#define SQLITE_TEMP_STORE 3

#ifndef assert
#define assert(x)
#endif

#define NULL 0

#undef memcopy
#undef memmove

typedef unsigned long time_t;
typedef unsigned int size_t;

struct tm
{
    int tm_sec;   // seconds of minutes from 0 to 61
    int tm_min;   // minutes of hour from 0 to 59
    int tm_hour;  // hours of day from 0 to 24
    int tm_mday;  // day of month from 1 to 31
    int tm_mon;   // month of year from 0 to 11
    int tm_year;  // year since 1900
    int tm_wday;  // days since sunday
    int tm_yday;  // days since January 1st
    int tm_isdst; // hours of daylight savings time
};

#ifdef __cplusplus
extern "C"
{
#endif

int sqlite3_os_init();
int sqlite3_os_end();

void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);
struct tm* gmtime(const time_t* timer);
size_t strftime(char* ptr, size_t maxsize, const char* format, const struct tm* timeptr);
void* memmove(void* destination, const void* source, size_t num);
int memcmp(const void* str1, const void* str2, size_t count);
int strncmp(const char* str1, const char* str2, size_t num);
int strcmp(const char* X, const char* Y);

#ifdef __cplusplus
}
#endif

#endif