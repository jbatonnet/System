#ifdef WINDOWS

#include <System/System.h>
#include <System/Test.h>

using namespace System;
using namespace System::Runtime;
using namespace System::Objects;
using namespace System::Devices;
using namespace System::IO;
using namespace System::Interface;
using namespace System::Graphics;

#undef lock
#undef using
#define _INITIALIZER_LIST_

#include <Windows.h>
#include <Dwmapi.h>
#include <Shlwapi.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <mutex>
//#include <map>

using namespace std;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    AppMain();
}
int main()
{
    AppMain();
}

class WindowsConsoleStream : public ConsoleStream
{
private:
    HANDLE handle;

public:
    WindowsConsoleStream()
    {
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    virtual u32 Read(void * buffer, u32 count, bool intercept) override
    {
        for (u32 i = 0; i < count; i++)
        {
            char character = cin.get();
            ((char*)buffer)[i] = character;
        }

        return count;
    }
    virtual void Write(void* buffer, u32 count) override
    {
        for (u32 i = 0; i < count; i++)
        {
            char character = ((char*)buffer)[i];

            switch (character)
            {
            case 'â': character = (char)0x83; break;
            case 'ä': character = (char)0x84; break;
            case 'à': character = (char)0x85; break;

            case 'é': character = (char)0x82; break;
            case 'ê': character = (char)0x88; break;
            case 'ë': character = (char)0x89; break;
            case 'è': character = (char)0x8A; break;

            case 'ï': character = (char)0x8B; break;
            case 'î': character = (char)0x8C; break;

            case 'ô': character = (char)0x93; break;
            case 'ö': character = (char)0x94; break;

            case 'û': character = (char)0x96; break;
            case 'ü': character = (char)0x81; break;

            case 'ç': character = (char)0x87; break;
            }

            SetConsoleTextAttribute(handle, (WORD)Console::BackColor << 4 | (WORD)Console::Color);
            cout << character;
        }
    }
};
class WindowsThread : public Thread
{
private:
    HANDLE handle;

public:
    //WindowsThread() { }
    //WindowsThread(u32 id) { }
};

ConsoleColor Console::Color = ConsoleColor::Gray;
ConsoleColor Console::BackColor = ConsoleColor::Black;

void Test::Action()
{
    std::cout << "Test::Action()" << std::endl;
}
void Test::Action(u32 parameter)
{
    std::cout << "Test::Action(" << parameter << ")" << std::endl;
}
u32 Test::Function()
{
    std::cout << "Test::Function()" << std::endl;
    return 12345678;
}
u32 Test::Function(u32 parameter)
{
    std::cout << "Test::Function(" << parameter << ")" << std::endl;
    return 87654321;
}

void* Memory::Allocate(u32 count, s16 value)
{
    if (!count)
        return null;

    void* memory = malloc(count);
    ZeroMemory(memory, count);

    return memory;
}
void Memory::Free(void* address)
{
    if (address)
        free(address);
}

ConsoleStream* Stream::GetConsoleStream()
{
    return new WindowsConsoleStream();
}
Stream* Stream::GetSerialStream()
{
	return Stream::Null;
}

Thread* Thread::GetCurrent()
{
    return null;
}

u64 Timer::Time()
{
	return timeGetTime();
}
void Timer::Sleep(u64 milliseconds)
{
	SleepEx(milliseconds, false);
}

#endif