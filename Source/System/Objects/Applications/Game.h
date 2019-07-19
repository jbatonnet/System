#ifndef _SYSTEM_GAME_H_
#define _SYSTEM_GAME_H_

#include <System/Common.h>
#include <System/Objects/Applications/Application.h>

namespace System
{
    namespace Interface
    {
        class Window;
        class Image;
    }
    namespace Graphics
    {
        class Surface;
    }
}

#define DEBUG 1
#define FRAMES 30

class Game : public Application
{
private:
    bool running;

protected:
    System::Interface::Window* window;
    //System::Graphics::Surface* surface;
    System::Interface::Image* image;

    u8 frameRate;
    u8 frameSkip;
    bool vSync;

#if DEBUG
    float ups, dps;
#endif

public:
    virtual void Initialize() = 0;
    virtual void Load() { };
    virtual void Update(u64 lastTime, u64 time) { };
    virtual void Draw(u64 lastTime, u64 time) { };
    virtual void Unload() { };
    
    void Start(string parameters = "");
};

#endif