#ifndef _SYSTEM_COMMON_H_
#define _SYSTEM_COMMON_H_

#ifdef __clang__
#define _declspec(x) const volatile
#endif

#include <System/Base/Types.h>
#include <System/Base/Flags.h>
#include <System/Base/String.h>
#include <System/Base/Object.h>
#include <System/Base/Reference.h>
#include <System/Base/Unit.h>
#include <System/Base/Parameters.h>
#include <System/Base/Functions.h>
#include <System/Base/Events.h>
#include <System/Base/Exception.h>
#include <System/Base/Macros.h>
#include <System/Base/Default.h>
#include <System/Base/Templates.h>

#define loop for (;;) _asm hlt

#endif