#ifndef _SYSTEM_IMAGE_H_
#define _SYSTEM_IMAGE_H_

#include <System/Interface/Controls/Control.h>

namespace System
{
    namespace Interface
    {
        class Image : public Control
        {
        protected:
            Reference<Graphics::Bitmap> bitmap;
            Color32 color;

        public:
            Image(Reference<Graphics::Bitmap> bitmap);
            Image(u16 width, u16 height);

            // Accessors
            _declspec(property(get = GetColor, put = SetColor)) Color32 Color;
            Color32 GetColor() const { return color; }
            void SetColor(Color32 value) { if (color == value) return; color = value; Redraw(); }

            virtual void SetBackColor(Color32 value) override { if (backColor == value) return; Control::SetBackColor(value); Redraw(); }

            // Methods
            virtual void Redraw() override;
        };
    }
}

#endif