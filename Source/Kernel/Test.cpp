#include <System/Test.h>
#include <System/Debugging/Console.h>

void Test::Action()
{
    Console::WriteLine("Test::Action()");
}
void Test::Action(u32 parameter)
{
    Console::WriteLine("Test::Action(0x{0:X8})", parameter);
}
u32 Test::Function()
{
    Console::WriteLine("Test::Function()");
    return 0x12345678;
}
u32 Test::Function(u32 parameter)
{
    Console::WriteLine("Test::Function(0x{0:X8})", parameter);
    return 0x9ABCDEF0;
}

#include <System/System.h>

#include <Kernel/Test.h>
#include <Kernel/Runtime/Threading/Thread.h>
#include <System/Runtime/Threading/Dispatcher.h>
#include <Kernel/Devices/Drivers/PCI/PCI.h>
#include <Kernel/Runtime/Threading/Task.h>
#include <Kernel/Memory/PMM.h>
#include <[Libraries]/ZLib/DeflateStream.h>
#include <Kernel/Devices/Drivers/Serial/SerialDevice.h>
#include <[Libraries]/SQLite/SQLiteDatabase.h>
#include <[Libraries]/SQLite/SQLiteRecord.h>
#include <Kernel/Debugging/StackTrace.h>
#include <[Libraries]/LibPNG/PngBitmap.h>

#include <HAL/Utilities.h>

using namespace System::Graphics;
using namespace System::Runtime;
using namespace System::Devices;
using namespace System::IO;
using namespace System::Data;

AddTest(RTTI)
{
    struct Animal : public Object
    {
        virtual void Scream()
        {
            Console::WriteLine("Animal::Scream");
        }
    };
    struct Monster : public Object
    {
        virtual void Hit()
        {
            Console::WriteLine("Monster::Hit");
        }
    };
    struct Lion : public Animal, public Monster
    {
        void Scream() override
        {
            Console::WriteLine("Lion::Scream");
        }
        void Hit() override
        {
            Console::WriteLine("Lion::Hit");
        }
    };

    Animal animal;
    Lion lion;

    Animal a = Lion();
    a.Scream();

    //Console::WriteLine("Lion is Animal: {0}", lion.Is<Animal>());
    //Console::WriteLine("Lion is File: {0}", animal.Is<File>());
}
AddTest(UserMode)
{
    #define USER_CODE   0x00100000 //  1 Mo
    #define KERNEL_CODE 0x02000000 // 32 Mo
    #define CODE_SIZE   0x00020000
    #define SHARED_SIZE 0x00100000 //  1 Mo

    /*MemoryMapping* kernelMapping = new MemoryMapping((PageDirectory*)MEMORY_DIRECTORIES);
    MemoryMapping* userMapping = new MemoryMapping();

    //Console::WriteLine("Copy {0} to {1}", kernelMapping->pageDirectory, userMapping->pageDirectory);
    //Memory::Copy<PageDirectory>(kernelMapping->pageDirectory, userMapping->pageDirectory);
    //Console::WriteLine("Done");

    userMapping->Map(null, null, (u32)SHARED_SIZE);

    for (u32 i = 0; i < CODE_SIZE / 0x1000; i++)
    {
        void* physicalAddress = PMM_AllocateBlock();

        kernelMapping->Map(physicalAddress, (void*)(KERNEL_CODE + i * 0x1000));
        userMapping->Map(physicalAddress, (void*)(USER_CODE + i * 0x1000));
    }

    PageDirectory* userDirectory = userMapping->pageDirectory;//*/
    //Console::WriteLine("UserDirectory: {0}", userDirectory);

    PageDirectory* kernelDirectory = (PageDirectory*)MEMORY_DIRECTORIES;
    PageDirectory* userDirectory = VMM_GetDirectory();
        
    //Memory::Clear<PageDirectory>(userDirectory);
    Memory::Copy<PageDirectory>(kernelDirectory, userDirectory);
    //Memory::Clear<u32>(userDirectory, 1);

    // Add shared space
    PageTable* userSharedTable = VMM_GetTable();
    Memory::Copy<PageTable>((void*)MEMORY_TABLES, userSharedTable);

    PageDirectoryEntry* userDirectoryEntry = &userDirectory->Entries[0];
    AddFlag(*userDirectoryEntry, PTE_PRESENT);
AddFlag(*userDirectoryEntry, PTE_WRITABLE);
AddFlag(*userDirectoryEntry, PTE_USERMODE);
    SetFrame(userDirectoryEntry, userSharedTable);

    for (u32 pageIndex = 0; pageIndex < SHARED_SIZE / 0x1000; pageIndex++)
    {
        PageTableEntry* userSharedTableEntry = &userSharedTable->Entries[pageIndex];
        AddFlag(*userSharedTableEntry, PTE_PRESENT);
AddFlag(*userSharedTableEntry, PTE_WRITABLE);
AddFlag(*userSharedTableEntry, PTE_USERMODE);
        SetFrame(userSharedTableEntry, (void*)(pageIndex * 0x1000));
    }

    // Allocate code space
    PageTable* userCodeTable = userSharedTable;
    PageTable* kernelCodeTable = VMM_GetTable();

    PageDirectoryEntry* kernelDirectoryEntry = &kernelDirectory->Entries[KERNEL_CODE / 0x400000];
    AddFlag(*kernelDirectoryEntry, PTE_PRESENT);
    AddFlag(*kernelDirectoryEntry, PTE_WRITABLE);
AddFlag(*kernelDirectoryEntry, PTE_USERMODE);
    SetFrame(kernelDirectoryEntry, kernelCodeTable);

    for (u32 pageIndex = 0; pageIndex < CODE_SIZE / 0x1000; pageIndex++)
    {
        void* physicalMemory = PMM_AllocateBlock();

        PageTableEntry* userCodeTableEntry = &userCodeTable->Entries[USER_CODE / 0x1000 + pageIndex];
        AddFlag(*userCodeTableEntry, PTE_PRESENT);
        AddFlag(*userCodeTableEntry, PTE_WRITABLE);
        AddFlag(*userCodeTableEntry, PTE_USERMODE);
        SetFrame(userCodeTableEntry, physicalMemory);

        PageTableEntry* kernelCodeTableEntry = &kernelCodeTable->Entries[(KERNEL_CODE % 0x400000) / 0x1000 + pageIndex];
        AddFlag(*kernelCodeTableEntry, PTE_PRESENT);
        AddFlag(*kernelCodeTableEntry, PTE_WRITABLE);
AddFlag(*kernelCodeTableEntry, PTE_USERMODE);
        SetFrame(kernelCodeTableEntry, physicalMemory);
    }//*/

    Console::WriteLine("Directory :");
    for (u32 i = 0; i < 11; i++)
        Console::Write("{0:X6} ", ((u32*)kernelDirectory)[i]);
    Console::WriteLine();
    for (u32 i = 0; i < 11; i++)
        Console::Write("{0:X6} ", ((u32*)userDirectory)[i]);
    Console::WriteLine();
    Console::WriteLine();

    Console::WriteLine("Table :");
    for (u32 j = 0; j < 5; j++)
    {
        for (u32 i = 0; i < 11; i++)
            Console::Write("{0:X6} ", ((u32*)MEMORY_TABLES)[j * 11 + i]);
        Console::WriteLine();
    }
    Console::WriteLine();
    for (u32 j = 0; j < 5; j++)
    {
        for (u32 i = 0; i < 11; i++)
            Console::Write("{0:X6} ", ((u32*)userSharedTable)[j * 11 + i]);
        Console::WriteLine();
    }
    Console::WriteLine();

    Console::WriteLine();
    //for (;;);

    // Refresh TLB
    _asm
    {
        mov eax, cr3
        mov cr3, eax
    }

    string appPath = "/System/Test";
    Console::WriteLine("Loading {0}", appPath);

    // Copy some code
    Stream* stream = File::OpenStream(appPath);
        
    // PE data
    u32 peHeader;
    u32 sections;
    u32 entry;
    u32 textReal, textVirtual, textSize;
    u32 rdataReal, rdataVirtual, rdataSize;
    u32 dataReal, dataVirtual, dataSize;

    // DOS header
    stream->SetPosition(0x3C);
    stream->Read(&peHeader, sizeof(u32));

    // PE header
    sections = peHeader + 0xF8;
    stream->SetPosition(peHeader + 0x28);
    stream->Read(&entry, sizeof(u32));
    //Console::WriteLine("  Entry: {0:X8}", entry);
        
    // .text
    stream->SetPosition(sections + 0x0C);
    stream->Read(&textVirtual, sizeof(u32));
    stream->Read(&textSize, sizeof(u32));
    stream->Read(&textReal, sizeof(u32));
    //Console::WriteLine("  .text: { Real: {0:X8}, Virtual: {1:X8}, Size: {2:X8} }", textReal, textVirtual, textSize);
       
    // .rdata
    stream->SetPosition(sections + 0x34);
    stream->Read(&rdataVirtual, sizeof(u32));
    stream->Read(&rdataSize, sizeof(u32));
    stream->Read(&rdataReal, sizeof(u32));
    //Console::WriteLine("  .rdata: { Real: {0:X8}, Virtual: {1:X8}, Size: {2:X8} }", rdataReal, rdataVirtual, rdataSize);

    // .data
    stream->SetPosition(sections + 0x5C);
    stream->Read(&dataVirtual, sizeof(u32));
    stream->Read(&dataSize, sizeof(u32));
    stream->Read(&dataReal, sizeof(u32));
    //Console::WriteLine("  .data: { Real: {0:X8}, Virtual: {1:X8}, Size: {2:X8} }", dataReal, dataVirtual, dataSize);
        
    // Copy everything
    stream->SetPosition(textReal);
    stream->Read((void*)(KERNEL_CODE + textVirtual), textSize);
    stream->SetPosition(rdataReal);
    stream->Read((void*)(KERNEL_CODE + rdataVirtual), rdataSize);
    stream->SetPosition(dataReal);
    stream->Read((void*)(KERNEL_CODE + dataVirtual), dataSize);

    Console::WriteLine();
    Console::WriteLine("Running {0}", appPath);
    Console::WriteLine();

    // Run .text section
    Task* userTask = new Task(TaskType::User, (void*)(USER_CODE + entry), (void*)(USER_CODE + CODE_SIZE - 4), userDirectory);// userMapping->pageDirectory);

    //for (;;);
    userTask->Run();
}
AddTest(Callables)
{
    Console::WriteLine("-- Callables --");

    class Car
    {
    public:
        static void Action()
        {
            Console::WriteLine("Car::Action()");
        }
        u32 Start(u32 test)
        {
            Console::Write("Car::Start({0}) -> ", test);
            return 4321;
        }
        void Start2(void* pointer)
        {
            Console::WriteLine("Car::Start({0})", pointer);
        }
        static u32 Initialize()
        {
            Console::Write("Car::Initialize() -> ");
            return 4321;
        }
    };

    Car car;

    u32 j = 2;
    u32 result;

    Function<u32> function1(&Car::Initialize);
    Console::WriteLine(function1());

    Function<u32, u32> function2(&car, &Car::Start);
    Console::WriteLine(function2(1234));

    Action<> action1(&Car::Action);
    action1();

    Action<int> action2([](int i) -> void { Console::WriteLine("Lambda: {0}", i); });
    action2(1234);

    Action<void*> action3(car, &Car::Start2);
    action3(&car);

    Action<int> action4([&](int i) -> void { Console::WriteLine("Lambda with capture: {0}, {1}", i, j); });
    action4(1234);
}
AddTest(FPU)
{
     Console::WriteLine("-- FPU --");

    int i;
    float f;
    double d;
        
    f = 1234567890.1234567890f;

    string value(f);
    Console::WriteLine("Floating point : {0}", value);
}
AddTest(DateTime)
{
    DateTime birthday(1991, Month::December, 21);
    Console::WriteLine("Birthday: {0}", birthday.ToLongDate());

    DateTime now(2014, Month::November, 2, 1, 2, 3, 456);
    Console::WriteLine("Now: {0}", now);

    TimeSpan age = now - birthday;
    Console::WriteLine("Age: {0}", age);
}
AddTest(String)
{
    union
    {
        u64 value;

        struct
        {
            union
            {
                char buffer[7];

                struct
                {
                    char* pointer;
                    u16 length;
                };
            };

            struct
            {
                bool embedded : 1;
                bool allocation : 1;
            } informations;
        };
    } test;

    #define WriteInfos(object, field) Console::WriteLine("{0}: {1} @{2}", #field, sizeof(field), (u8*)&field - (u8*)&object)

    Console::WriteLine("sizeof(test): {0}", sizeof(test));
    WriteInfos(test, test.informations);
    WriteInfos(test, test.buffer);
    WriteInfos(test, test.length);
    WriteInfos(test, test.pointer);

    test.value = -1;
    test.length = 0;

    for (int i = 0; i < sizeof(test); i++)
        Console::Write("{0:b8} ", ((u8*)&test)[i]);
    Console::WriteLine();


    Console::WriteLine();
    Console::WriteLine("sizeof(string): {0}", sizeof(string));

    string test1(true);
    for (int i = 0; i < sizeof(string); i++)
        Console::Write("{0:x2} ", ((u8*)&test1)[i]);
    Console::WriteLine();

    string test2("Dede");
    for (int i = 0; i < sizeof(string); i++)
        Console::Write("{0:x2} ", ((u8*)&test2)[i]);
    Console::WriteLine();
}
AddTest(Deflate)
{
    Console::WriteLine("-- Deflate --");

    Stream* fileStream = File::OpenStream("/System/Fonts/Open.font");
    Console::WriteLine("File: {0}", fileStream);

    DeflateStream* deflateStream = new DeflateStream(fileStream, CompressionMode::Decompress);
    Console::WriteLine("Stream: {0}", deflateStream);

    byte* buffer = Memory::Allocate<byte>(4096);
    Console::WriteLine("Buffer: {0}", buffer);

    deflateStream->Read(buffer, 4);
    deflateStream->Read(buffer + 4, 4);
    deflateStream->Read(buffer + 8, 8);
    deflateStream->Read(buffer + 16, 16);
    deflateStream->Read(buffer + 32, 32);

    for (int i = 0; i < 64; i++)
    {
        if (i % 0x10 == 0)
            Console::WriteLine();
        Console::Write("{0:X2} ", buffer[i]);
    }
    Console::WriteLine();

    Console::WriteLine("-- End --");
}
AddTest(Debugger)
{
    Serial::WriteLine("Debugger");
    Timer::Sleep(100);

    Stream* serialStream = Serial::BaseStream;
	DataStream dataStream(serialStream);
		
    byte b;

    for (;;)
    {
        if (!serialStream->Read(&b, 1))
            continue;

        Console::Write("{0:X2} ", b);
    }
}
AddTest(VSync)
{
    //DisplayDevice* displayDevice = Device::Get<DisplayDevice>();

    Console::WriteLine("-- VSync Test --");

    for (u32 n = 0;; n++)
    {
        //displayDevice->VSync->Wait();

        if (n % 60 == 0)
            Serial::WriteLine("VSync #{0} ({1} seconds)", n, n / 60);
    }
}
AddTest(Collections)
{
    //Array<u32, 32> array1;
    //Array<u32> array2;

	List<u32>* numbers = new List<u32>(10);

    numbers->Add(0);
    numbers->Add(1);
    numbers->Add(2);
    numbers->Add(3);
    numbers->Add(4);
    numbers->Add(5);
    numbers->Add(6);
    numbers->Add(7);
    numbers->Add(8);
    numbers->Add(9);

    Collection<u32>* collection = numbers;

    foreach (u32, number, collection)
    {
        Console::WriteLine("Item : {0}", number);
    }

    Console::WriteLine();

    Console::WriteLine("First : {0}", collection->First());
    Console::WriteLine("Last : {0}", collection->Last());

    Console::WriteLine();

    u32 factor = 3;
    Function<bool, u32> filter = [=](u32 n) -> bool { return n % factor == 0; };
    
    u32 first = collection->First(filter);
    u32 second = collection->First([=](u32 n) -> bool { return n % factor == 0; });

    //auto whereCollection = new FilteredCollection<u32>(collection, filter);
    //auto whereCollection = collection->Where([](u32 n) -> bool { return n % 3 == 0; });
    auto whereCollection = collection->Where(filter);

    foreach (u32, number, whereCollection)
    {
        Console::WriteLine("*{0} : {1}", factor, number);
    }
}
AddTest(References)
{
    struct Chicken
    {
        void Scream()
        {
            Console::WriteLine("Meuuhhh !");
        }
    };

    Reference<Chicken> cow = new Chicken();
    cow->Scream();
}
AddTest(SQLite)
{
    Database* db = new SQLiteDatabase("/System/Kernel.db");
    Console::WriteLine("SQLiteDatabase: {0}", db);
    Console::WriteLine();

    // QueryTable
    {
        Console::Write("QueryTable -> ");

        Reference<Table> table = db->QueryTable("SELECT * FROM pci_classes");
        Reference<Record> record = table->First();
        string value = record->Get(3);

        Console::WriteLine("{0}", value);
    }
    
    // QueryRecord
    {
        Console::Write("QueryRecord -> ");

        Reference<Record> record = db->QueryRecord("SELECT * FROM pci_classes WHERE class = 1 AND subclass = 128");
        string value = record->Get(3);

        Console::WriteLine("{0}", value);
    }

    // QueryValue
    {
        Console::Write("QueryValue -> ");

        u32 count = db->QueryValue<u32>("SELECT Count(*) FROM pci_classes");
        string name = db->QueryValue("SELECT name FROM pci_classes WHERE class = {0} AND subclass = {1}", 1, 128);

        Console::Write("{ Count: {0} } ", count);
        Console::Write("{ Name: {0} } ", name);
        Console::WriteLine();
    }
}
AddTest(PNG)
{
    Stream* stream = File::OpenStream("/Database.png");
    Console::WriteLine("Stream: {0}", stream);

    Bitmap* bitmap = PngBitmap::Load(stream);
    Console::WriteLine("Bitmap: {0}", (void*)bitmap);

    Console::WriteLine("{ Width: {0}, Height: {1} }", bitmap->Size.X, bitmap->Size.Y);
}
AddTest(Default)
{
    Console::WriteLine("default(bool): {0}", DefaultValue<bool>::Get());
    Console::WriteLine("default(u8): {0}", DefaultValue<u8>::Get());
    Console::WriteLine("default(u16): {0}", DefaultValue<u16>::Get());
    Console::WriteLine("default(u32): {0}", DefaultValue<u32>::Get());
    Console::WriteLine("default(unit): {0}", DefaultValue<unit>::Get());
    Console::WriteLine("default(u32*): {0}", DefaultValue<u32*>::Get());
    Console::WriteLine("default(string): \"{0}\"", DefaultValue<string>::Get());
}





/*template<typename... Args> class Frame
{
    Action<Args...> invokation;
    Tuple<Args...> parameters;

public:
    Frame(const Action<Args...>& invokation, Args... parameters) : invokation(invokation), parameters(parameters...) { }

    void Process()
    {
        Processor<Tuple<Args...>>::Process(invokation, parameters);
    }

private:
    template<typename Tuple, typename... Params> struct Processor
    {
        static void Process(const Action<Args...>& invokation, Tuple& remaining, Params... parameters)
        {
            Processor<decltype(remaining.Values), Params..., decltype(remaining.Value)>::Process(invokation, remaining.Values, parameters..., remaining.Value);
        }
    };
    template<typename Arg, typename... Params> struct Processor<Tuple<Arg>, Params...>
    {
        static void Process(const Action<Args...>& invokation, Tuple<Arg>& remaining, Params... parameters)
        {
            invokation(parameters..., remaining.Value);
        }
    };
};*/

AddTest(Events)
{
	Serial::WriteLine("test");

    u32 number = 0x4321;

    Event<u32> event;
    Function<u32, u32> function;
    Action<void*, u32> action;

    Thread::GetCurrent()->Dispatcher = new Dispatcher();

    action = [](void* origin, u32 value) -> void { Console::WriteLine("Callback: {0}", value); };
    Console::WriteLine("action set");

    event += action;
    Console::WriteLine("event set");
    
    Debugger::Break();
    event(null, 1234);
    Console::WriteLine("event called");

    Thread::GetCurrent()->Dispatcher->Flush();

    return;



    /*Console::WriteLine();

    // Function
    {
        function = [](u32 value) -> u32 { return value * 2; };

        for (u32 i = 0; i < sizeof(Function<u32, u32>); i++)
            Console::Write("{0:x2} ", ((u8*)&function)[i]);
        Console::WriteLine();
    }

    // Method
    {
        struct Test
        {
            u32 Half(u32 value) { return value / 2; }
        } test;

        function = Function<u32, u32>(test, &Test::Half);

        for (u32 i = 0; i < sizeof(Function<u32, u32>); i++)
            Console::Write("{0:x2} ", ((u8*)&function)[i]);
        Console::WriteLine();
    }

    // Generic
    {
        val++;
        function = [=](u32 value) -> u32 { return value + val; };

        for (u32 i = 0; i < sizeof(Function<u32, u32>); i++)
            Console::Write("{0:x2} ", ((u8*)&function)[i]);
        Console::WriteLine();
    }
    
    Console::WriteLine();

    // Function
    {
        function = [](u32 value) -> u32 { return value * 2; };

        for (u32 i = 0; i < sizeof(Function<u32, u32>); i++)
            Console::Write("{0:x2} ", ((u8*)&function)[i]);
        Console::WriteLine();
    }

    // Method
    {
        struct Test
        {
            u32 Half(u32 value) { return value / 2; }
        } test;

        function = Function<u32, u32>(test, &Test::Half);

        for (u32 i = 0; i < sizeof(Function<u32, u32>); i++)
            Console::Write("{0:x2} ", ((u8*)&function)[i]);
        Console::WriteLine();
    }

    // Generic
    {
        val++;
        function = [=](u32 value) -> u32 { return value + val; };

        for (u32 i = 0; i < sizeof(Function<u32, u32>); i++)
            Console::Write("{0:x2} ", ((u8*)&function)[i]);
        Console::WriteLine();
    }

    loop*/

    /*Event<u32> test;
    test += [](void* origin, u32 value) -> void { Console::WriteLine("Callback: {0}", value); };
    test(null, 1234);

    Thread::Current->Dispatcher->Flush();*/
    //loop
}
AddTest(Tuples)
{
    Tuple<u8, u16, u32, u64> tuple1(0, 1, 2, 3);
    Tuple<u8> tuple2;

    tuple1.At<0>() = 86;
    tuple2.At<0>() = 45;
}