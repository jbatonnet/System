#include <System/System.h>
#include <System/Data/Database.h>

#include "DatabasesApplication.h"

using namespace System::Data;
using namespace System::Graphics; 
using namespace System::IO;
using namespace System::Interface;
using namespace System::Devices;

void DatabasesApplication_Main()
{
    Databases app;
    app.Start();

    for (;;)
        Timer::Sleep(1000);
}

Window* window;
Image* icon;
StackContainer* databases;
Grid* results;

Directory* directory = null;

void Databases::Start(string parameters)
{
    FontFamily* fontFamily = FontFamily::Load("/System/Fonts/Open.font.raw"); //FontFamily::GetDefaultFamily();

    // Window
    window = new Window("Database");
    window->Position = Point(420, 64);
    window->Size = Point(720, 480);
    //window->BackColor = 0xE4E9EB;

    // Icon
    /*window->Add(icon = new Image(Bitmap::Slot[3]));
    icon->Position = Point(10, 4);*/

    // Databases
    window->Add(databases = new StackContainer());
    databases->Size = Point(128, window->Size.Y);
    databases->Dock = DockStyle::LeftFull;
    databases->Orientation = Orientation::Vertical;
    databases->BackColor = 0xECEEF0;
    databases->BorderColor = 0xC5D0D3;
    databases->Border = Outline(0, 1, 0, 0);

    Database* database = Database::Default;
    auto result = database->QueryTable("SELECT name FROM sqlite_master WHERE type = 'table'");

    foreach (Reference<Record>, record, result)
    {
        string name = record->GetString(0);
        Button* button = new Button(name);

        button->Size = Point(databases->Size.X, 40);
        button->Dock = DockStyle::LeftRight;
        button->BackColor = 0xF8F9F9;
        button->BorderColor = 0xCFD8DA;
        button->Border = Outline(1, 0, 1, 4);
        //button->PointerDown += Databases::Databases_PointerDown;

        databases->Add(button);
    }

    // Results
    window->Add(results = new Grid());
    results->Position = Point(databases->Size.X + 8, 48);
    results->Size = Point(window->Size.X - results->Position.X - 8, window->Size.Y - results->Position.Y - 8);
    results->Dock = DockStyle::Full;
    results->BackColor = Colors::LightBlue;
    results->AddColumn("ID");
    results->AddColumn("Name");

    results->AddRow("a", "b");

    WindowsManager::Add(window);
}

void Databases_PointerDown(void* origin, PointerEvent pointer)
{
    Button* button = (Button*)origin;

    foreach (Element*, element, &databases->Elements)
    {
        Button* elementButton = (Button*)element;
        elementButton->Border = Outline(0, 1, 0, 0);
        elementButton->BackColor = 0xF8F9F9;
    }

    button->Border = Outline(1, 0, 1, 4);
    button->BackColor = 0xFFFFFF;

    string name = button->Text;

    Database* database = Database::Default;
    auto table = database->QueryTable("SELECT * FROM pci_classes");

    //foreach (Reference<Record>, record, *table)
    for (u32 i = 0; i < 10; i++)
    {
        results->AddRow("a", "b");
    }
}