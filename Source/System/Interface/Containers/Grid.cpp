#include <System/Interface/Containers/Grid.h>

using namespace System::Interface;
using namespace System::Graphics;

Grid::Grid() : showHeaders(true), cellHeight(28), alternateBackColor(0xF6F8F8), autoSize(false)
{
    font = FontFamily::GetDefaultFamily()->GetFont(10);
}

void Grid::Redraw(Surface* surface, Rectangle rectangle)
{
    surface->FillRectangle(rectangle.Position, rectangle.Size, backColor);

    // Borders
    surface->FillRectangle(0, 0, size.X, border.Top, borderColor);
    surface->FillRectangle(size.X - border.Right, 0, border.Right, rectangle.Size.Y, borderColor);
    surface->FillRectangle(0, size.Y - border.Bottom, size.X, border.Bottom, borderColor);
    surface->FillRectangle(0, 0, border.Left, size.Y, borderColor);

    // Columns
    u16 columnSizes[16] = { 0 };
    u16 totalSize = 0;
    u16 totalWeights = 0;

    for (u32 i = 0; i < columns.Count; i++)
        if (columns[i]->Width.Type == ColumnWidthType::Absolute)
        {
            columnSizes[i] = columns[i]->Width.Size;
            totalSize += columnSizes[i];
        }
        else if (columns[i]->Width.Type == ColumnWidthType::Relative)
            totalWeights += columns[i]->Width.Size;

    for (u32 i = 0; i < columns.Count; i++)
        if (columns[i]->Width.Type == ColumnWidthType::Relative)
            columnSizes[i] = (size.X - totalSize) * columns[i]->Width.Size / totalWeights;
        else if (columns[i]->Width.Type == ColumnWidthType::Fill)
            columnSizes[i] = size.X - totalSize;

    // Cells
    u16 x = 0, y;
    for (u32 i = 0; i < columns.Count; i++)
    {
        Column* column = columns[i];

        if (showHeaders)
        {
            surface->FillRectangle(x, 0, columnSizes[i], cellHeight, 0xE4E9EB);
            surface->DrawText(column->title, font, x + 6, cellHeight / 2, Colors::Black, Alignment::MiddleLeft);
        }

        for (u32 j = 0; j < rowsOrder.Count; j++)
        {
            Cell* cell = column->cells[j];
            y = cellHeight * (j + showHeaders);

            if (y + cellHeight >= Size.Y)
                break;

            SubSurface subSurface(surface, x, y, columnSizes[i], cellHeight);
            cell->Redraw(&subSurface, Rectangle(0, 0, columnSizes[i], cellHeight));
        }

        x += columnSizes[i];
    }
}
void Grid::Clear()
{
    columnsOrder.Clear();
    rowsOrder.Clear();

    for (u32 i = 0; i < columns.Count; i++)
        columns[i]->cells.Clear();

    Refreshed(this, Rectangle(Position, Size));
}
void Grid::UpdateSize()
{
    if (!autoSize)
        return;

    // Compute columns width if there are no dynamic widths
    u32 width = 0;
    bool updateWidth = !Flag::Test(dock, DockStyle::LeftRight);

    for (u32 i = 0; i < columns.Count; i++)
    {
        Column* column = columns[i];

        if (column->Width.Type != ColumnWidthType::Absolute)
            updateWidth = false;
        if (!updateWidth)
            break;

        width += column->Width.Size;
    }

    // Compute global height
    u32 height = ((showHeaders ? 1 : 0) + rowsOrder.Count) * cellHeight;

    // Update size
    Size = Point(updateWidth ? width : size.X, height);
}

Grid::Column* Grid::AddColumn()
{
    Column* column = new Column(this);

    columns.Add(column);
    UpdateSize();

    return column;
}
Grid::Column* Grid::AddColumn(Column* column)
{
    columns.Add(column);
    UpdateSize();

    return column;
}
Grid::Column* Grid::AddColumn(const string& title)
{
    return AddColumn(title, ColumnWidth(), Alignment::MiddleLeft);
}
Grid::Column* Grid::AddColumn(const string& title, ColumnWidth width)
{
    return AddColumn(title, width, Alignment::MiddleLeft);
}
Grid::Column* Grid::AddColumn(const string& title, Alignment alignment)
{
    return AddColumn(title, ColumnWidth(), alignment);
}
Grid::Column* Grid::AddColumn(const string& title, ColumnWidth width, Alignment alignment)
{
    Column* column = new Column(this, title, width, alignment);

    columns.Add(column);
    UpdateSize();

    return column;
}

Grid::Row* Grid::AddRow()
{
    return null;
}
Grid::Row* Grid::AddRow(Row* row)
{
    return null;
}
Grid::Row* Grid::AddRow(Control* control1, Control* control2, Control* control3, Control* control4, Control* control5, Control* control6, Control* control7, Control* control8)
{
    Control* parameters[8] = { control1, control2, control3, control4, control5, control6, control7, control8 };

    u32 row = rowsOrder.Count;
    for (u32 i = 0; i < columns.Count; i++)
        columns[i]->AddCell(new Cell(columns[i], row, parameters[i]));
    rowsOrder.Add(row);

    UpdateSize();
    Refreshed(this, Rectangle(Position, Size));

    return null;
}
Grid::Row* Grid::AddRow(const string& value1, const string& value2, const string& value3, const string& value4, const string& value5, const string& value6, const string& value7, const string& value8)
{
    const string* parameters[8] = { &value1, &value2, &value3, &value4, &value5, &value6, &value7, &value8 };

    u32 row = rowsOrder.Count;
    for (u32 i = 0; i < columns.Count; i++)
        columns[i]->AddCell(new Cell(columns[i], row, *parameters[i]));
    rowsOrder.Add(row);

    UpdateSize();
    Refreshed(this, Rectangle(Position, Size));

    return null;
}

// Columns
Grid::Column::Column(Grid* grid) : grid(grid), title(string::Empty), alignment(Alignment::MiddleLeft)
{
}
Grid::Column::Column(Grid* grid, const string& title) : grid(grid), title(title), alignment(Alignment::MiddleLeft)
{
}
Grid::Column::Column(Grid* grid, const string& title, ColumnWidth width) : grid(grid), title(title), width(width), alignment(Alignment::MiddleLeft)
{
}
Grid::Column::Column(Grid* grid, const string& title, Alignment alignment) : grid(grid), title(title), alignment(alignment)
{
}
Grid::Column::Column(Grid* grid, const string& title, ColumnWidth width, Alignment alignment) : grid(grid), title(title), width(width), alignment(alignment)
{
}

Grid::Cell* Grid::Column::AddCell()
{
    return AddCell(new Cell(this, cells.Count));
}
Grid::Cell* Grid::Column::AddCell(const string& title)
{
    return AddCell(new Cell(this, cells.Count, title));
}
Grid::Cell* Grid::Column::AddCell(Grid::Cell* cell)
{
    u32 index = cells.Count;

    cell->BackColor = index % 2 == grid->showHeaders ? grid->AlternateBackColor : grid->BackColor;

    cells.Add(cell);
    return cell;
}

// Cells
Grid::Cell::Cell(Column* column, u32 row) : column(column), row(row), control(null), alignment(column->alignment)
{
}
Grid::Cell::Cell(Column* column, u32 row, const string& text) : column(column), row(row), alignment(column->alignment)
{
    Label* label = new Label(text);
    label->Size = Graphics::Point(96, column->grid->cellHeight);
    label->Dock = DockStyle::Full;
    label->Alignment = Graphics::Alignment::MiddleLeft;

    Control = label;
}
Grid::Cell::Cell(Column* column, u32 row, System::Interface::Control* control) : column(column), row(row), alignment(column->alignment)
{
    Control = control;
}

void Grid::Cell::SetControl(System::Interface::Control* value)
{
    if (control == value)
        return;

    control = value;
    control->Redrawn += Event<Rectangle>::Callback(this, &Grid::Cell::Control_Redrawn);
}
void Grid::Cell::Control_Redrawn(void* origin, Rectangle rectangle)
{
    Grid* grid = column->grid;

    if (control)
        control->Position = Point(6, (grid->cellHeight - control->Size.Y + 1) / 2);

    grid->Refreshed(this, Rectangle(grid->Position, grid->Size));
}
void Grid::Cell::Redraw(Surface* surface, Rectangle rectangle)
{
    if (control->BackColor.Alpha)
        surface->FillRectangle(rectangle.Position, rectangle.Size, backColor);

    Point2 size = rectangle.Size;
    u32 x = 0, y = 0;

    if (Flag::Test(alignment, Alignment::Center))     x = (size.X - control->Size.X) / 2;
    else if (Flag::Test(alignment, Alignment::Right)) x = size.X - control->Size.X;
    else if (Flag::Test(alignment, Alignment::Left));

    if (Flag::Test(alignment, Alignment::Middle) || Flag::Test(alignment, Alignment::Baseline)) y = (size.Y - control->Size.Y) / 2;
    else if (Flag::Test(alignment, Alignment::Bottom))                                          y = size.Y - control->Size.Y;
    else if (Flag::Test(alignment, Alignment::Top));

    surface->DrawBitmap(x, y, control->Surface, true);
}