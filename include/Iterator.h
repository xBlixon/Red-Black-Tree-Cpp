#ifndef REDBLACKTREE_ITERATOR_H
#define REDBLACKTREE_ITERATOR_H
#include "Node.h"

template <typename T>
class Iterator {
private:
    Node<T> *_root;
    Node<T> *ptr;
    void moveNext();
    void movePrevious();
public:
    Iterator(Node<T> *pointer, Node<T> *root);
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    T& operator*();
    T* operator->();
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
};

#include "Iterator.tpp"
#endif //REDBLACKTREE_ITERATOR_H