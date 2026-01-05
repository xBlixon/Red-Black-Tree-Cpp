template<typename T>
Node<T>::Node(T value) : value(value) {}

template<typename T>
Node<T> *Node<T>::uncle() {
    Node<T> *nodeParent = this->parent;
    if (nodeParent != nullptr && nodeParent->parent != nullptr) {
        Node<T> *nodeGrandparent = nodeParent->parent;

        if (nodeGrandparent->left == nodeParent ) {
            return nodeGrandparent->right;
        } else {
            return nodeGrandparent->left;
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