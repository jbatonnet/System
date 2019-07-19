#include "errno.h"

int __errno;

int* _errno()
{
    return &__errno;
}