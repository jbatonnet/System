#include <System/System.h>

#include "Windows.h"

#include "../../[Applications]/Default/Timer/TimerApplication.h"
#include "../../[Applications]/Default/Files/FilesApplication.cpp"

#include <[Libraries]/LibPNG/PngBitmap.h>
#include <[Libraries]/Basics/Documents/Fonts/BasicFontFamily.h>

using namespace System::IO;
using namespace System::Interface;
using namespace System::Runtime;
using namespace System::Graphics;
using namespace System::Devices;

struct Animal : Object
{
    virtual void Scream() = 0;

    u32 speed;
    virtual void SetSpeed(u32 value) { Console::WriteLine("Animal::SetSpeed()"); }
    _declspec(property(put = SetSpeed)) u32 Speed;
};
struct Lion : Animal
{
    Lion()
    {
        Console::WriteLine("Lion() -> {0}", (void*)this);
    }

    void Scream()
    {
        Console::WriteLine("Roarr !");
    }

    virtual void SetSpeed(u32 value) { Console::WriteLine("Lion::SetSpeed()"); }
};

ResourceLoader<Bitmap, PngBitmap> pngBitmapLoader("png");
ResourceLoader<FontFamily, BasicFontFamily> basicFontFamilyLoader("raw");

void AppMain()
{
    /*{
        InitializerCollection<int> test1 { 0, 1, 2, 3, 4 };
        List<int> test2 { 5, 6, 7, 8, 9 };

        for (int n : test1)
            Console::WriteLine("Test: {0}", n);
    }

    Console::Read(true);
    return;*/

    WindowsManager::Initialize();

    Test_Files();

    //TimerApplication_Main();
    //FilesApplication_Main();

    while (true)
        Timer::Sleep(10);

    return;

    /*{
        File* file = File::Open("D:\\Web\\web.config");
        Stream* stream = file ? file->GetStream() : null;
        TextStream* textStream = stream ? new TextStream(stream) : null;

        if (textStream)
        {
            while (!textStream->EndOfStream)
            {
                string line = textStream->ReadLine();
                Console::WriteLine(line);
            }
        }
    }*/

    /*{
        float value = 81;
        value = Maths::Pow(value, 0.5);

        Console::WriteLine("Floating point: {0}", value);
    }*/

    {
    }

    {
        string test = "Hello World !";

        Console::WriteLine(test);
    }

    {
        Dynamic<Lion> lion([]() -> Lion* { return new Lion(); });

        Console::WriteLine("Lion is Animal: {0}", lion->Is<Animal>());
        lion->Scream();

        Console::WriteLine();
    }

    {
        Action<void*, u32> action = [](void* origin, u32 param) { Console::WriteLine("Action: {0}, {1}", origin, param); };

        Event<u32> testEvent;
        testEvent += action;

        testEvent(null, 1234);
        Console::WriteLine();
    }

    {
        Directory* directory = Directory::Root;
        Console::WriteLine("Root: {0}", directory->Name);

        //foreach (File*, file, &directory->Files)
        //    Console::WriteLine("File: {0}", file->Name);

        Console::WriteLine();
    }

    {
        DateTime date(1991, Month::December, 21);
        DateTime now(2015, Month::August, 12);

        TimeSpan diff = now - date;

        Console::WriteLine("Date: {0}", date.ToLongDate());
        Console::WriteLine("Now: {0}", now.ToLongDate());
        Console::WriteLine("Diff: {0}", diff.Days);

        Console::WriteLine();
    }

    {
        List<string>* list = new List<string>();

        list->Add("Amélie");
        list->Add("Benoît");
        list->Add("Clara");
        list->Add("Daniel");
        list->Add("Emilie");
        list->Add("François");

        Reference<Collection<string>> collection = list;

        foreach (string, name, collection)
            Console::WriteLine("Name: {0}", name);
        Console::WriteLine();

        Console::WriteLine("First: {0}", collection->First());
        Console::WriteLine("Last: {0}", collection->Last());
        Console::WriteLine();

        //foreach (string, name, collection->Where([](string s) -> bool { return s.Length == 6; })
        //                                 ->Where([](string s) -> bool { return s.Contains('i'); }))
        //    Console::WriteLine("Test: {0}", name);
    }

    Console::Read();
}