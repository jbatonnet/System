#ifndef _KERNEL_SHELLCONTROL_H_
#define _KERNEL_SHELLCONTROL_H_

#include <System/Interface/Controls/Control.h>
#include <System/Graphics/Font.h>

class ShellControl : public System::Interface::Control
{
private:
    void* address;
    System::Graphics::Font* font;

public:
    ShellControl(void* address);

    // Accessors
    _declspec(property(get = GetFont, put = SetFont)) System::Graphics::Font* Font;
    System::Graphics::Font* GetFont() { return font; }
    void SetFont(System::Graphics::Font* value) { font = value; }

    // Control
    void Initialize();
    void Redraw();
};

#endif