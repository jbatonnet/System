#ifndef _SYSTEM_DICTIONARY_H_
#define _SYSTEM_DICTIONARY_H_

#include <System/Structures/Collections/List.h>

template<typename TKey, typename TValue> struct Pair
{
    TKey Key;
    TValue Value;

    Pair(TKey key, TValue value) : Key(key), Value(value) { }
    Pair(u32) { }
};

template<typename TKey, typename TValue> class Dictionary : public List<Pair<TKey, TValue>*>
{
public:
    Dictionary(u32 limit = 0) : List(limit) { }
    ~Dictionary() { }

    void Add(TKey key, TValue value)
    {
        List<Pair<TKey, TValue>*>::Add(new Pair<TKey, TValue>(key, value));
    }
    void Remove(TKey key)
    {
        // TODO
    }

    TValue& Get(const TKey& key)
    {
        //WriteLine("%s", key.characters);

        for (u32 i = 0; i < Count; i++)
        {
            //WriteLine("- %s => %s", (*this)[i].Key.characters, (*this)[i].Key == key.characters ? "true" : "false");
            if (At(i)->Key == key)
                return At(i)->Value;
        }

        Exception::Assert(false, "No such key in this directory");
    }
    /*Pair<TKey, TValue>* operator[](u32 index)
    {
        return List<Pair<TKey, TValue>*>::operator[](index);
    }*/
};

#endif