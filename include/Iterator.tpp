#pragma once

template<typename T>
Iterator<T>::Iterator(Node<T> *pointer, Node<T> *root) : ptr(pointer), _root(root) {}

template<typename T>
void Iterator<T>::moveNext() {
    if (ptr->right) { // Go right and most left
        ptr = ptr->right;
        while (ptr->left) {
            ptr = ptr->left;
        }
    } else { // Go up until ptr becomes the parent of left child
        Node<T>* parent = ptr->parent;
        while (parent && ptr == parent->right) {
            ptr = parent;
            parent = parent->parent;
        }
        ptr = parent;
    }
}

template<typename T>
void Iterator<T>::movePrevious() {
    if (ptr == nullptr) {
        ptr = _root;
        while (ptr->right) {
            ptr = ptr->right;
        }
        return;
    }

    if (ptr->left) { // Next smaller element
        ptr = ptr->left;
        while (ptr->right) {
            ptr = ptr->right;
        }
    } else {
        Node<T>* p = ptr->parent; // Ptr becomes a parent whose child is right
        while (p != nullptr && ptr == p->left) {
            ptr = p;
            p = p->parent;
        }
        ptr = p;
    }
}

template<typename T>
Iterator<T> &Iterator<T>::operator++() {
    moveNext();
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator it = *this;
    ++(*this);
    return it;
}

template<typename T>
Iterator<T> &Iterator<T>::operator--() {
    movePrevious();
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator--(int) {
    Iterator it = *this;
    --(*this);
    return it;
}

template<typename T>
T &Iterator<T>::operator*() {
    return ptr->value;
}

template<typename T>
T *Iterator<T>::operator->() {
    return &(ptr->value);
}

template<typename T>
bool Iterator<T>::operator==(const Iterator &other) const {
    return ptr == other.ptr;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator &other) const {
    return ptr != other.ptr;
}

// template<typename T>
// Iterator<T>::
