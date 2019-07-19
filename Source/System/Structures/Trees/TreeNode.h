#ifndef _SYSTEM_TREENODE_H_
#define _SYSTEM_TREENODE_H_

#include <System/Structures/Collections/Collection.h>

template<typename T> class TreeNode : public Collection<TreeNode<T>>
{
protected:
    T element;

public:
    TreeNode(const T& element);

    // Accessors
    T GetElement() const { return element; }
    void SetElement(const T& value) { element = value; }
    _declspec(property(get = GetElement, put = SetElement)) T Element;
};

#endif