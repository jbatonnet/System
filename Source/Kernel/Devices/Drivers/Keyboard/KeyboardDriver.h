#ifndef _KERNEL_KEYBOARDDRIVER_H_
#define _KERNEL_KEYBOARDDRIVER_H_

#include <Kernel/Devices/Drivers/Driver.h>

class KeyboardDriver : public System::Devices::Driver
{
public:
    KeyboardDriver();
    
    void Load() override;
    void Unload() override;

	string GetEditor() override { return "Dju'"; }
	string GetName() override { return "Basic keyboard driver"; }
};

#endif