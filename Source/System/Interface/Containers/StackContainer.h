#ifndef _SYSTEM_STACKCONTAINER_H_
#define _SYSTEM_STACKCONTAINER_H_

#include <System/Graphics/Bitmap.h>
#include <System/Interface/Containers/Container.h>

namespace System
{
    namespace Interface
    {
        class StackContainer : public Container
        {
        private:
            Graphics::Orientation orientation;
            List<Element*> elements;
            bool autoSize;
            Graphics::Outline padding;

        public:
            StackContainer();

            // Accessors
            Graphics::Orientation GetOrientation() { return orientation; }
            virtual Graphics::Orientation SetOrientation(const Graphics::Orientation value) { if (orientation == value || (value != Graphics::Orientation::Horizontal && value != Graphics::Orientation::Vertical)) return value; orientation = value; Refresh(); return orientation; }
            _declspec(property(get = GetOrientation, put = SetOrientation)) Graphics::Orientation Orientation;

            bool GetAutoSize() { return autoSize; }
            virtual void SetAutoSize(bool value) { if (autoSize == value) return; autoSize = value; Refresh(); }
            _declspec(property(get = GetAutoSize, put = SetAutoSize)) bool AutoSize;

            Graphics::Outline GetPadding() const { return padding; }
            void SetPadding(Graphics::Outline value) { if (padding == value) return; padding = value; Refresh(); }
            _declspec(property(get = GetPadding, put = SetPadding)) Graphics::Outline Padding;

            Pointer<Collection<Element*>> GetElements() { return elements; }
            _declspec(property(get = GetElements)) Pointer<Collection<Element*>> Elements;

            // Methods
            virtual void Add(Container* container) override;
            virtual void Add(Control* control) override;
            virtual void Remove(Container* container) override;
            virtual void Remove(Control* control) override;
            virtual void Clear() override;

        protected:
            virtual void Refresh(Element* element = null);

            virtual void Element_SizeChanged(void* control, ChangeEventParameter<Graphics::Point> parameter);
            virtual void Element_PositionChanged(void* control, ChangeEventParameter<Graphics::Point> parameter);
            virtual void Element_VisibleChanged(void* control, ChangeEventParameter<bool> parameter);
            virtual void Element_MarginChanged(void* control, ChangeEventParameter<Graphics::Outline> parameter);

            void Containers_Changed(void* origin, ObservableList<Container*>::Change change);
            void Controls_Changed(void* origin, ObservableList<Control*>::Change change);
        };
    }
}

#endif