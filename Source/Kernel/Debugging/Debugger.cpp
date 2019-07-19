#include <Kernel/Debugging/Debugger.h>

#include <System/Common.h>
#include <System/Debugging/Console.h>
#include <System/Utilities/Time/Timer.h>

using namespace System;

bool Debugger::present = false;
bool Debugger::attached = false;

void Debugger::Initialize()
{
    /*Console::Write("Waiting for debugger to attach ... ");

	u64 timeout = Timer::Time() + 2000;
    while (!attached && Timer::Time() < timeout);

	Console::WriteLine(attached ? "OK" : "Nope");*/

	while (!attached);
}