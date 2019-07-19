#include <HAL/HAL.h>
#include <HAL/Utilities.h>

#include <Kernel/Multiboot.h>
#include <Kernel/Kernel.h>
#include <Kernel/API/API.h>
#include <Kernel/Test.h>
#include <Kernel/Shell.h>

#include "Exceptions.h"

#include <Kernel/Memory/PMM.h>

// Devices
#include <Kernel/Devices/DeviceManager.h>
#include <Kernel/Devices/Drivers/FileSystems/FAT/FATDriver.h>
#include <Kernel/Devices/Drivers/ATA/ATADriver.h>
#include <Kernel/Devices/Drivers/VESA/VESADriver.h>
#include <Kernel/Devices/Drivers/Serial/SerialDriver.h>
#include <Kernel/Devices/Drivers/Keyboard/KeyboardDriver.h>
#include <Kernel/Devices/Drivers/VMware/Mouse/MouseDriver.h>
#include <Kernel/Devices/Drivers/PCI/PCIDriver.h>
#include <Kernel/Devices/Drivers/VMware/VMwareDriver.h>

// Applications
#include <Kernel/Applications/Launcher/LauncherApplication.h>
#include <Kernel/Applications/Shell/ShellApplication.h>
#include <Kernel/Applications/Monitor/MonitorApplication.h>
#include <Kernel/Applications/Breakout/BreakoutGame.h>

// Runtime
#include <Kernel/Runtime/Threading/Dispatcher.h>
#include <Kernel/Debugging/Debugger.h>

// Other
#include <[Libraries]/SQLite/SQLiteDatabase.h>
#include <[Applications]/Windows/Editor.cpp>

using namespace System::Devices;
using namespace System::Devices::Drivers;
using namespace System::IO;
using namespace System::Graphics;
using namespace System::Interface;
using namespace System::Runtime;
using namespace System::Data;

extern void InitializeConstructors();
void RunTest();
void StatsThread();

void Main(MultibootInfo* bootInfo)
{
    Clear();

    #pragma region Kernel initialization

    Write("Loading ...\n");
    Write("\n");

    Write("Initializing Hardware Abstraction Layer ... ");
    HAL_Load();
    Write("OK\n");

    Write("Initializing Interrupts ... ");
    Interrupt_Initialize();
    Interrupt_AddExceptionHandler(0x00, (InterruptHandler)Exception_DivideByZero);
    Interrupt_AddExceptionHandler(0x01, Exception_SingleStep);
    Interrupt_AddExceptionHandler(0x02, Exception_NMI);
    Interrupt_AddExceptionHandler(0x03, Exception_Breakpoint);
    Interrupt_AddExceptionHandler(0x04, Exception_Overflow);
    Interrupt_AddExceptionHandler(0x05, (InterruptHandler)Exception_BoundsCheck);
    Interrupt_AddExceptionHandler(0x06, (InterruptHandler)Exception_InvalidOPCode);
    Interrupt_AddExceptionHandler(0x07, Exception_NoDevice);
    Interrupt_AddExceptionHandler(0x08, Exception_DoubleFault);
    Interrupt_AddExceptionHandler(0x0A, Exception_InvalidTSS);
    Interrupt_AddExceptionHandler(0x0B, Exception_NoSegment);
    Interrupt_AddExceptionHandler(0x0C, Exception_StackFault);
    Interrupt_AddExceptionHandler(0x0D, (InterruptHandler)Exception_GeneralProtectionFault);
    Interrupt_AddExceptionHandler(0x0E, Exception_PageFault);
    Interrupt_AddExceptionHandler(0x10, Exception_FPUFault);
    Interrupt_AddExceptionHandler(0x11, Exception_AlignmentCheck);
    Interrupt_AddExceptionHandler(0x12, Exception_MachineCheck);
    Interrupt_AddExceptionHandler(0x13, Exception_SimdFPUFault);
    //Interrupt_AddSystemHandler((InterruptHandler)API_InterruptHandler);
    Interrupt_Enable();
    Write("OK\n");

	Write("Waiting for the debugger to attach ... ");
	::Debugger::Initialize();
	Write("OK\n");

    Write("Initializing Memory ... ");
    Memory_Initialize(bootInfo);
    Task::PreInitialize();
    InitializeConstructors();
    Write("%d Mo\n", PMM_GetTotalMemory() / 1024 / 1024);

    Write("Initializing Multitasking ... ");
    Task::Initialize();
    Write("OK\n");

    _asm sti

    //void* interruptsStack = Memory::Allocate(0x4000);
    //Task* interruptsTask = new Task(TaskType::Kernel, API_HandleInterrupts, (void*)((u32)interruptsStack + 0x4000 - 4), (void*)HEAP_BASE);
    //interruptsTask->Run();

    Write("\n");

    #pragma endregion
    #pragma region Drivers initialization

    Console::WriteLine("Installing drivers ... ");

    Console::Write("\tMouse ... ");       DeviceManager::RegisterDriver<MouseDriver>();    Console::WriteLine("OK");
    Console::Write("\tKeyboard ... ");    DeviceManager::RegisterDriver<KeyboardDriver>(); Console::WriteLine("OK");
    Console::Write("\tFileSystems ... "); DeviceManager::RegisterDriver<FATDriver>();      Console::WriteLine("OK");
    Console::Write("\tATA ... ");         DeviceManager::RegisterDriver<ATADriver>();      Console::WriteLine("OK");
    Console::Write("\tSerial ... ");      DeviceManager::RegisterDriver<SerialDriver>();   Console::WriteLine("OK");
    //Console::Write("\tVESA ... ");      DeviceManager::RegisterDriver<VESADriver>();     Console::WriteLine("OK");
	Console::Write("\tVMWare ... ");      DeviceManager::RegisterDriver<VMwareDriver>();   Console::WriteLine("OK");
	Console::Write("\tPCI ... ");         DeviceManager::RegisterDriver<PCIDriver>();      Console::WriteLine("OK");

    Console::WriteLine();

    #pragma endregion
    #pragma region System initialization

	// Components initializations
    InputManager::Initialize();
    //FontFamily::Initialize();

	// System database
	Database::Default = new SQLiteDatabase("/System/Kernel.db");
    
    // Resources preloading
    #pragma region Bitmaps

    Bitmap::Load("/System/Images/Icons/Close.png");
    Bitmap::Load("/System/Images/Cursors/Normal.image");

    #pragma endregion

    #pragma endregion

    Shell_Main();

    if (false)
        Thread::Start(RunTest);
    else
    {
        WindowsManager::Initialize();

		//Thread::Start(LauncherApplication_Main, "Launcher");
        Thread::Start(Test_Editor, "Test");

		Timer::Sleep(100);

        //Thread::Start(TestApplication_Main, "Test 1");
        //Timer::Sleep(100);

        //Thread::Start(TestApplication_Main, "Test 2");
        //Timer::Sleep(100);

        //Thread::Start(BreakoutGame_Main, "Breakout");
        //Timer::Sleep(100);

        //Thread(FilesApplication_Main, "Files").Start();
        //Timer::Sleep(100);

        //Thread(DatabasesApplication_Main, "Databases").Start();
        //Timer::Sleep(100);

        //Thread(MonitorApplication_Main, "Monitor").Start();
		//Timer::Sleep(100);

		Timer::Sleep(400);
    }

    Task::PostInitialize();

    // Run interrupts
    for (;;)
    {
        interruptDispatcher.Flush();
        Timer::Sleep(0);
    }

    Console::WriteLine();
    Console::Write("End");
}

void RunTest()
{
    RunTest("Events");
}