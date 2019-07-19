#ifndef _KERNEL_SHELLAPPLICATION_H_
#define _KERNEL_SHELLAPPLICATION_H_

#include <System/Objects/Applications/Application.h>

class Shell : public Application
{
public:
    void Start(string parameters = "");
};

void Shell_AppMain();

#endif