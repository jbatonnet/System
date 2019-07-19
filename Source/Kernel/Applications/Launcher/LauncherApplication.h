#ifndef _KERNEL_LAUNCHERAPPLICATION_H_
#define _KERNEL_LAUNCHERAPPLICATION_H_

#include <System/Objects/Applications/Application.h>

class LauncherApplication : public Application
{
public:
    void Start(string parameters = "");
};

void LauncherApplication_Main();

#endif