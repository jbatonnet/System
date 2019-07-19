#ifndef _KERNEL_KERNEL_H_
#define _KERNEL_KERNEL_H_

// System
#include <System/System.h>

// Memory
#include <Kernel/Memory/Memory.h>

// Devices
#include <Kernel/Devices/Screen/Screen.h>
#include <Kernel/Devices/Drivers/Driver.h>
#include <Kernel/Devices/Drivers/FileSystems/VFS/VFS.h>

// Tasking
//#include <Kernel/Tasking/Task.h>
//#include <Kernel/Tasking/Mutex.h>

// Reflection
//#include <Kernel/Runtime/Type.h>

// Global vars
extern System::Devices::Drivers::VFS*  Vfs;
extern System::IO::Directory*          StorageDirectory;
extern List<System::Devices::Device*>* Devices;

#endif