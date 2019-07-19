#ifndef _SYSTEM_BUTTON_H_
#define _SYSTEM_BUTTON_H_

#include <System/Interface/Controls/Control.h>
#include <System/Graphics/Bitmap.h>
#include <System/Graphics/Colors.h>
#include <System/Devices/Input/PointerDevice.h>

namespace System
{
    namespace Interface
    {
        enum class ButtonStyle : u8
        {
            None,
            Text,
            Image
        };

        enum class ButtonState : u8
        {
            Idle,
            Over,
            Down
        };

        class Button : public Control
        {
        protected:
            string text;
            Reference<Graphics::Bitmap> image;
            Reference<Graphics::Font> font;
            Color32 color, overColor, downColor, borderColor;
            Graphics::Outline border;
            ButtonStyle style;
            ButtonState state;
            Graphics::Alignment alignment;
            Graphics::Outline padding;

        public:
            Button(const string& text);
            Button(const Reference<Graphics::Bitmap>& bitmap);

            // Accessors
            ChangeEvent<Reference<Graphics::Bitmap>> ImageChanged;
            Reference<Graphics::Bitmap> GetImage() { return image; }
            void SetImage(Reference<Graphics::Bitmap> value) { if (image == value) return; Maths::Swap(image, value); Style = ButtonStyle::Image; ImageChanged(this, value, image); Redraw(); }
            _declspec(property(get = GetImage, put = SetImage)) Reference<Graphics::Bitmap> Image;

            ChangeEvent<string> TextChanged;
            string& GetText() { return text; }
            void SetText(string value) { if (text == value) return; Maths::Swap(text, value); Style = ButtonStyle::Text; TextChanged(this, value, text); Redraw(); }
            _declspec(property(get = GetText, put = SetText)) string Text;

            ChangeEvent<Reference<Graphics::Font>> FontChanged;
            Reference<Graphics::Font> GetFont() { return font; }
            void SetFont(Reference<Graphics::Font> value) { if (font == value) return; Maths::Swap(font, value); FontChanged(this, value, font); Redraw(); }
            _declspec(property(get = GetFont, put = SetFont)) Reference<Graphics::Font> Font;

            ChangeEvent<ButtonStyle> StyleChanged;
            ButtonStyle GetStyle() { return style; }
            void SetStyle(ButtonStyle value) { if (style == value) return; Maths::Swap(style, value); StyleChanged(this, value, style); Redraw(); }
            _declspec(property(get = GetStyle, put = SetStyle)) ButtonStyle Style;

            ChangeEvent<Graphics::Outline> BorderChanged;
            Graphics::Outline GetBorder() { return border; }
            void SetBorder(Graphics::Outline& value) { if (border == value) return; Maths::Swap(border, value); BorderChanged(this, value, border); Redraw(); }
            _declspec(property(get = GetBorder, put = SetBorder)) Graphics::Outline Border;

            Graphics::Alignment GetAlignment() const { return alignment; }
            void SetAlignment(Graphics::Alignment value) { if (alignment == value) return; alignment = value; Redraw(); }
            _declspec(property(get = GetAlignment, put = SetAlignment)) Graphics::Alignment Alignment;

            Graphics::Outline GetPadding() const { return padding; }
            void SetPadding(Graphics::Outline value) { if (padding == value) return; padding = value; Redraw(); }
            _declspec(property(get = GetPadding, put = SetPadding)) Graphics::Outline Padding;

            Color32& GetColor() { return color; }
            void SetColor(Color32 value) { if (color == value) return; color = value; Redraw(); }
            _declspec(property(get = GetColor, put = SetColor)) Color32 Color;

            Color32& GetBorderColor() { return borderColor; }
            void SetBorderColor(Color32 value) { if (borderColor == value) return; borderColor = value; Redraw(); }
            _declspec(property(get = GetBorderColor, put = SetBorderColor)) Color32 BorderColor;

            Color32 GetOverColor() { return overColor; }
            void SetOverColor(Color32 value) { if (overColor == value) return; overColor = value; Redraw(); }
            _declspec(property(get = GetOverColor, put = SetOverColor)) Color32 OverColor;

            Color32 GetDownColor() { return downColor; }
            void SetDownColor(Color32 value) { if (downColor == value) return; downColor = value; Redraw(); }
            _declspec(property(get = GetDownColor, put = SetDownColor)) Color32 DownColor;

            virtual void SetBackColor(Color32 value) override { if (backColor == value) return; Maths::Swap(backColor, value); BackColorChanged(this, value, backColor); Redraw(); }

            // Control
            virtual void Redraw() override;

        protected:
            virtual void OnPointerIn(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerOut(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerDown(void* origin, Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerUp(void* origin, Devices::PointerEvent pointerEvent) override;
        };
    }
}

#endif