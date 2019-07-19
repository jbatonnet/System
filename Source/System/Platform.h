#ifndef _SYSTEM_PLATFORM_H_
#define _SYSTEM_PLATFORM_H_

#ifdef WINDOWS
    #define AppMain WinMain
#endif
#ifdef KERNEL
    #define AppMain main
#endif

#endif