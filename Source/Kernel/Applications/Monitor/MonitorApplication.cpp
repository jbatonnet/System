#include "MonitorApplication.h"

#include <Kernel/Kernel.h>

#include <Kernel/Memory/PMM.h>
#include <Kernel/Memory/Heap.h>

using namespace System::Interface;
using namespace System::Graphics;

void MonitorApplication_Main()
{
    MonitorApplication app;
    app.Start();

    for (;;)
        Timer::Sleep(1000);
}

Grid *grid;

void MonitorApplication::Start(string parameters)
{
    Window *window;
    TabContainer *container;
    Tab *debug, *processes, *usage, *devices;
    Image *image, *icon;

    Reference<FontFamily> fontFamily = FontFamily::Load("/System/Fonts/Open.font.raw"); //FontFamily::GetDefaultFamily();

    //Timer::Sleep(1000); // FIXME

    // Window
    window = new Window("Monitor");
    window->Position = Point(420, 64);
    window->Size = Point(720, 480);
    window->BackColor = 0xE4E9EB;

    // Icon
    //window->Add(icon = new Image(Bitmap::Slot[2]));
    //icon->Position = Point(10, 4);

    // Tabs
    window->Add(container = new TabContainer());
    container->Dock = DockStyle::Full;
    container->Size = window->Size;

    #pragma region Debug tab

    container->Add(debug = new Tab("Debug"));

    debug->Add(grid = new Grid());
    grid->Position = Point(16, 56);
    grid->Size = Point(debug->Size.X - 32, debug->Size.Y - 72);
    grid->Dock = DockStyle::Full;

    grid->AddColumn("Column 1");
    grid->AddColumn("Column 2");
    grid->AddRow("Value 1", "Value 2");
    grid->AddRow("Value 3", "Value 4");
    grid->AddRow("Value 5", "Value 6");
    grid->AddRow("Value 7", "Value 8");

    #pragma endregion
    #pragma region Usage tab
    
    Label *heapLabel, *heapUsedLabel, *heapTotalLabel, *heapMaxLabel,
          *kernelLabel, *kernelTicksLabel, *kernelTotalLabel, *kernelUsageLabel;
    Graph *kernelUsageGraph;
    Graph::Curve *kernelUsageCurve;

    container->Add(usage = new Tab("Usage"));
    
    usage->Add(heapLabel = new Label("Heap"));
    heapLabel->Position = Point(16, 16);

    usage->Add(heapUsedLabel = new Label("Used: 0 KB"));
    heapUsedLabel->Position = Point(40, 40);

    usage->Add(heapTotalLabel = new Label("Total: 0 KB"));
    heapTotalLabel->Position = Point(40, 64);

    usage->Add(heapMaxLabel = new Label("Maximum: 0 KB"));
    heapMaxLabel->Position = Point(40, 88);

    usage->Add(kernelLabel = new Label("Kernel"));
    kernelLabel->Position = Point(256, 16);

    usage->Add(kernelTicksLabel = new Label("Ticks: 0"));
    kernelTicksLabel->Position = Point(280, 40);

    usage->Add(kernelTotalLabel = new Label("Total: 0"));
    kernelTotalLabel->Position = Point(280, 64);

    usage->Add(kernelUsageLabel = new Label("Usage: 0%"));
    kernelUsageLabel->Position = Point(280, 88);

    usage->Add(kernelUsageGraph = new Graph());
    kernelUsageGraph->Position = Point(16, 128);
    kernelUsageGraph->Size = Point(384, 160);
    kernelUsageGraph->BackColor = Colors::White;
    kernelUsageGraph->SegmentSize = 12;
    kernelUsageGraph->GridSize = Point(40, 16);
    kernelUsageGraph->FillBelow = true;

    kernelUsageCurve = kernelUsageGraph->AddCurve(Colors::Green);

    #pragma endregion

    container->Add(processes = new Tab("Processes"));
    container->Add(devices = new Tab("Devices"));

    WindowsManager::Add(window);

    // Loop
    u64 lastTime = Timer::Ticks;
    for (u32 i = 0;; i++)
    {
        if (container->CurrentTab == usage)
        {
            /*{
                u32 free = Heap_FreeMemory((Heap*)HEAP_BASE);
                u32 total = Heap_TotalMemory((Heap*)HEAP_BASE);

                heapUsedLabel->Text = String::Format("Used: {0} KB", (total - free) / 1024);
                heapTotalLabel->Text = String::Format("Total: {0} KB", total / 1024);
                heapMaxLabel->Text = String::Format("Maximum: {0} KB", HEAP_SIZE / 1024);
            }*/

            /*{
                u32 ticks = Task::Kernel->totalTime;
                u32 total = Timer::Ticks - lastTime;

                kernelTicksLabel->Text = String::Format("Ticks: {0}", ticks);
                kernelTotalLabel->Text = String::Format("Total: {0}", total);

                if (ticks < total)
                {
                    s32 percentage = 100 - ticks * 100 / total;
                    kernelUsageLabel->Text = String::Format("Usage: {0}%", percentage);

                    if (i % 10 == 0)
                        kernelUsageCurve->AddValue(percentage);
                }
            }

            if (i % 10 == 0)
            {
                Task::Kernel->totalTime = 0;
                lastTime = Timer::Ticks;
            }*/
        }

        Timer::Sleep(100);
    }
}