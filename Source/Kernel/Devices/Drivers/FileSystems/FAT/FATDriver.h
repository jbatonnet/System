#ifndef _KERNEL_FATDRIVER_H_
#define _KERNEL_FATDRIVER_H_

#include <Kernel/Devices/Drivers/Driver.h>

class FATDriver : public System::Devices::Driver
{
public:
    FATDriver();
	
	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "Basic FAT driver to support FAT16 and FAT32 filesystems"; }

    void Load() override;
    void Unload() override;
};

#endif