#include <System/System.h>

#include "Windows.h"

using namespace System::IO;
using namespace System::Interface;
using namespace System::Runtime;
using namespace System::Graphics;
using namespace System::Devices;

namespace Theme
{
    Color24 MainColor = 0x425F67;

    Color24 CategoriesPanel = 0xEDF0F1;
    Color24 CategoriesBorder = 0xC4CFD2;

    Color24 DirectoriesPanel = 0xF7F8F8; // FIXME
    Color24 DirectoriesBorder = 0xCFD8Da; // FIXME
}

Window* window;
Image *icon, *directoryIcon, *fileIcon;
Label *computer, *network;
StackContainer *categories, *computerContainer, *networkContainer;
StackContainer *directoriesContainer, *directoriesMenu;
ScrollContainer *directoriesScroller, *filesScroller;
Button *newDirectoryButton, *parentDirectoryButton;

Grid *files;
Grid::Column *iconColumn, *nameColumn, *detailsColumn;

Directory* selectedDirectory = Directory::GetRootDirectory();
Directory* parentDirectory = selectedDirectory->Parent ? selectedDirectory->Parent : selectedDirectory;

void RefreshDirectories();
void RefreshFiles();

void Categories_PointerDown(void* origin, PointerEvent pointer)
{
    Button* button = (Button*)origin;
    FileSystem* fileSystem = (FileSystem*)button->Tag;

    foreach (Element*, element, computerContainer->Elements)
    {
        if (!element->Is<Button>())
            continue;

        Button* elementButton = (Button*)element;
        elementButton->Border = Outline(0, 1, 0, 0);
    }

    button->Border = Outline(1, 0, 1, 4);

    Serial::WriteLine("Selected \"{0:w}\"", fileSystem->Name);
}

void Directories_PointerUp(void* origin, PointerEvent pointer)
{
    Button* button = (Button*)origin;
    Directory* buttonDirectory = (Directory*)button->Tag;

    if (selectedDirectory->FullPath == buttonDirectory->FullPath)
        parentDirectory = selectedDirectory;
    else
        selectedDirectory = buttonDirectory;

    RefreshDirectories();
    RefreshFiles();
}
void ParentDirectory_PointerUp(void* origin, PointerEvent pointer)
{
    Directory* parent = parentDirectory->Parent;
    selectedDirectory = parentDirectory;

    if (parent)
    {
        parentDirectory = parent;
        RefreshDirectories();
    }

    RefreshFiles();
}
void NewDirectory_PointerUp(void* origin, PointerEvent pointer)
{
    Exception::NotImplemented();
}

void RefreshDirectories()
{
    directoriesContainer->Clear();

    foreach (Directory*, child, parentDirectory->Directories)
    {
        Button* button = new Button(child->Name);

        button->Size = Point(directoriesContainer->Size.X, 40);
        button->Dock = DockStyle::LeftRight;
        button->Alignment = Alignment::MiddleLeft;
        button->Padding = Outline(0, 0, 0, 12);
        button->Tag = child;
        button->Color = Theme::MainColor;
        button->OverColor = 0x10FFFFFF;
        button->DownColor = 0xE0000000;
        button->BorderColor = Theme::DirectoriesBorder;
        button->PointerUp += Directories_PointerUp;

        if (child->FullPath == selectedDirectory->FullPath)
        {
            button->BackColor = window->BackColor;
            button->Border = Outline(1, 0, 1, 0);
        }
        else
            button->Border = Outline(0, 1, 0, 0);

        directoriesContainer->Add(button);
    }
}
void RefreshFiles()
{
    files->Clear();

    foreach (Directory*, child, selectedDirectory->Directories)
    {
        Label* nameLabel = new Label(child->Name);
        nameLabel->Color = Theme::MainColor;

        Label* infoLabel = new Label("Directory");
        infoLabel->Color = Colors::Gray;

        files->AddRow(directoryIcon, nameLabel, infoLabel);
    }

    foreach (File*, child, selectedDirectory->Files)
    {
        Label* nameLabel = new Label(child->Name);
        nameLabel->Color = Theme::MainColor;

        Label* sizeLabel = new Label(String::Format("{0} B", (u32)child->Size));
        sizeLabel->Color = Colors::Gray;

        files->AddRow(fileIcon, nameLabel, sizeLabel);
    }
}

void Test_Files()
{
    Reference<FontFamily> fontFamily = FontFamily::GetDefaultFamily();

    // Window
    window = new Window("Files");
    window->Position = Point(420, 64);
    window->Size = Point(640, 400);
    window->BackColor = Colors::White;

    #pragma region Categories panel

    // Categories
    window->Add(categories = new StackContainer());
    categories->Size = Point(144, window->Size.Y);
    categories->Dock = DockStyle::LeftFull;
    categories->Orientation = Orientation::Vertical;
    categories->Padding = Outline(40, 0, 0, 0);
    categories->BackColor = Theme::CategoriesPanel;
    categories->BorderColor = Theme::CategoriesBorder;
    categories->Border = Outline(0, 1, 0, 0);

    // Computer
    categories->Add(computer = new Label("Computer"));
    computer->Size = Point(categories->Size.X - 1 - 12, 40);
    computer->Dock = DockStyle::LeftRight;
    computer->Margin = Outline(0, 0, 0, 12);
    computer->Alignment = Alignment::MiddleLeft;
    computer->Font = fontFamily->GetFont(12);
    computer->Color = Theme::MainColor;

    categories->Add(computerContainer = new StackContainer());
    computerContainer->Size = Point(categories->Size.X - 1, 0);
    computerContainer->Dock = DockStyle::LeftRight;
    computerContainer->Orientation = Orientation::Vertical;
    computerContainer->AutoSize = true;
    //computerContainer->BorderColor = Colors::LightRed;
    //computerContainer->Border = Outline(1);
    computerContainer->Padding = Outline(4);

    /*auto storageDevices = Device::GetAll<StorageDevice>();
    foreach (StorageDevice*, device, storageDevices)
    {
        foreach (FileSystem*, fileSystem, device->FileSystems)
        {
            if (!directory)
                directory = fileSystem->Root;

            Button* button = new Button(String::Format("{0:w}", fileSystem->Name));

            button->Size = Point(computerContainer->Size.X, 40);
            button->Dock = DockStyle::LeftRight;
            button->Tag = fileSystem;
            button->BackColor = 0xF8F9F9;
            button->BorderColor = 0xCFD8DA;
            button->Border = Outline(1, 0, 1, 4);
            button->PointerDown += Event<PointerEvent>::Callback(this, &Files::Categories_PointerDown);

            computerContainer->Add(button);
        }
    }*/

    // Network
    categories->Add(network = new Label("Network"));
    network->Size = Point(categories->Size.X - 1 - 12, 40);
    network->Dock = DockStyle::LeftRight;
    network->Margin = Outline(0, 0, 0, 12);
    network->Alignment = Alignment::MiddleLeft;
    network->Font = fontFamily->GetFont(12);
    network->Color = Theme::MainColor;

    categories->Add(networkContainer = new StackContainer());
    networkContainer->Size = Point(categories->Size.X - 1, 0);
    networkContainer->Dock = DockStyle::LeftRight;
    networkContainer->Orientation = Orientation::Vertical;
    networkContainer->AutoSize = true;
    //networkContainer->BorderColor = Colors::LightRed;
    //networkContainer->Border = Outline(1);
    networkContainer->Padding = Outline(4);

    #pragma endregion
    #pragma region Directories panel
    
    // Scroll
    window->Add(directoriesScroller = new ScrollContainer());
    directoriesScroller->Position = Point(categories->Size.X, 40);
    directoriesScroller->Size = Point(128, window->Size.Y - 40);
    directoriesScroller->Dock = DockStyle::LeftFull;
    directoriesScroller->BackColor = Theme::DirectoriesPanel;
    directoriesScroller->BorderColor = Theme::DirectoriesBorder;
    directoriesScroller->Border = Outline(0, 1, 0, 0);

    // Container
    directoriesScroller->Add(directoriesContainer = new StackContainer());
    directoriesContainer->Size = Point(directoriesScroller->Size.X, 40);
    directoriesContainer->Dock = DockStyle::TopFull;
    directoriesContainer->Orientation = Orientation::Vertical;
    directoriesContainer->AutoSize = true;
    //directoriesContainer->BorderColor = Colors::Green;
    //directoriesContainer->Border = Outline(1);

    // Menu
    window->Add(directoriesMenu = new StackContainer());
    directoriesMenu->Position = Point(categories->Size.X, 0);
    directoriesMenu->Size = Point(directoriesScroller->Size.X, 40);
    directoriesMenu->Orientation = Orientation::Horizontal;
    directoriesMenu->BackColor = Theme::DirectoriesPanel;
    directoriesMenu->BorderColor = Theme::DirectoriesBorder;
    directoriesMenu->Border = Outline(0, 1, 0, 0);

    directoriesMenu->Add(newDirectoryButton = new Button(Bitmaps::Icons::Plus));
    newDirectoryButton->Size = Point(40, 40);
    newDirectoryButton->Position = Point(0, 0);
    newDirectoryButton->PointerUp += NewDirectory_PointerUp;
    newDirectoryButton->Color = Theme::MainColor;
    newDirectoryButton->OverColor = 0x10FFFFFF;
    newDirectoryButton->DownColor = 0xE0000000;

    directoriesMenu->Add(parentDirectoryButton = new Button(Bitmaps::Icons::Up));
    parentDirectoryButton->Size = Point(40, 40);
    parentDirectoryButton->Position = Point(40, 0);
    parentDirectoryButton->PointerUp += ParentDirectory_PointerUp;
    parentDirectoryButton->Color = Theme::MainColor;
    parentDirectoryButton->OverColor = 0x10FFFFFF;
    parentDirectoryButton->DownColor = 0xE0000000;

    #pragma endregion
    
    // Icon
    window->Add(icon = new Image(Bitmap::Load("/Applications/Files/Icon.png")));
    icon->Color = Theme::MainColor;
    icon->BackColor = categories->BackColor;
    icon->Position = Point2(6, 4);

    #pragma region Files panel

    // Scroll
    window->Add(filesScroller = new ScrollContainer());
    filesScroller->Position = Point(directoriesScroller->Position.X + directoriesScroller->Size.X + 8, 48);
    filesScroller->Size = Point(window->Size.X - filesScroller->Position.X - 8, window->Size.Y - filesScroller->Position.Y - 8);
    filesScroller->Dock = DockStyle::Full;
    //filesScroller->BorderColor = Colors::Red;

    // Grid
    window->Add(files = new Grid());
    files->Position = Point(directoriesScroller->Position.X + directoriesScroller->Size.X + 8, 48);
    files->Size = Point(window->Size.X - files->Position.X - 8, window->Size.Y - files->Position.Y - 8);
    //files->AutoSize = true;
    files->Dock = DockStyle::Full;
    files->AlternateBackColor = 0xF8F8F8;
    files->ShowHeaders = false;
    //files->BorderColor = Colors::Green;

    // Prepare icons
    directoryIcon = new Image(Bitmap::Load("/Applications/Files/Directory.png"));
    directoryIcon->Color = Theme::MainColor;
    fileIcon = new Image(Bitmap::Load("/Applications/Files/File.png"));
    fileIcon->Color = Theme::MainColor;

    // Columns
    iconColumn = files->AddColumn("", 28, Alignment::MiddleCenter);
    nameColumn = files->AddColumn("Name", ColumnWidthType::Fill);
    detailsColumn = files->AddColumn("Details", 80, Alignment::MiddleRight);

    #pragma endregion

    // Refresh data
    RefreshDirectories();
    RefreshFiles();

    WindowsManager::Add(window);

    for (;;)
    {
        Timer::Sleep(10);

        Dispatcher* dispatcher = Dispatcher::GetCurrent();
        if (dispatcher)
            dispatcher->Flush();
    }
}