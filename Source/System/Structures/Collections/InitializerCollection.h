#ifndef _SYSTEM_INITIALIZERCOLLECTION_H_
#define _SYSTEM_INITIALIZERCOLLECTION_H_

#include <System/Common.h>
#include <System/Structures/Collections/Collection.h>

namespace std
{
    template<typename T> class initializer_list : public Collection<T>
    {
        class InitializerCollectionIterator : public Iterator<T>
        {
        private:
            T* current;
            T* last;

        public:
            InitializerCollectionIterator(T* first, T *last) : current(first - 1), last(last) { }

            bool IsEnd()
            {
                return current == last;
            }
            T GetCurrent()
            {
                return *current;
            }
            bool Next()
            {
                if (current == last)
                    return false;

                current++;
                return true;
            }
        };

    private:
        T* first;
        T* last;

    public:
        initializer_list(const T* first, const T *last) : first(const_cast<T*>(first)), last(const_cast<T*>(last)) { }

        const T* begin() const
        {
            return first;
        }
        const T* end() const
        {
            return last;
        }

        virtual Reference<Iterator<T>> GetIterator() const override
        {
            return new InitializerCollectionIterator(first, last);
        }
    };
}

template<typename T>
using InitializerCollection = std::initializer_list<T>;

#endif