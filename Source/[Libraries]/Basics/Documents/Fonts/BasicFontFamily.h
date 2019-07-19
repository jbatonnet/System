#ifndef _BASICFONTFAMILY_H_
#define _BASICFONTFAMILY_H_

#include <System/Graphics/Font.h>
#include <System/Graphics/FontFamily.h>
#include <System/Graphics/Surface.h>

struct FontIndex
{
    System::Graphics::FontAttribute Attribute;
    u8  Size;
    u32 Position;
};

class BasicFontFamily : public System::Graphics::FontFamily
{
    friend class BasicFont;

private:
    string name;
    System::Graphics::FontType type;

    System::IO::Stream* stream;
    FontIndex* index;
    u16 indexCount;

    BasicFontFamily() { }

public:
    virtual string GetName() const override { return name; }
    virtual System::Graphics::FontType GetType() const override { return type; }

    virtual Reference<System::Graphics::Font> GetFont(u8 size, System::Graphics::FontAttribute attributes = System::Graphics::FontAttribute::Regular) override;

    static BasicFontFamily* Load(System::IO::Stream* stream);
};

class BasicFont : public System::Graphics::Font
{
    friend class BasicFontFamily;

private:
    u8 size;
    System::Graphics::FontAttribute attributes;
    Reference<System::Graphics::FontFamily> family;

    u16 positions[257];
    u8 baseline;
    System::Graphics::Bitmap* cache;

    BasicFont() { }

public:
    virtual u8 GetSize() const override { return size; }
    virtual System::Graphics::FontAttribute GetAttributes() const override { return attributes; }
    virtual Reference<System::Graphics::FontFamily> GetFamily() const override { return family; }

    virtual void Draw(System::Graphics::Surface* surface, const string& text, u16 x, u16 y, Color32 color = 0x000000, System::Graphics::Alignment alignment = System::Graphics::Alignment::TopLeft) override;
    virtual Point2 Measure(const string& text) override;
    virtual Point2 Measure(char character) override;
};

#endif