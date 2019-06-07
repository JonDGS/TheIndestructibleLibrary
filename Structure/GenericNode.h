//
// Created by jondorito on 05/06/19.
//

#ifndef THEINDESTRUCTIBLELIBRARY_GENERICNODE_H
#define THEINDESTRUCTIBLELIBRARY_GENERICNODE_H

/**
 * GenericNode class for the GenericLinkedList
 * @tparam T
 */
template<class T>
class GenericNode {
public:
    GenericNode(T);
    T getData();
    GenericNode<T>* getNext();
    void setNext(GenericNode<T>*);


private:
    GenericNode* next;
    T data;
};

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


#endif //THEINDESTRUCTIBLELIBRARY_GENERICNODE_H
