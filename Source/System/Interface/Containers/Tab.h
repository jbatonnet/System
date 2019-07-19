#ifndef _SYSTEM_TAB_H_
#define _SYSTEM_TAB_H_

#include <System/Interface/Containers/Container.h>

namespace System
{
    namespace Interface
    {
        class Tab : public Container
        {
        protected:
            string title;

        public:
            Tab(const string& title);

            // Accessors
            _declspec(property(get = GetTitle, put = SetTitle)) string Title;
            string& GetTitle() { return title; }
            void SetTitle(const string& value) { title = value; }
        };
    };
};

#endif