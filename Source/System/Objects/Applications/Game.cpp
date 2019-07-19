#include <System/System.h>

using namespace System::Interface;
using namespace System::Graphics;
using namespace System::Devices;

void Game::Start(string parameters)
{
    // Timing
    u64 lastUpdateTime = 0, updateTime = 0;
    u64 lastDrawTime = 0, drawTime = 0;
    u64 lastTime = 0, time = 0;
    u8 currentSkip = 0;
    frameRate = 60;
    frameSkip = 0;
    vSync = true;

    // Window creation
    window = new Window("MyGame");
    window->Position = Point(100, 200);
    window->Size = Point(640, 480);
    window->BackColor = 0xE4E9EB;

    image = new Image(10, 10);
    image->Dock = DockStyle::Full;
    image->Position = Point(0, 40);
    image->Size = Point(window->Size.X, window->Size.Y - 40);

    window->Add(image);

    WindowsManager::Add(window);

    //void* videoAddress = (void*)0xE8000000;
    //u16 videoWidth = SCREEN_WIDTH;
    //u16 videoHeight = SCREEN_HEIGHT;

    //surface = image->Surface; //new Surface(videoAddress, videoWidth, videoHeight, 
    //image->Redraw();
    
    // Initialization
    //DisplayDevice* displayDevice = Device::Get<DisplayDevice>();
    Initialize();

    // Loading
    Load();

    // Main loop
    running = true;
    while (running)
    {
        lastUpdateTime = updateTime;
        updateTime = Timer::Time();
        //movers->Update(lastUpdateTime, updateTime);
        Update(lastUpdateTime, updateTime);

#if DEBUG
        static u16 updates[FRAMES] = { 0 };
        static u32 updateIndex = 0;

        updates[updateIndex] = updateTime - lastUpdateTime;
        ++updateIndex %= FRAMES;

        float updatesTotal = 0;
        for (int i = 0; i < FRAMES; i++)
            updatesTotal += updates[i];
        updatesTotal /= FRAMES;
        ups = 1000 / updatesTotal;
#endif

        drawTime = Timer::Time();
        //if (frameRate < 1 || drawTime - lastTime < 1000 / frameRate || ++currentSkip > frameSkip)
        {
            /*renderer->SetRenderTarget(null);
            if (autoDraw)
            {
                renderer->Clear(Color::Black);
                renderer->effect->Begin();
                renderer->effect->SetViewProjection(camera->View, camera->Projection);
                movers->Draw(renderer, lastDrawTime, drawTime);
            }*/
            Draw(lastDrawTime, drawTime);
            /*if (autoDraw)
            {
                renderer->effect->End();
            }*/

            //camera->Update(lastDrawTime, drawTime);

#if DEBUG
            static u16 draws[FRAMES] = { 0 };
            static u32 drawIndex = 0;

            draws[drawIndex] = drawTime - lastDrawTime;
            ++drawIndex %= FRAMES;

            float drawsTotal = 0;
            for (int i = 0; i < FRAMES; i++)
                drawsTotal += draws[i];
            drawsTotal /= FRAMES;
            dps = 1000 / drawsTotal;
#endif

            currentSkip = 0;
            lastDrawTime = drawTime;
        }
        
        /*if (vSync)
            displayDevice->VSync->Wait();
        else*/
        {
            time = Timer::Time();
            while (frameRate > 0 && time - lastTime < 1000 / frameRate)
            {
                Timer::Sleep(1);
                time = Timer::Time();
            }
            lastTime = time;
        }
    }

    // Unloading
    Unload();
}