#ifndef _LIBC_IO_H_
#define _LIBC_IO_H_

#include "stdio.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Macros

enum
{
    IO_OK,
    IO_ERR_READ,
    IO_ERR_LENGTH,
    IO_ERR_BUFFER,
    IO_ERR_CONVERSION,
    IO_ERR_EMPTY,
    IO_ERR_OUTPUT_ADDRESS,
    IO_ERR_FILE,
    IO_ERR_BUFFER_SIZE,
    IO_ERR_NB
};

// Functions

char const *io_sver(void);
char const *io_sid(void);

int fget_s(char *s, size_t size, FILE * fp);
int fget_c(FILE * fp);
int fget_l(long *p, FILE * fp);
int fget_ul(unsigned long * p, FILE * fp);
int fget_d(double *p, FILE * fp);

int get_s(char *s, size_t size);
int get_c(void);
int get_l(long *p);
int get_ul(unsigned long * p);
int get_d(double * p);

char *fget_line(FILE * fp, int *p_end);
char *get_line(void);

void io_perror(int err);

#ifdef __cplusplus
}
#endif

#endif