#include <System/Common.h>
#include <System/Runtime/Threading/Spinlock.h>
#include <System/Runtime/Debugging/Debugger.h>

using namespace System::Runtime;

bool Spinlock::Lock(u32 timeout)
{
    Exception::Assert(timeout == 0, "Spinlocks does not support timeout yet");

	u32* statePointer = &state;

	_asm
	{
		mov ebx, [statePointer]

	spin:
		mov eax, 1
		xchg eax, [ebx]
		test eax, eax
		jnz spin
	}

    return true;
}
bool Spinlock::TryLock()
{
    u32* statePointer = &state;
    u32 result = 0;

    _asm
    {
        mov ebx, [statePointer]

        mov eax, 1
        xchg eax, [ebx]

        test [result], eax
    }

    return !result;
}

void Spinlock::Unlock()
{
    u32* statePointer = &state;

	_asm
	{
		mov ebx, [statePointer]

		mov eax, 0
		xchg eax, [ebx]
	}
}