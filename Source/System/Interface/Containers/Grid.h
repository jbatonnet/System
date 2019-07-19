#ifndef _SYSTEM_GRID_H_
#define _SYSTEM_GRID_H_

#include <System/Interface/Controls/Control.h>
#include <System/Interface/Containers/ScrollContainer.h>
#include <System/Structures/Collections/List.h>
#include <System/Interface/Controls/Label.h>
#include <System/Graphics/Point.h>

namespace System
{
    namespace Interface
    {
        enum class ColumnWidthType : u8
        {
            Absolute,
            Relative,
            Fill
        };

        class Grid : public Container
        {
        public:
            class Column;

            struct ColumnWidth
            {
                u32 Size;
                ColumnWidthType Type;

                ColumnWidth() : Size(1), Type(ColumnWidthType::Relative) { }
                ColumnWidth(u32 size) : Size(size), Type(ColumnWidthType::Absolute) { }
                ColumnWidth(u32 size, ColumnWidthType type) : Size(size), Type(type) { }
                ColumnWidth(ColumnWidthType type) : Size(1), Type(type) { }
            };

            class Cell : public Element
            {
                friend class Grid;

            private:
                Column* column;
                u32 row;
                Control* control;
                Graphics::Alignment alignment;

            protected:
                void Control_Redrawn(void* origin, Graphics::Rectangle rectangle);

            public:
                Cell(Column* column, u32 row);
                Cell(Column* column, u32 row, const string& text);
                Cell(Column* column, u32 row, Control* control);

                /// <summary>
                /// Returns this cell hosted control
                /// </summary>
                _declspec(property(get = GetControl, put = SetControl)) Control* Control;
                Interface::Control* GetControl()const { return control; }
                void SetControl(Interface::Control* value);

                /// <summary>
                /// Returns this cell hosted control alignment
                /// </summary>
                _declspec(property(get = GetAlignment, put = SetAlignment)) Graphics::Alignment Alignment;
                Graphics::Alignment GetAlignment() const { return alignment; }
                void SetAlignment(Graphics::Alignment value);

                void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle);
            };
            class Column
            {
                friend class Grid;

            private:
                Grid* grid;
                string title;
                List<Cell*> cells;
                ColumnWidth width;
                Graphics::Alignment alignment;

            public:
                Column(Grid* grid);
                Column(Grid* grid, const string& title);
                Column(Grid* grid, const string& title, ColumnWidth width);
                Column(Grid* grid, const string& title, Graphics::Alignment alignment);
                Column(Grid* grid, const string& title, ColumnWidth width, Graphics::Alignment alignment);

                /// <summary>
                /// Returns this column title
                /// </summary>
                _declspec(property(get = GetTitle, put = SetTitle)) string Title;
                string GetTitle() const { return title; }
                void SetTitle(const string& value) { title = value; }

                /// <summary>
                /// Returns this column width
                /// </summary>
                _declspec(property(get = GetWidth, put = SetWidth)) ColumnWidth Width;
                ColumnWidth GetWidth() const { return width; }
                void SetWidth(ColumnWidth value) { width = value; }

                Reference<Collection<Cell*>> GetCells() { return &cells; }
                _declspec(property(get = GetCells)) Reference<Collection<Cell*>> Cells;

                // Methods
                Cell* AddCell();
                Cell* AddCell(const string& title);
                Cell* AddCell(Cell* cell);
            };
            class Row
            {
                friend class Grid;

            private:
                List<Cell*> cells;

            public:
            };

            friend class Column;

        private:
            List<Column*> columns;
            List<u32> columnsOrder, rowsOrder;
            
            Reference<Graphics::Font> font;
            bool showHeaders;
            bool showIndices;
            u16 cellHeight;
            Color24 alternateBackColor;
            bool autoSize;

        public:
            Grid();

            _declspec(property(get = GetColumns)) List<Column*> Columns;
            List<Column*>& GetColumns() { return columns; }

            _declspec(property(get = GetShowHeader, put = SetShowHeaders)) bool ShowHeaders;
            bool GetShowHeaders() { return showHeaders; }
            bool SetShowHeaders(bool value) { showHeaders = value; return showHeaders; }

            _declspec(property(get = GetFont, put = SetFont)) Reference<Graphics::Font> Font;
            Reference<Graphics::Font> GetFont() { return font; }
            void SetFont(Reference<Graphics::Font> value) { font = value; }

            _declspec(property(get = GetAlternateBackColor, put = SetAlternateBackColor)) Color24 AlternateBackColor;
            Color24& GetAlternateBackColor() { return alternateBackColor; }
            Color24& SetAlternateBackColor(const Color24& value) { return alternateBackColor = value; }

            bool GetAutoSize() { return autoSize; }
            virtual void SetAutoSize(bool value) { if (autoSize == value) return; autoSize = value; }
            _declspec(property(get = GetAutoSize, put = SetAutoSize)) bool AutoSize;

            // Methods
            virtual void Redraw(Graphics::Surface* surface, Graphics::Rectangle rectangle) override;
            virtual void Clear() override;
            void UpdateSize();

            // Data
            Column* AddColumn();
            Column* AddColumn(Column* column);
            Column* AddColumn(const string& title);
            Column* AddColumn(const string& title, ColumnWidth width);
            Column* AddColumn(const string& title, Graphics::Alignment alignment);
            Column* AddColumn(const string& title, ColumnWidth width, Graphics::Alignment alignment);

            Row* AddRow();
            Row* AddRow(Row* row);
            Row* AddRow(Control* control1, Control* control2 = null, Control* control3 = null, Control* control4 = null, Control* control5 = null, Control* control6 = null, Control* control7 = null, Control* control8 = null);
            Row* AddRow(const string& value1, const string& value2 = string::Empty, const string& value3 = string::Empty, const string& value4 = string::Empty, const string& value5 = string::Empty, const string& value6 = string::Empty, const string& value7 = string::Empty, const string& value8 = string::Empty);

            //Column* Column(u32 index);
            //Row* Row(u32 index);
            //Cell* Cell(u32 column, u32 row);
        };
    }
}

#endif