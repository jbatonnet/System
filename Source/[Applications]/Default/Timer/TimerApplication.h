#ifndef _TIMERAPPLICATION_H_
#define _TIMERAPPLICATION_H_

#include <System/Objects/Applications/Application.h>

class TimerApplication : public Application
{
public:
    void Start(string parameters = "");
};

void TimerApplication_Main();

#endif