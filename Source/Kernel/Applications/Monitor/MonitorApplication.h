#ifndef _KERNEL_MONITORAPPLICATION_H_
#define _KERNEL_MONITORAPPLICATION_H_

#include <System/Objects/Applications/Application.h>

class MonitorApplication : public Application
{
public:
    void Start(string parameters = "");
};

void MonitorApplication_Main();

#endif