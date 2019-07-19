#include <Kernel/Interface/Message.h>
#include <System/Interface/WindowsManager.h>

using namespace System::Interface;
using namespace System::Graphics;

Message::Message(const string& text) : text(text), Window(string::Empty)
{
    size = Point(384, 160);
    position = Point(100, 100);// Point((SCREEN_WIDTH - size.X) / 2, (SCREEN_HEIGHT - size.Y) / 2);

    Add(label = new Label(text));
    label->Position = Point(16, 16);
    label->Size = Point(size.X - 32, size.Y - 72);

    Add(yesButton = new Button("Y")); // Bitmap::Slot[0]));
    yesButton->Size = Point(40, 40);
    yesButton->Position = Point(size.X - 40, size.Y - 40);
    yesButton->Dock = DockStyle::BottomRight;

    Add(noButton = new Button("N")); // Bitmap::Slot[0]));
    noButton->Size = Point(40, 40);
    noButton->Position = Point(size.X - 80, size.Y - 40);
    noButton->Dock = DockStyle::BottomRight;
}

void Message::Initialize()
{
    Window::Initialize();
}

void Message::Show()
{
    WindowsManager::Add(this);
}
void Message::Show(const string& text)
{
    //Serial::WriteLine("Message: \"{0}\"", text);

    Message* message = new Message(text);
    message->Show();

    delete message;
}