#include <System/System.h>
#include <System/Interface/Controls/TextBox.h>

#define BUFFER_BLOCK_SIZE 256

using namespace System::Devices;
using namespace System::Graphics;
using namespace System::Interface;
using namespace System::Runtime;

TextBox::TextBox() : backColor(Colors::White), selectionColor(Colors::LightBlue), multiLine(true)
{
    font = FontFamily::GetDefaultFamily()->GetFont(10);
}

void TextBox::SetText(string value)
{
    if (value == buffer)
        return;
    
    u32 newSize = value.Length;
    if (!multiLine)
    {
        for (u32 i = 0; i < newSize; i++)
            if (value.Buffer[i] == '\r' || value.Buffer[i] == '\n')
            {
                newSize = i;
                break;
            }
    }

    TextChanged(this, GetText(), value.SubString(0, newSize));

    u32 newCapacity = newSize - newSize % BUFFER_BLOCK_SIZE + BUFFER_BLOCK_SIZE;

    // Reallocate buffer if needed
    if (newCapacity != capacity)
    {
        if (buffer != null)
            delete buffer;

        buffer = Memory::Allocate<character>(newCapacity);
        capacity = newCapacity;
    }

    // Store string in buffer
    Memory::Copy<character>(value.Buffer, buffer, newSize);
    length = newSize;
    
    Clear();
    Update();
    Redraw();
}
void TextBox::SetFont(Reference<System::Graphics::Font> value)
{
    if (font == value || !value.Valid)
        return;
    
    FontChanged(this, font, value);
    font = value;
    Redraw();
}

void TextBox::OnPointerScroll(void* origin, PointerScrollEvent pointerScrollEvent)
{
    view.Y = Maths::Clamp<s32>(view.Y + pointerScrollEvent.Delta * 3, 0, lines.Count - 2);
    Redraw();
}
void TextBox::OnPointerDown(void* origin, PointerEvent pointerEvent)
{
    pointerDown = true;

    if (!control)
        selections.Clear();
    currentSquareSelection = null; // FIXME: Memory leak

    if (AllowSquareSelection())
    {
        Point2 size = font->Measure('a');
        Point2 view = Point2(pointerPosition.X / size.X + this->view.X, pointerPosition.Y / size.Y + this->view.Y);

        currentSquareSelection = new TextSquareSelection();
        currentSquareSelection->Position = view;
        currentSquareSelection->Size = Point2::Zero;
    }
    else
    {
        u32 index = GetIndexAtPosition(pointerPosition);
        Point2 view = GetViewAtIndex(index);

        currentSelection = new TextSelection();
        currentSelection->Begin = currentSelection->End = index;
        currentSelection->LastColumn = view.X;

        selections.Add(currentSelection);
    }

    Redraw();
}
void TextBox::OnPointerUp(void* origin, PointerEvent pointerEvent)
{
    pointerDown = false;
    currentSelection = null;
    Redraw();
}
void TextBox::OnPointerMove(void* origin, PointerPositionEvent pointerPositionEvent)
{
    pointerPosition = Point2(pointerPositionEvent.X, pointerPositionEvent.Y);

    if (!pointerDown)
        return;
    if (!currentSelection && !currentSquareSelection)
        return;

    if (AllowSquareSelection() && !currentSquareSelection && currentSelection)
    {
        Point2 viewStart = GetViewAtIndex(currentSelection->Begin);

        currentSquareSelection = new TextSquareSelection();
        currentSquareSelection->Position = viewStart;
        currentSquareSelection->Size = Point2(view.X - viewStart.X, view.Y - viewStart.Y);

        selections.Clear();
        currentSelection = null; // FIXME: Memory leak
    }

    if (currentSquareSelection)
    {
        Point2 size = font->Measure('a');
        Point2 view = Point2(pointerPosition.X / size.X + this->view.X, pointerPosition.Y / size.Y + this->view.Y);

        view.Y = Maths::Clamp<s32>(view.Y, 0, lines.Count - 2);

        currentSquareSelection->Size = Point2(view.X - currentSquareSelection->Position.X, view.Y - currentSquareSelection->Position.Y);
    }
    else if (currentSelection)
    {
        u32 index = GetIndexAtPosition(pointerPosition);
        Point2 view = GetViewAtIndex(index);

        if (currentSelection->End == index)
            return;

        currentSelection->End = index;
        currentSelection->LastColumn = view.X;
    }

    Redraw();
}
void TextBox::OnButtonDown(void* origin, ButtonEvent buttonEvent)
{
    bool shouldRedraw = false;

    if (control)
    {
        switch (buttonEvent.Button)
        {
            case Buttons::C: // TODO: Copy
                Debugger::Break();
                break;

            case Buttons::V: // TODO: Paste
                Debugger::Break();
                break;
        }

        return;
    }
    else
    {
        switch (buttonEvent.Button)
        {
            case Buttons::Left:
            case Buttons::Right:
            case Buttons::Up:
            case Buttons::Down:
            case Buttons::PageUp:
            case Buttons::PageDown:
            case Buttons::Origin:
            case Buttons::End:
            {
                if (!currentSquareSelection && !selections.Count)
                    break;

                // If alt is pressed, turn selections into a square one
                if (!currentSquareSelection && AllowSquareSelection())
                {
                    TextSelection* selection = selections.Last();

                    for (u32 i = 0; i < selections.Count - 1; i++)
                        delete selections[i];

                    Point2 selectionBegin = GetViewAtIndex(selection->Begin);
                    Point2 selectionEnd = GetViewAtIndex(selection->End);

                    currentSquareSelection = new TextSquareSelection();
                    currentSquareSelection->Position = selectionBegin;
                    currentSquareSelection->Size = Point2(selectionEnd.X - selectionBegin.X + (buttonEvent.Button == Buttons::Left ? -1 : 1), selectionEnd.Y - selectionBegin.Y);
                    currentSquareSelection->Size.X = Maths::Max(currentSquareSelection->Size.X, -selectionBegin.X);

                    selections.Clear();
                    if (currentSelection != selection)
                        currentSelection = null;
                }

                // If shift is not pressed, we keep only one selection
                if (!shift)
                {
                    // Keep the last one
                    if (!currentSquareSelection)
                    {
                        /*TextSelection* selection = selections.Last();

                        for (u32 i = 0; i < selections.Count - 1; i++)
                            delete selections[i];

                        selections.Clear();
                        if (currentSelection != selection)
                            currentSelection = null;

                        selections.Add(selection);*/
                    }

                    // Or turn the square one into a classical one
                    else
                    {
                        u32 selectionBegin = GetIndexAtView(currentSquareSelection->Position);
                        u32 selectionEnd = GetIndexAtView(currentSquareSelection->Position + currentSquareSelection->Size);

                        delete currentSquareSelection;

                        TextSelection* selection = new TextSelection();
                        selection->Begin = selectionBegin;
                        selection->End = selectionEnd;

                        selections.Add(selection);
                        currentSquareSelection = null;
                    }
                }

                // Extend the square seletion, if any
                if (currentSquareSelection)
                {
                    Point2 characterSize = font->Measure('a');

                    switch (buttonEvent.Button)
                    {
                        case Buttons::Left: currentSquareSelection->Size.X--; break;
                        case Buttons::Right: currentSquareSelection->Size.X++; break;
                        case Buttons::Up: currentSquareSelection->Size.Y--; break;
                        case Buttons::Down: currentSquareSelection->Size.Y++; break;
                        //case Buttons::PageUp: currentSquareSelection->Size.Y -= size.Y / characterSize.Y; break;
                        //case Buttons::PageDown: currentSquareSelection->Size.Y += size.Y / characterSize.Y; break;
                        case Buttons::Origin:
                        {
                            u32 index = GetIndexAtView(Point2(0, currentSquareSelection->Position.Y + currentSquareSelection->Size.Y));
                            u32 column = 0;

                            if (currentSquareSelection->Position.X + currentSquareSelection->Size.X == 0)
                                while (index + column < length && (buffer[index + column] == ' ' || buffer[index + column] == '\t'))
                                    column++;

                            currentSquareSelection->Size.X = column - currentSquareSelection->Position.X;
                            break;
                        }
                        case Buttons::End:
                        {
                            u32 index = GetIndexAtView(Point2(0, currentSquareSelection->Position.Y + currentSquareSelection->Size.Y));
                            u32 column = 0;

                            while (index + column < length && buffer[index + column] != '\r' && buffer[index + column] != '\n')
                                column++;

                            currentSquareSelection->Size.X = column - currentSquareSelection->Position.X;
                            break;
                        }
                    }

                    currentSquareSelection->Size.X = Maths::Max(currentSquareSelection->Size.X, -currentSquareSelection->Position.X);
                    currentSquareSelection->Size.Y = Maths::Clamp<s32>(currentSquareSelection->Size.Y , -currentSquareSelection->Position.Y, lines.Count - currentSquareSelection->Position.Y - 2);
                }

                // Else, updates other selections
                else
                {
                    u32 selectionCount = selections.Count;

                    for (u32 i = 0; i < selectionCount; i++)
                    {
                        TextSelection* selection = selections[i];
                        u32 selectionLength = selection->Length();

                        Point2 view = GetViewAtIndex(selection->End);
                        bool canMove = !selectionLength || shift;
                        bool saveLastColumn = false;

                        if (buffer[selection->End] != '\r' && buffer[selection->End] != '\n')
                            selection->LastColumn = view.X;

                        switch (buttonEvent.Button)
                        {
                            case Buttons::Left:
                            {
                                if (selectionLength && !shift)
                                    selection->End = selection->First();
                                else if ((selectionCount == 1 || view.X > 0) && canMove)
                                    selection->End--;

                                saveLastColumn = true;
                                break;
                            }
                            case Buttons::Right:
                            {
                                if (selectionLength && !shift)
                                    selection->End = selection->Last();
                                else if ((selectionCount == 1 || (buffer[selection->End] != '\r' && buffer[selection->End] != '\n')) && canMove)
                                    selection->End++;

                                saveLastColumn = true;
                                break;
                            }
                            case Buttons::Up:
                            {
                                if (shift)
                                {
                                    if (view.Y > 0)
                                        selection->End = GetIndexAtView(Point2(selection->LastColumn, view.Y - 1));
                                }
                                else
                                {
                                    Point2 firstView = GetViewAtIndex(selection->End);//First());
                                    selection->End = GetIndexAtView(Point2(selection->LastColumn, firstView.Y - (firstView.Y > 0 ? 1 : 0)));
                                }

                                break;
                            }
                            case Buttons::Down:
                            {
                                if (shift)
                                {
                                    if (view.Y < lines.Count - 2)
                                        selection->End = GetIndexAtView(Point2(selection->LastColumn, view.Y + 1));
                                }
                                else
                                {
                                    Point2 firstView = GetViewAtIndex(selection->End);//Last());
                                    selection->End = GetIndexAtView(Point2(selection->LastColumn, firstView.Y + (firstView.Y < lines.Count - 2 ? 1 : 0)));
                                }

                                break;
                            }
                            //case Buttons::PageUp: break;
                            //case Buttons::PageDown: break;
                            case Buttons::Origin:
                            {
                                u32 index = selection->End - view.X;

                                if (view.X == 0)
                                    while (index < length && (buffer[index] == ' ' || buffer[index] == '\t'))
                                        index++;

                                selection->End = index;
                                break;
                            }
                            case Buttons::End:
                            {
                                u32 index = selection->End - view.X;

                                while (index < length && (buffer[index] != '\r' || buffer[index] == '\n'))
                                    index++;

                                selection->End = index;
                                break;
                            }
                        }

                        selection->Begin = Maths::Clamp<s32>(selection->Begin, 0, length);
                        selection->End = Maths::Clamp<s32>(selection->End, 0, length);

                        if (buffer[selection->End - 1] == '\r' && buffer[selection->End] == '\n')
                            selection->End += buttonEvent.Button == Buttons::Left ? -1 : 1;

                        if (saveLastColumn)
                        {
                            view = GetViewAtIndex(selection->End);
                            selection->LastColumn = view.X;
                        }

                        if (!shift)
                            selection->Begin = selection->End;
                    }
                }

                shouldRedraw = true;
                break;
            }
            
            case Buttons::Backspace:
            case Buttons::Delete:
            {
                string oldText(buffer, length, true);

                // Empty each selection
                for (u32 i = 0; i < selections.Count; i++)
                {
                    TextSelection* selection = selections[i];
                    if (selection->Begin == selection->End)
                    {
                        if (buttonEvent.Button == Buttons::Backspace && selection->Begin > 0)
                            selection->Begin--;
                        else if (buttonEvent.Button == Buttons::Delete && selection->End < length)
                            selection->End++;

                        if (buffer[selection->Begin - 1] == '\r' && buffer[selection->Begin] == '\n')
                            selection->Begin--;
                        if (buffer[selection->End - 1] == '\r' && buffer[selection->End] == '\n')
                            selection->End++;
                    }

                    u32 selectionLength = selection->Length();
                    if (!selectionLength)
                        continue;

                    // Update other selections
                    for (u32 j = 0; j < selections.Count; j++)
                    {
                        TextSelection* otherSelection = selections[j];
                        if (otherSelection == selection)
                            continue;
                        if (otherSelection->First() < selection->Last())
                            continue;

                        otherSelection->Begin -= selectionLength;
                        otherSelection->End -= selectionLength;
                    }

                    // Update current buffer
                    u32 newLength = length - selectionLength;
                    Memory::Copy(buffer + selection->Last(), buffer + selection->First(), length - selection->Last());

                    length = newLength;
                    selection->End = selection->Begin;

                    Update();
                }

                TextChanged(this, oldText, string(buffer, length, true));

                shouldRedraw = true;
                break;
            }

            case Buttons::Enter:
            {
                if (!multiLine)
                    break;

                string oldText(buffer, length, true);
                Insert("\r\n", 2);
                TextChanged(this, oldText, string(buffer, length, true));
                break;
            }
            case Buttons::Tab:
            {
                string oldText(buffer, length, true);
                Insert("\t", 0);
                TextChanged(this, oldText, string(buffer, length, true));
                break;
            }

            case Buttons::Escape:
            {
                currentSelection = null;
                selections.Clear();

                shouldRedraw = true;
                break;
            }
        }
    }
    
    if (buttonEvent.Character)
    {
        string oldText(buffer, length, true);
        Insert(&buttonEvent.Character, 1);
        TextChanged(this, oldText, string(buffer, length, true));
    }

    shift |= buttonEvent.Button == Buttons::Shift;
    control |= buttonEvent.Button == Buttons::Control;
    alt |= buttonEvent.Button == Buttons::Alt;

    if (shouldRedraw)
        Redraw();
}
void TextBox::OnButtonUp(void* origin, ButtonEvent buttonEvent)
{
    shift &= buttonEvent.Button != Buttons::Shift;
    control &= buttonEvent.Button != Buttons::Control;
    alt &= buttonEvent.Button != Buttons::Alt;
}

void TextBox::Clear()
{
    view = Point2::Zero;

    selections.Clear();
    currentSelection = null;

    blocks.Clear();
}
void TextBox::Update()
{
    // Find lines in buffer
    lines.Clear();
    lines.Add(0);

    for (u32 i = 0; i < length; i++)
    {
        if (buffer[i] != '\r' && buffer[i] != '\n')
            continue;

        while (i < length && buffer[i] != '\n')
            i++;
        if (i == length)
            break;

        lines.Add(i + 1);
    }

    lines.Add(length);
}

/*void TextBox::Initialize()
{
    Exception::Assert(font, "A font must be specified");

    surface = new System::Graphics::Surface(size.X, size.Y);

    Redraw();
}*/
void TextBox::Redraw()
{
    if (!font.Valid)
        return;

    surface->Clear(backColor);
    u32 yOffset = 2;

    if (lines.Count > 0)
    {
        u32 viewOffset = lines[view.Y];

        //TextBlock* currentBlock = blocks.First();
        //while (currentBlock->Last() < viewOffset)
        //    currentBlock = currentBlock->Next;

        s32 y = 0;
        for (u32 i = view.Y; i < lines.Count - 1; i++)
        {
            u32 lineBegin = lines[i];
            u32 lineEnd = lines[i + 1];

            u32 lineHeight = font->Measure(buffer[lineBegin]).Y;

            for (u32 j = 0; j < selections.Count; j++)
            {
                TextSelection* selection = selections[j];

                if (!selection->Empty())
                {
                    if (selection->First() >= lineBegin && selection->First() < lineEnd)
                    {
                        Point2 size1 = font->Measure(string(buffer + lineBegin, selection->First() - lineBegin));
                        Point2 size2 = font->Measure(string(buffer + selection->First(), Maths::Min(selection->Last(), lineEnd) - selection->First()));
                        surface->FillRectangle(size1.X, Maths::Max<s32>(0, y - yOffset), Maths::Max(size2.X, 3), size2.Y, selectionColor); // Colors::LightGreen);
                    }
                    else if (selection->First() <= lineBegin && selection->Last() >= lineEnd)
                    {
                        Point2 size = font->Measure(string(buffer + lineBegin, lineEnd - lineBegin));
                        surface->FillRectangle(0, Maths::Max<s32>(0, y - yOffset), Maths::Max(size.X, 3), size.Y, selectionColor); // Colors::LightBlue);
                    }
                    else if (selection->First() <= lineBegin && selection->Last() > lineBegin && selection->Last() < lineEnd)
                    {
                        Point2 size = font->Measure(string(buffer + lineBegin, selection->Last() - lineBegin));
                        surface->FillRectangle(0, Maths::Max<s32>(0, y - yOffset), size.X, size.Y, selectionColor); // Colors::LightRed);
                    }
                }

                if (selection->End >= lineBegin && (selection->End < lineEnd || (selection->End == lineEnd && lineEnd == length)))
                {
                    Point2 size = font->Measure(string(buffer + lineBegin, selection->End - lineBegin));
                    surface->FillRectangle(size.X, Maths::Max<s32>(0, y - yOffset), 1, size.Y, Colors::Black);
                }
            }

            if (currentSquareSelection && i >= currentSquareSelection->First().Y && i <= currentSquareSelection->Last().Y)
            {
                Point2 size = font->Measure('a');
                surface->FillRectangle(size.X * currentSquareSelection->First().X, Maths::Max<s32>(0, y - yOffset), Maths::Max(size.X * Maths::Abs(currentSquareSelection->Size.X), 2), size.Y, selectionColor);

                if (i == (currentSquareSelection->Position.Y + currentSquareSelection->Size.Y))
                    surface->FillRectangle((currentSquareSelection->Position.X + currentSquareSelection->Size.X) * size.X, Maths::Max<s32>(0, y - yOffset), 1, size.Y, Colors::Black);
            }

            surface->DrawText(string(buffer + lineBegin, lineEnd - (buffer[lineEnd - 2] == '\r' ? 1 : 0) - lineBegin), font, 0, y);

            y += lineHeight;
            if (y > size.Y)
                break;
        }
    }

    // Debug
    for (u32 i = 0; i < selections.Count; i++)
    {
        TextSelection* selection = selections[i];
        surface->DrawText(String::Format("#{0}: {1}-{2}", i, selection->Begin, selection->End), font, size.X - 4, 4 + 16 * i, Colors::Green, Alignment::TopRight);
    }

    Redrawn(this, Rectangle(Point::Zero, size));
}

void TextBox::Insert(character* text, u32 textLength)
{
    char buffer[256] = { ' ' };

    bool tabify = *text == '\t';
    if (tabify)
        text = "    ";

    if (selections.Count == 0 && !currentSquareSelection)
        return;

    if (currentSquareSelection)
    {
        Point2 selectionFirst = currentSquareSelection->First();
        u32 selectionHeight = Maths::Abs(currentSquareSelection->Size.Y);
        u32 selectionWidth = Maths::Abs(currentSquareSelection->Size.X);

        if (tabify)
            textLength = 4 - selectionFirst.X % 4;

        for (u32 i = 0; i <= selectionHeight; i++)
        {
            u32 lineBegin = lines[selectionFirst.Y + i];
            u32 lineEnd = lines[selectionFirst.Y + i + 1];

            while (lineEnd > 0 && this->buffer[lineEnd - 1] == '\r' || this->buffer[lineEnd - 1] == '\n')
                lineEnd--;

            u32 padding = lineBegin + selectionFirst.X > lineEnd ? selectionFirst.X - lineEnd : 0;
            u32 selectionStart = lineBegin + selectionFirst.X - padding;
            
            // Generate padding
            u32 j = 0;
            for (; j < padding; j++)
                buffer[j] = ' ';
            for (; j < padding + textLength; j++)
                buffer[j] = text[j - padding];

            Replace(selectionStart - padding, selectionWidth, buffer, padding + textLength);
            Update();
        }

        currentSquareSelection->Position.X = selectionFirst.X + textLength;
        currentSquareSelection->Size.X = 0;
    }

    for (u32 i = 0; i < selections.Count; i++)
    {
        TextSelection* selection = selections[i];
        u32 selectionLength = selection->Length();

        if (tabify)
        {
            Point2 view = GetViewAtIndex(selection->First());
            textLength = 4 - view.X % 4;
        }

        // Update other selections
        for (u32 j = 0; j < selections.Count; j++)
        {
            TextSelection* otherSelection = selections[j];
            if (otherSelection == selection)
                continue;
            if (otherSelection->First() < selection->Last())
                continue;

            otherSelection->Begin += textLength - selectionLength;
            otherSelection->End += textLength - selectionLength;
        }

        Replace(selection->First(), selectionLength, text, textLength);

        selection->Begin += textLength;
        selection->End = selection->Begin;
    }

    Update();
    Redraw();
}
/*void TextBox::Remove()
{
}*/
void TextBox::Replace(u32 position, u32 selectionLength, character* text, u32 textLength)
{
    u32 newLength = length - selectionLength + textLength;
    if (newLength > capacity)
    {
        u32 newCapacity = newLength - newLength % BUFFER_BLOCK_SIZE + BUFFER_BLOCK_SIZE;

        character* newBuffer = Memory::Allocate<character>(newCapacity);
        Memory::Copy(buffer, newBuffer, position);
        Memory::Copy(text, newBuffer + position, textLength);
        Memory::Copy(buffer + position + selectionLength, newBuffer + position + textLength, length - (position + selectionLength));

        Memory::Free(buffer);

        buffer = newBuffer;
        capacity = newCapacity;
    }
    else
    {
        if (newLength > length)
        {
            for (u32 j = 0; j < newLength - (position + selectionLength); j++)
                buffer[newLength - 1 - j] = buffer[newLength - 1 - j - textLength];
        }
        else
            Memory::Copy(buffer + (position + selectionLength), buffer + position + textLength, length - (position + selectionLength));

        Memory::Copy(text, buffer + position, textLength);
    }

    length = newLength;
}

u32 TextBox::GetIndexAtPosition(Point2 position)
{
    if (!font.Valid)
        return 0;
    if (lines.Count == 0)
        return 0;

    u32 y = 0;

    // Find the line
    for (u32 i = view.Y; i < lines.Count - 1; i++)
    {
        u32 offset = lines[i];
        u32 nextOffset = lines[i + 1];

        u32 lineHeight = font->Measure(buffer[offset]).Y;

        if (pointerPosition.Y >= y && pointerPosition.Y < y + lineHeight)
        {
            u32 x = 0;

            // Find the character
            for (u32 j = offset; j < nextOffset; j++)
            {
                Point2 size = font->Measure(buffer[j]);

                if (pointerPosition.X >= x && pointerPosition.X < x + size.X)
                    return j;

                x += size.X;
            }

            if (nextOffset == length)
                return length;

            return buffer[nextOffset - 2] == '\r' ? nextOffset - 2 : nextOffset - 1;
        }

        y += lineHeight;
    }

    return length;
}
u32 TextBox::GetIndexAtView(Point2 view)
{
    if (view.Y < 0)
        return 0;
    if (view.Y >= lines.Count - 1)
        return length;

    u32 lineOffset = lines[view.Y];
    u32 nextLineOffset = lines[view.Y + 1];

    return Maths::Min(lineOffset + view.X, nextLineOffset - (buffer[nextLineOffset - 2] == '\r' ? 2 : 1));
}
Point2 TextBox::GetViewAtIndex(u32 index)
{
    u32 row = 0;
    u32 column = 0;

    for (row = 0; row < lines.Count - 1; row++)
    {
        u32 lineOffset = lines[row];
        u32 nextLineOffset = lines[row + 1];

        if (index >= lineOffset && index < nextLineOffset)
        {
            column = index - lineOffset;
            break;
        }
    }

    if (row == lines.Count - 1)
        return Point2::Zero;

    return Point2(column, row);
}
bool TextBox::AllowSquareSelection()
{
    return alt && font->Family->Type == FontType::Monospace;
}