#ifndef _SYSTEM_TEXTBOX_H_
#define _SYSTEM_TEXTBOX_H_

#include <System/Graphics/Font.h>
#include <System/Interface/Controls/Control.h>

namespace System
{
    namespace Interface
    {
        enum class TextStyle : u8
        {
            Normal = 0x00,
            Bold = 0x01,
            Italic = 0x02,
            Strike = 0x04,
            Underline = 0x08
        };

        class TextBox : public Control
        {
            typedef char character;

        public:
            typedef u32 TextPoint;
            struct TextSpan
            {
                TextPoint Begin, End;

                TextPoint First() const { return Begin < End ? Begin : End; }
                TextPoint Last() const { return Begin > End ? Begin : End; }

                bool Empty() const { return Begin == End; }
                u32 Length() const { return Last() - First(); }
            };
            struct TextSelection : TextSpan
            {
                character** Buffer;
                u32 LastColumn;
            };
            struct TextBlock : TextSpan
            {
                Color32 Color;
                TextStyle Style;
                TextBlock *Previous, *Next;
            };
            struct TextSquareSelection
            {
                Point2 Position;
                Point2 Size;

                Point2 First() const { return Point2(Size.X < 0 ? Position.X + Size.X : Position.X, Size.Y < 0 ? Position.Y + Size.Y : Position.Y); }
                Point2 Last() const { return Point2(Size.X < 0 ? Position.X : Position.X + Size.X, Size.Y < 0 ? Position.Y : Position.Y + Size.Y); }
            };

        private:
            TextSelection* currentSelection;
            TextSquareSelection* currentSquareSelection;
            bool shift, control, alt;
            bool pointerDown;

            virtual void OnPointerScroll(void* origin, System::Devices::PointerScrollEvent pointerScrollEvent) override;
            virtual void OnPointerDown(void* origin, System::Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerUp(void* origin, System::Devices::PointerEvent pointerEvent) override;
            virtual void OnPointerMove(void* origin, System::Devices::PointerPositionEvent pointerEvent) override;

            virtual void OnButtonDown(void* origin, System::Devices::ButtonEvent buttonEvent) override;
            virtual void OnButtonUp(void* origin, System::Devices::ButtonEvent buttonEvent) override;

        protected:
            Reference<Graphics::Font> font;
            Color32 backColor;
            Color32 selectionColor;
            bool readOnly;
            bool multiLine;

            character* buffer;
            u32 length;
            u32 capacity;

            List<TextPoint> lines;
            List<TextSelection*> selections;
            List<TextBlock*> blocks;

            Point2 view;

            void Clear();
            void Update();

            Point2 pointerPosition;

            void Insert(character* text, u32 textLength);
            void Replace(u32 position, u32 selectionLength, character* text, u32 textLength);

            bool AllowSquareSelection();

        public:
            TextBox();

            /// <summary>
            /// Gets or sets this textbox text
            /// </summary>
            _declspec(property(get = GetText, put = SetText)) string Text;
            ChangeEvent<string> TextChanged;
            string GetText() const { return string(buffer, length); }
            void SetText(string value);

            /// <summary>
            /// Gets or sets this textbox font
            /// </summary>
            _declspec(property(get = GetFont, put = SetFont)) Reference<Graphics::Font> Font;
            ChangeEvent<Reference<Graphics::Font>> FontChanged;
            Reference<Graphics::Font> GetFont() const { return font; }
            void SetFont(Reference<Graphics::Font> value);

            /// <summary>
            /// Enabled or disables the edition of this textbox text
            /// </summary>
            _declspec(property(get = GetReadOnly, put = SetReadOnly)) bool ReadOnly;
            bool GetReadOnly() const { return readOnly; }
            void SetReadOnly(bool value) { if (readOnly == value) return; readOnly = value; }

            /// <summary>
            /// Enabled or disables the multilne edition of this textbox text
            /// </summary>
            _declspec(property(get = GetMultiLine, put = SetMultiLine)) bool MultiLine;
            bool GetMultiLine() const { return multiLine; }
            void SetMultiLine(bool value) { if (multiLine == value) return; multiLine = value; SetText(string(buffer, length)); }

            /// <summary>
            /// Gets or sets this textbox background color
            /// </summary>
            _declspec(property(get = GetBackColor, put = SetBackColor)) Color32 BackColor;
            Color32 GetBackColor() const { return backColor; }
            void SetBackColor(Color32 value) { if (backColor == value) return; backColor = value; Redraw(); }

            /// <summary>
            /// Gets or sets this textbox selection color
            /// </summary>
            _declspec(property(get = GetSelectionColor, put = SetSelectionColor)) Color32 SelectionColor;
            Color32 GetSelectionColor() const { return selectionColor; }
            void SetSelectionColor(Color32 value) { if (selectionColor == value) return; selectionColor = value; Redraw(); }

            /// <summary>
            /// Returns the current textbox selections
            /// </summary>
            _declspec(property(get = GetSelections)) List<TextSelection*> Selections;
            List<TextSelection*>& GetSelections() { return selections; }

            // Control
            virtual void Redraw() override;

            // Helpers
            u32 GetIndexAtPosition(Point2 position);
            u32 GetIndexAtView(Point2 view);
            Point2 GetViewAtIndex(u32 index);
        };
    }
}

#endif