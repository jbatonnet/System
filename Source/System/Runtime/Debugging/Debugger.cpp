#include <System/Runtime/Debugging/Debugger.h>

using namespace System::Runtime;

void Debugger::Break()
{
    _asm int 3
}