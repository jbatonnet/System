#include <System/Interface/Controls/Menu.h>

using namespace System::Interface;

Menu::Item::Item(const string& text) : Button(text)
{
    dock = DockStyle::TopFull;
    size.Y = 48;
}

Menu::Menu()
{
}

void Menu::Add(Menu::Item* item)
{
    StackContainer::Add(item);
    item->Size.X = size.X;
}