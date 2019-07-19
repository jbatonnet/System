#ifndef _SYSTEM_DISPLAYDEVICE_H_
#define _SYSTEM_DISPLAYDEVICE_H_

#include <System/Devices/Device.h>
#include <System/Graphics/Surface.h>
#include <System/Runtime/Threading/Signal.h>

namespace System
{
    namespace Devices
    {
        struct DisplayMode
        {
            u16 Id;
            u16 Width;
            u16 Height;
            u8 Bpp;
        };

		class DisplayOverlay
		{
		public:
			virtual bool GetVisible() = 0;
			virtual void SetVisible(bool visible) = 0;
			_declspec(property(get = GetVisible, put = SetVisible)) bool Visible;

			virtual Point2 GetPosition() = 0;
			virtual void SetPosition(Point2 position) = 0;
			_declspec(property(get = GetPosition, put = SetPosition)) Point2 Position;

			virtual Graphics::Bitmap* GetBitmap() = 0;
			virtual void SetBitmap(Graphics::Bitmap* surface) = 0;
			_declspec(property(get = GetBitmap, put = SetBitmap)) Graphics::Bitmap* Bitmap;
		};

        class DisplayDevice : public Device
        {
        public:
			virtual Graphics::Surface* GetSurface() = 0;
			_declspec(property(get = GetSurface)) Graphics::Surface* Surface;

			virtual Runtime::Signal* GetVSync() = 0;
			_declspec(property(get = GetVSync)) Runtime::Signal* VSync;

			virtual DisplayOverlay* GetOverlay() = 0;
			_declspec(property(get = GetOverlay)) DisplayOverlay* Overlay;

            virtual DisplayMode* FindDisplayMode(u16 width, u16 height, u8 bpp = 32, bool exact = true) = 0;
			virtual DisplayMode* GetDisplayMode() = 0;
            virtual void SetDisplayMode(DisplayMode* displayMode) = 0;
			_declspec(property(get = GetDisplayMode, put = SetDisplayMode)) DisplayMode* DisplayMode;

			virtual void Update() = 0;
			virtual void Update(u16 x, u16 y, u16 width, u16 height) = 0;
        };
    }
}

#endif