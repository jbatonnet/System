#ifndef _SYSTEM_LABEL_H_
#define _SYSTEM_LABEL_H_

#include <System/Interface/Controls/Control.h>

namespace System
{
    namespace Graphics
    {
        class Font;
    }

    namespace Interface
    {
        class Label : public Control
        {
        private:
            Color32 color;
            string text;
            Reference<Graphics::Font> font;
            bool autoSize;
            Graphics::Alignment alignment;

        public:
            Label();
            Label(string text);

            // Accessors
            _declspec(property(get = GetColor, put = SetColor)) Color32 Color;
            Color32 GetColor() const { return color; }
            void SetColor(Color32 value) { if (color == value) return; color = value; Redraw(); }

            _declspec(property(get = GetText, put = SetText)) string Text;
            string GetText() const { return text; }
            void SetText(string value) { if (text == value) return; text = value; UpdateSize(); Redraw(); }

            _declspec(property(get = GetFont, put = SetFont)) Reference<Graphics::Font> Font;
            Reference<Graphics::Font> GetFont() const { return font; }
            void SetFont(Reference<Graphics::Font> value) { if (font == value) return; font = value; UpdateSize(); Redraw(); }

            _declspec(property(get = GetAutoSize, put = SetAutoSize)) bool AutoSize;
            bool GetAutoSize() const { return autoSize; }
            void SetAutoSize(bool value) { if (autoSize == value) return; autoSize = value;  UpdateSize(); Redraw(); }

            _declspec(property(get = GetAlignment, put = SetAlignment)) Graphics::Alignment Alignment;
            Graphics::Alignment GetAlignment() const { return alignment; }
            void SetAlignment(Graphics::Alignment value) { if (alignment == value) return; alignment = value; Redraw(); }

            virtual void SetBackColor(Color32 value) override;
            virtual void SetSize(Graphics::Point value) override;

            // Control
            virtual void Redraw() override;

        protected:
            void UpdateSize();
        };
    };
};

#endif