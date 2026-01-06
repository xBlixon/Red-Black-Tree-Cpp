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

template<>
inline unsigned int Node<char>::score() {
    return value;
}

template<>
inline unsigned int Node<int>::score() {
    return value;
}