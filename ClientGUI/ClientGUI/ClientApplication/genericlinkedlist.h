#ifndef GENERICLINKEDLIST_H
#define GENERICLINKEDLIST_H


#include "genericnode.h"
#include <iostream>
#include "imgtable.h"
#include "keyvalue.h"

/**
 * Class use for storing any type of object
 * @tparam T
 */
template <class T>
class GenericLinkedList{
public:
    GenericLinkedList();
    void add(T);
    void remove(int);
    GenericNode<T>* get(int);
    GenericNode<T>* getHead();
    int* getLength();
    bool includes(T);
    void deleteEndNode();
    GenericNode<T>* getLast();
private:
    GenericNode<T>* header;
    GenericNode<T>* last;
    int length;
};


#endif // GENERICLINKEDLIST_H
