#ifndef _KERNEL_MESSAGE_H_
#define _KERNEL_MESSAGE_H_

#include <System/Common.h>
#include <System/Interface/Window.h>
#include <System/Interface/Controls/Image.h>
#include <System/Interface/Controls/Label.h>
#include <System/Interface/Controls/Button.h>

namespace System
{
    namespace Interface
    {
        class Message : public Window
        {
        protected:
            string text;

            Image *icon;
            Label *label;
            Button *yesButton, *noButton;

        public:
            Message(const string& text);
            void Initialize();

            // Accessors
            _declspec(property(get = GetText, put = SetText)) string Text;
            string& GetText() { return title; }
            void SetText(const string& value) { title = value; }

            // Methods
            void Show();
            static void Show(const string& text);
        };
    }
}

#endif