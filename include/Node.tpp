#include <bits/locale_facets_nonio.h>

template<typename T>
Node<T>::Node(T value) : value(value) {}

template<typename T>
Node<T> *Node<T>::grandparent() {
    if (this->parent) {
        return this->parent->parent;
    }
    return nullptr;
}

template<typename T>
Node<T> *Node<T>::uncle() {
    Node<T> *grandparent = this->grandparent();
    if (grandparent) {
        if (grandparent->left == this->parent ) {
            return grandparent->right;
        } else {
            return grandparent->left;
        }
    }
    return nullptr;
}

template<typename T>
Color Node<T>::uncleColor() {
    if (this->uncle() == nullptr) {
        return Color::BLACK;
    }
    return this->uncle()->color;
}

template<typename T>
Node<T> *Node<T>::sibling() {
    auto parent = this->parent;
    if (!parent) {
        return nullptr;
    }

    if (parent->left == this) {
        return parent->right;
    }
    return parent->left;
}

template<>
inline unsigned int Node<char>::score() {
    return value;
}

template<>
inline unsigned int Node<int>::score() {
    return value;
}