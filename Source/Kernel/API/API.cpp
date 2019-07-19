#include <HAL/Interrupts.h>
#include <Kernel/Runtime/Threading/Task.h>
#include <Kernel/Memory/Memory.h>

#include <System/Common.h>
#include <System/System.h>
#include <System/Test.h>
#include <System/Base/Default.h>
#include <System/Base/Events.h>
#include <System/Base/Exception.h>
#include <System/Base/Flags.h>
#include <System/Base/Functions.h>
#include <System/Base/Macros.h>
#include <System/Base/Object.h>
#include <System/Base/Parameters.h>
#include <System/Base/Reference.h>
#include <System/Base/String.h>
#include <System/Base/Templates.h>
#include <System/Base/Types.h>
#include <System/Base/Unit.h>
#include <System/Data/Database.h>
#include <System/Data/Record.h>
#include <System/Data/Table.h>
#include <System/Debugging/Console.h>
#include <System/Debugging/Log.h>
#include <System/Debugging/Serial.h>
#include <System/Devices/Device.h>
#include <System/Devices/Communication/CommunicationDevice.h>
#include <System/Devices/Display/DisplayDevice.h>
#include <System/Devices/Input/ButtonsDevice.h>
#include <System/Devices/Input/InputDevice.h>
#include <System/Devices/Input/InputManager.h>
#include <System/Devices/Input/PointerDevice.h>
#include <System/Devices/Storage/FileSystem.h>
#include <System/Devices/Storage/StorageDevice.h>
#include <System/Graphics/Bitmap.h>
#include <System/Graphics/Colors.h>
#include <System/Graphics/Font.h>
#include <System/Graphics/Point.h>
#include <System/Graphics/Surface.h>
#include <System/Interface/Element.h>
#include <System/Interface/Window.h>
#include <System/Interface/WindowsManager.h>
#include <System/Interface/Controls/Button.h>
#include <System/Interface/Controls/Control.h>
#include <System/Interface/Controls/Field.h>
#include <System/Interface/Controls/Graph.h>
#include <System/Interface/Controls/Image.h>
#include <System/Interface/Controls/Label.h>
#include <System/Interface/Controls/ListView.h>
#include <System/Interface/Controls/Menu.h>
#include <System/Interface/Controls/Containers/Container.h>
#include <System/Interface/Controls/Containers/Grid.h>
#include <System/Interface/Controls/Containers/ScrollContainer.h>
#include <System/Interface/Controls/Containers/SideMenu.h>
#include <System/Interface/Controls/Containers/StackContainer.h>
#include <System/Interface/Controls/Containers/Tab.h>
#include <System/Interface/Controls/Containers/TabContainer.h>
#include <System/Interface/Controls/Containers/Table.h>
#include <System/IO/File.h>
#include <System/IO/Streams/AsyncStream.h>
#include <System/IO/Streams/DataStream.h>
#include <System/IO/Streams/Stream.h>
#include <System/IO/Streams/TeeStream.h>
#include <System/IO/Streams/TextStream.h>
#include <System/Maths/Maths.h>
#include <System/Maths/Matrixes.h>
#include <System/Maths/Vectors.h>
#include <System/Memory/Memory.h>
#include <System/Objects/Entity.h>
#include <System/Objects/User.h>
#include <System/Runtime/Reflection/Constructor.h>
#include <System/Runtime/Reflection/Method.h>
#include <System/Runtime/Reflection/Namespace.h>
#include <System/Runtime/Reflection/Property.h>
#include <System/Runtime/Reflection/Symbol.h>
#include <System/Runtime/Reflection/Type.h>
#include <System/Runtime/Serialization/Serializer.h>
#include <System/Runtime/Serialization/XML.h>
#include <System/Runtime/Threading/Mutex.h>
#include <System/Runtime/Threading/Process.h>
#include <System/Runtime/Threading/Signal.h>
#include <System/Runtime/Threading/Thread.h>
#include <System/Structures/Dictionary.h>
#include <System/Structures/List.h>
#include <System/Structures/ObservableList.h>
#include <System/Structures/Queue.h>
#include <System/Structures/Stack.h>
#include <System/Structures/Collections/Collection.h>
#include <System/Structures/Collections/ConcatenedCollection.h>
#include <System/Structures/Collections/FilteredCollection.h>
#include <System/Structures/Collections/OrderedCollection.h>
#include <System/Structures/Collections/ProjectedCollection.h>
#include <System/Structures/Graphs/GraphNode.h>
#include <System/Structures/Trees/Tree.h>
#include <System/Structures/Trees/TreeNode.h>
#include <System/Utilities/Random.h>
#include <System/Utilities/Units.h>
//#include <System/Utilities/Containers/IContainer.h>
#include <System/Utilities/Time/DateTime.h>
#include <System/Utilities/Time/Enums.h>
#include <System/Utilities/Time/Timer.h>
#include <System/Utilities/Time/TimeSpan.h>

using namespace System;
using namespace Types;
using namespace Values;
using namespace System::Runtime;
using namespace System::Data;
using namespace System::Devices;
using namespace System::IO;
using namespace System::Graphics;
using namespace System::Interface;
using namespace System::Objects;

struct API_Interrupt
{
    u64 Id;
    u64 Time;

    Task* Task;
    u32 Function;
    u32 ObjectId;
    void* Parameters;
    void* Result;

    API_Interrupt* Next;
};

API_Interrupt *firstInterrupt = null, *lastInterrupt = null;
u32 interruptIds = 0;

u32 sharedIds = 1;
void* sharedObjects[256] = { null };

Signal* signal = null;

void API_InterruptHandler(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)
{
    API_Interrupt* newInterrupt = new API_Interrupt();

    newInterrupt->Id = interruptIds++;
    newInterrupt->Time = Timer::Time();
    newInterrupt->Task = Task::Current;
    newInterrupt->Function = registers.eax;
    newInterrupt->ObjectId = registers.ebx;
    newInterrupt->Parameters = (void*)registers.esi;
    newInterrupt->Result = (void*)registers.edi;
    newInterrupt->Next = null;

    if (firstInterrupt)
    {
        lastInterrupt->Next = newInterrupt;
        lastInterrupt = newInterrupt;
    }
    else
        firstInterrupt = lastInterrupt = newInterrupt;

    Task::Current->mode = TaskMode::WaitAPI;

    //signal->Send();
}

void API_HandleInterrupts()
{
    signal = new Signal();

    for (;;)
    {
        //signal->Wait();

        if (!firstInterrupt)
        {
            _asm hlt
            continue;
        }

        switch (firstInterrupt->Function)
        {
            #pragma region u64 ConsoleStream::GetLength()

            case 0xDD1E31FF:
            {
                ConsoleStream* object = (ConsoleStream*)sharedObjects[firstInterrupt->ObjectId];

                u64 result = object->GetLength();
                Memory::Copy<u64>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
            }
            break;

            #pragma endregion
            #pragma region u32 ConsoleStream::Read(void* buffer, u32 count)

            case 0x817EB885:
            {
                ConsoleStream* object = (ConsoleStream*)sharedObjects[firstInterrupt->ObjectId];
                void** bufferPtr = (void**)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                void* buffer = (void*)Memory_Translate((void*)*bufferPtr, firstInterrupt->Task, Task::Kernel);
                u32* count = (u32*)Memory_Translate((void*)((u32)firstInterrupt->Parameters + sizeof(void*)), firstInterrupt->Task, Task::Kernel);

                u32 result = object->Read(buffer, *count);
                Memory::Copy<u32>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
            }
            break;

            #pragma endregion
            #pragma region u32 ConsoleStream::Read(void* buffer, u32 count, bool intercept)

            case 0xA94D1836:
            {
                ConsoleStream* object = (ConsoleStream*)sharedObjects[firstInterrupt->ObjectId];
                void** bufferPtr = (void**)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                void* buffer = (void*)Memory_Translate((void*)*bufferPtr, firstInterrupt->Task, Task::Kernel);
                u32* count = (u32*)Memory_Translate((void*)((u32)firstInterrupt->Parameters + sizeof(void*)), firstInterrupt->Task, Task::Kernel);
                bool* intercept = (bool*)Memory_Translate((void*)((u32)firstInterrupt->Parameters + sizeof(void*) + sizeof(u32)), firstInterrupt->Task, Task::Kernel);

                u32 result = object->Read(buffer, *count, *intercept);
                Memory::Copy<u32>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
            }
            break;

            #pragma endregion
            #pragma region void ConsoleStream::Write(void* buffer, u32 count)

            case 0x83D4728A:
            {
                ConsoleStream* object = (ConsoleStream*)sharedObjects[firstInterrupt->ObjectId];
                void** bufferPtr = (void**)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                void* buffer = (void*)Memory_Translate((void*)*bufferPtr, firstInterrupt->Task, Task::Kernel);
                u32* count = (u32*)Memory_Translate((void*)((u32)firstInterrupt->Parameters + sizeof(void*)), firstInterrupt->Task, Task::Kernel);

                object->Write(buffer, *count);
            }
            break;

            #pragma endregion
            #pragma region void* System::Graphics::Bitmap::GetData()

            case 0x2F3010DA:
            {
                Bitmap* object = (Bitmap*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] struct void* class System::Graphics::Bitmap::GetData()", null);
#endif
                void* result = object->GetData();
                Memory::Copy<void*>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region Point2 System::Graphics::Bitmap::GetSize()

            case 0xE645B6D7:
            {
                Bitmap* object = (Bitmap*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::WriteLine("[API] struct Point2 class System::Graphics::Bitmap::GetSize()", null);
#endif
                Point2 result = object->GetSize();
                Memory::Copy<Point2>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine();
#endif
            }
            break;

            #pragma endregion
            #pragma region string System::Graphics::Bitmap::ToString()

            case 0xD372CABF:
            {
                Bitmap* object = (Bitmap*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] struct string class System::Graphics::Bitmap::ToString()", null);
#endif
                string result = object->ToString();
                char* sharedString = (char*)Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel);
                Memory::Copy(result.Buffer, sharedString, result.Length);
                sharedString[result.Length] = 0;
#if DEBUG_API
                Console::WriteLine(" > \"{0}\"", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region System::Graphics::Font* System::Graphics::FontFamily::GetFont(u8 height, System::Graphics::FontAttribute attributes)

            case 0xF70B9008:
            {
                FontFamily* object = (FontFamily*)sharedObjects[firstInterrupt->ObjectId];
                u8* height = (u8*)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                System::Graphics::FontAttribute* attributes = (System::Graphics::FontAttribute*)Memory_Translate((void*)((u32)firstInterrupt->Parameters + sizeof(u8)), firstInterrupt->Task, Task::Kernel);

#if DEBUG_API
                Console::Write("[API] struct System::Graphics::Font* class System::Graphics::FontFamily::GetFont({0}, {1})", height, (u32)attributes);
#endif
                System::Graphics::Font* result = object->GetFont(*height, *attributes);
                Memory::Copy<System::Graphics::Font*>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region string System::IO::File::GetPath()

            case 0x977FF228:
            {
                File* object = (File*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] struct string class System::IO::File::GetPath()", null);
#endif
                string result = object->GetPath();
                char* sharedString = (char*)Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel);
                Memory::Copy(result.Buffer, sharedString, result.Length);
                sharedString[result.Length] = 0;
#if DEBUG_API
                Console::WriteLine(" > \"{0}\"", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region string System::IO::File::GetName()

            case 0x8B6A1A85:
            {
                File* object = (File*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] struct string class System::IO::File::GetName()", null);
#endif
                string result = object->GetName();
                char* sharedString = (char*)Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel);
                Memory::Copy(result.Buffer, sharedString, result.Length);
                sharedString[result.Length] = 0;
#if DEBUG_API
                Console::WriteLine(" > \"{0}\"", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region string System::IO::File::GetExtension()

            case 0xC541E069:
            {
                File* object = (File*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] struct string class System::IO::File::GetExtension()", null);
#endif
                string result = object->GetExtension();
                char* sharedString = (char*)Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel);
                Memory::Copy(result.Buffer, sharedString, result.Length);
                sharedString[result.Length] = 0;
#if DEBUG_API
                Console::WriteLine(" > \"{0}\"", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region u64 System::IO::File::GetSize()

            case 0xC99C2F27:
            {
                File* object = (File*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] class u64 class System::IO::File::GetSize()", null);
#endif
                u64 result = object->GetSize();
                Memory::Copy<u64>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", (u32)result);
#endif
            }
            break;

            #pragma endregion
            #pragma region System::IO::Stream* System::IO::File::GetStream()

            case 0x54F72F51:
            {
                File* object = (File*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] class System::IO::Stream* class System::IO::File::GetStream()", null);
#endif
                System::IO::Stream* result = object->GetStream();
                Memory::Copy<System::IO::Stream*>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region string System::IO::Directory::GetName()

            case 0xAE028CA3:
            {
                Directory* object = (Directory*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] struct string class System::IO::Directory::GetName()", null);
#endif
                string result = object->GetName();
                char* sharedString = (char*)Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel);
                Memory::Copy(result.Buffer, sharedString, result.Length);
                sharedString[result.Length] = 0;
#if DEBUG_API
                Console::WriteLine(" > \"{0}\"", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region System::IO::Directory* System::IO::Directory::GetParent()

            case 0x7EB8834F:
            {
                Directory* object = (Directory*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] class System::IO::Directory* class System::IO::Directory::GetParent()", null);
#endif
                System::IO::Directory* result = object->GetParent();
                Memory::Copy<System::IO::Directory*>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region string System::IO::Directory::GetFullPath()

            case 0x1CA0760B:
            {
                Directory* object = (Directory*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] struct string class System::IO::Directory::GetFullPath()", null);
#endif
                string result = object->GetFullPath();
                char* sharedString = (char*)Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel);
                Memory::Copy(result.Buffer, sharedString, result.Length);
                sharedString[result.Length] = 0;
#if DEBUG_API
                Console::WriteLine(" > \"{0}\"", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region void System::IO::Directory::AddDirectory(System::IO::Directory* directory)

            case 0xD3A92B1E:
            {
                Directory* object = (Directory*)sharedObjects[firstInterrupt->ObjectId];
                System::IO::Directory** directoryPtr = (System::IO::Directory**)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                System::IO::Directory* directory = (System::IO::Directory*)Memory_Translate((void*)*directoryPtr, firstInterrupt->Task, Task::Kernel);

#if DEBUG_API
                Console::WriteLine("[API] struct void class System::IO::Directory::AddDirectory({0})", directory);
#endif
                object->AddDirectory(directory);
            }
            break;

            #pragma endregion
            #pragma region void System::IO::Directory::AddFile(System::IO::File* file)

            case 0xEE0643BE:
            {
                Directory* object = (Directory*)sharedObjects[firstInterrupt->ObjectId];
                System::IO::File** filePtr = (System::IO::File**)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                System::IO::File* file = (System::IO::File*)Memory_Translate((void*)*filePtr, firstInterrupt->Task, Task::Kernel);

#if DEBUG_API
                Console::WriteLine("[API] struct void class System::IO::Directory::AddFile({0})", file);
#endif
                object->AddFile(file);
            }
            break;

            #pragma endregion
            #pragma region System::IO::Directory* System::IO::Directory::GetDirectory(string path)

            case 0x221E066B:
            {
                Directory* object = (Directory*)sharedObjects[firstInterrupt->ObjectId];
                string* pathString = (string*)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                char* pathChars = new char[pathString->Length];
                Memory::Copy(Memory_Translate((void*)pathString->Buffer, firstInterrupt->Task, Task::Kernel), pathChars, pathString->Length);
                string path(pathChars, pathString->Length);

#if DEBUG_API
                Console::Write("[API] class System::IO::Directory* class System::IO::Directory::GetDirectory(\"{0}\")", path);
#endif
                System::IO::Directory* result = object->GetDirectory(path);
                Memory::Copy<System::IO::Directory*>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region System::IO::File* System::IO::Directory::GetFile(string path)

            case 0x88D3AA3A:
            {
                Directory* object = (Directory*)sharedObjects[firstInterrupt->ObjectId];
                string* pathString = (string*)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                char* pathChars = new char[pathString->Length];
                Memory::Copy(Memory_Translate((void*)pathString->Buffer, firstInterrupt->Task, Task::Kernel), pathChars, pathString->Length);
                string path(pathChars, pathString->Length);

#if DEBUG_API
                Console::Write("[API] class System::IO::File* class System::IO::Directory::GetFile(\"{0}\")", path);
#endif
                System::IO::File* result = object->GetFile(path);
                Memory::Copy<System::IO::File*>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region u64 System::IO::Stream::GetPosition()

            case 0x482CB04A:
            {
                Stream* object = (Stream*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] class u64 class System::IO::Stream::GetPosition()", null);
#endif
                u64 result = object->GetPosition();
                Memory::Copy<u64>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", (u32)result);
#endif
            }
            break;

            #pragma endregion
            #pragma region void System::IO::Stream::SetPosition(u64 position)

            case 0x3EE223AD:
            {
                Stream* object = (Stream*)sharedObjects[firstInterrupt->ObjectId];
                u64* position = (u64*)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);

#if DEBUG_API
                Console::WriteLine("[API] struct void class System::IO::Stream::SetPosition({0})", position);
#endif
                object->SetPosition(*position);
            }
            break;

            #pragma endregion
            #pragma region u64 System::IO::Stream::GetLength()

            case 0x5E29FC88:
            {
                Stream* object = (Stream*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] class u64 class System::IO::Stream::GetLength()", null);
#endif
                u64 result = object->GetLength();
                Memory::Copy<u64>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", (u32)result);
#endif
            }
            break;

            #pragma endregion
            #pragma region bool System::IO::Stream::IsEndOfStream()

            case 0xE9CF6894:
            {
                Stream* object = (Stream*)sharedObjects[firstInterrupt->ObjectId];

#if DEBUG_API
                Console::Write("[API] struct bool class System::IO::Stream::IsEndOfStream()", null);
#endif
                bool result = object->IsEndOfStream();
                Memory::Copy<bool>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region u32 System::IO::Stream::Read(void* buffer, u32 count)

            case 0x7F218A1C:
            {
                Stream* object = (Stream*)sharedObjects[firstInterrupt->ObjectId];
                void** bufferPtr = (void**)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                void* buffer = (void*)Memory_Translate((void*)*bufferPtr, firstInterrupt->Task, Task::Kernel);
                u32* count = (u32*)Memory_Translate((void*)((u32)firstInterrupt->Parameters + sizeof(void*)), firstInterrupt->Task, Task::Kernel);

#if DEBUG_API
                Console::Write("[API] class u32 class System::IO::Stream::Read({0}, {1})", buffer, count);
#endif
                u32 result = object->Read(buffer, *count);
                Memory::Copy<u32>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));
#if DEBUG_API
                Console::WriteLine(" > {0}", result);
#endif
            }
            break;

            #pragma endregion
            #pragma region void System::IO::Stream::Write(void* buffer, u32 count)

            case 0x0AF90658:
            {
                Stream* object = (Stream*)sharedObjects[firstInterrupt->ObjectId];
                void** bufferPtr = (void**)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                void* buffer = (void*)Memory_Translate((void*)*bufferPtr, firstInterrupt->Task, Task::Kernel);
                u32* count = (u32*)Memory_Translate((void*)((u32)firstInterrupt->Parameters + sizeof(void*)), firstInterrupt->Task, Task::Kernel);

#if DEBUG_API
                Console::WriteLine("[API] struct void class System::IO::Stream::Write({0}, {1})", buffer, count);
#endif
                object->Write(buffer, *count);
            }
            break;

            #pragma endregion
            #pragma region void System::IO::Stream::Seek(u64 position, System::IO::SeekOrigin origin)

            case 0xFFCA19D0:
            {
                Stream* object = (Stream*)sharedObjects[firstInterrupt->ObjectId];
                u64* position = (u64*)Memory_Translate((void*)((u32)firstInterrupt->Parameters), firstInterrupt->Task, Task::Kernel);
                System::IO::SeekOrigin* origin = (System::IO::SeekOrigin*)Memory_Translate((void*)((u32)firstInterrupt->Parameters + sizeof(u64)), firstInterrupt->Task, Task::Kernel);

#if DEBUG_API
                Console::WriteLine("[API] struct void class System::IO::Stream::Seek({0}, {1})", position, (u32)origin);
#endif
                object->Seek(*position, *origin);
            }
            break;

            #pragma endregion
        }

        _asm cli

        firstInterrupt->Task->mode = TaskMode::Normal;
        delete firstInterrupt;
        firstInterrupt = firstInterrupt->Next;

        _asm sti

        Timer::Sleep(0);
    }
}
