#ifndef GENERICNODE_H
#define GENERICNODE_H

#include "imgtable.h"
#include "keyvalue.h"

/**
 * GenericNode class for the GenericLinkedList
 * @tparam T
 */
template<class T>
class GenericNode {
public:
    GenericNode(T);
    T getData();
    T* getDataPtr();
    GenericNode<T>* getNext();
    void setNext(GenericNode<T>*);


private:
    GenericNode* next;
    T data;
};


#endif // GENERICNODE_H
