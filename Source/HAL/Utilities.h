#ifndef _HAL_UTILITIES_H_
#define _HAL_UTILITIES_H_

#include <HAL/Types.h>

#define AddFlag(value, flag) (value |= flag);
#define RemoveFlag(value, flag) (value &= ~flag);
#define IsFlag(value, flag) ((value & flag) == flag)

#endif