#ifndef _KERNEL_SERIALDRIVER_H_
#define _KERNEL_SERIALDRIVER_H_

#include <Kernel/Devices/Drivers/Driver.h>

class SerialDriver : public System::Devices::Driver
{
public:
    SerialDriver();

	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "Basic serial driver";  }

    void Load() override;
    void Unload() override;
};

#endif