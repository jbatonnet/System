#ifndef _SYSTEM_CONTROL_H_
#define _SYSTEM_CONTROL_H_

#include <System/Common.h>
#include <System/Graphics/Surface.h>
#include <System/Graphics/Point.h>
#include <System/Interface/Element.h>

namespace System
{
    namespace Interface
    {
        class Control : public Element
        {
            friend class Container;

        protected:
            Graphics::Surface* surface;

        public:
            Control();
            Control(u16 width, u16 height);
            Control(Graphics::Point size);
            virtual ~Control() { }

            // Accessors
            _declspec(property(get = GetSurface)) Graphics::Surface* Surface;
            Graphics::Surface* GetSurface() const { return surface; }

            virtual void SetSize(Graphics::Point value) override;

            // Events
            Event<Graphics::Rectangle> Redrawn;

            // Control
            virtual void Redraw() = 0;
        };
    }
}

#endif