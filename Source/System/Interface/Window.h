#ifndef _SYSTEM_WINDOW_H_
#define _SYSTEM_WINDOW_H_

#include <System/Common.h>
#include <System/Interface/Containers/Container.h>
#include <System/Interface/Containers/Mover.h>
#include <System/Interface/Containers/Tab.h>
#include <System/Interface/Controls/Button.h>

namespace System
{
    namespace Interface
    {
        enum class WindowState : u8
        {
            Normal,
            Maximized,
            Hidden,
            Docked
        };

        enum class WindowLayer : u8
        {
            Bottom,
            Normal,
            Top
        };

        class Window : public Container
        {
        private:
            Button *minimize, *close;
            Mover *mover;

            void Close_PointerUp(void* origin, Devices::PointerEvent e);

        protected:
            string title;
            WindowState state;
            WindowLayer layer;

        public:
            Graphics::Surface* cachedSurface;

            Window(const string& title, bool buttons = true, bool moveable = true);

            void Initialize();

            /// <summary>
            /// Gets or sets this window title
            /// </summary>
            _declspec(property(get = GetTitle, put = SetTitle)) string Title;
            string GetTitle() const { return title; }
            void SetTitle(const string& value) { title = value; }

            /// <summary>
            /// Gets or sets this window state
            /// </summary>
            _declspec(property(get = GetState, put = SetState)) WindowState State;
            WindowState GetState() const { return state; }
            void SetState(WindowState value) { WindowState old = state; if (state != value) { state = value; StateChanged(this, old); } }

            /// <summary>
            /// Gets or sets this window layer
            /// </summary>
            _declspec(property(get = GetLayer, put = SetLayer)) WindowLayer Layer;
            WindowLayer GetLayer() const { return layer; }
            void SetLayer(WindowLayer value) { WindowLayer old = layer; if (layer != value) { layer = value; LayerChanged(this, old); } }

            virtual void SetBackColor(Color32 value);

            // Events
            Event<WindowState> StateChanged;
            Event<WindowLayer> LayerChanged;
            Event<void*> Closed;
        };
    };
};

#endif