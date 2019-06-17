#include "genericnode.h"
#include "genericlinkedlist.h"
#include <iostream>

/**
 * Generic Node constructor
 * @tparam T
 * @param data
 */
template<class T>
GenericNode<T>::GenericNode(T data) {
    this->data = data;
    this->next = nullptr;
}

/**
 * Return a data on an existing node
 * @tparam T
 * @return T
 */
template<class T>
T GenericNode<T>::getData() {
    return this->data;
}

/**
 * Return a data on an existing node
 * @tparam T
 * @return T
 */
template<class T>
T* GenericNode<T>::getDataPtr() {
    T* ptr = &data;
    return ptr;
}

/**
 * Returns the node next to this one
 * @tparam T
 * @return GenericNode<T>*
 */
template<class T>
GenericNode<T>* GenericNode<T>::getNext() {
    return this->next;
}

/**
 * Sets a pointer to a newly created node with is going to be the next
 * @tparam T
 * @param next
 */
template<class T>
void GenericNode<T>::setNext(GenericNode<T> *next) {
    this->next = next;
}


template class GenericNode<std::string>;
template class GenericNode<int>;
template class GenericNode<ImgTable>;
template class GenericNode<KeyValue>;
template class GenericNode<GenericLinkedList<std::string>*>;
