template<typename T>
Node<T>::Node(T value) : value(value) {}

template<typename T>
bool Node<T>::isLeftChild() {
    if (parent->left == this) {
        return true;
    }
    return false;
}

template<typename T>
bool Node<T>::isRightChild() {
    return !isLeftChild();
}

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

template<typename T>
Node<T> *Node<T>::closeNephew() {
    auto sibling = this->sibling();

    if (sibling->isLeftChild()) {
        return sibling->right;
    }
    return sibling->left;
}

template<typename T>
Node<T> *Node<T>::distantNephew() {
    auto sibling = this->sibling();

    if (sibling->isLeftChild()) {
        return sibling->left;
    }
    return sibling->right;
}

template<typename T>
bool Node<T>::hasChildren() {
    if (left || right) {
        return true;
    }
    return false;
}

template<typename T>
bool Node<T>::hasTwoChildren() {
    if (left && right) {
        return true;
    }
    return false;
}

template<typename T>
Node<T> *Node<T>::hasOnlyOneChild() {
    if (left && !right) {
        return left;
    }
    if (!left && right) {
        return right;
    }
    return nullptr;
}

template<typename T>
bool Node<T>::isLeaf() {
    if (!parent) {
        // Is a root
        return false;
    }
    if (!hasChildren()) {
        // Neither a root
        // Nor has children
        return true;
    }
    // Has children
    return false;
}

template<typename T>
void Node<T>::detachFromParent() {
    if (parent->left == this) {
        parent->left = nullptr;
    } else {
        parent->right = nullptr;
    }
}

template<typename T>
Color Node<T>::leftChildColor() {
    if (left) {
        return left->color;
    }

    return Color::BLACK;
}

template<typename T>
Color Node<T>::rightChildColor() {
    if (right) {
        return right->color;
    }

    return Color::BLACK;
}

template<typename T>
bool Node<T>::hasRedChild() {
    return rightChildColor() == Color::RED || leftChildColor() == Color::RED;
}

template<typename T>
inline unsigned int Node<T>::score() {
    return value.score();
}

template<>
inline unsigned int Node<char>::score() {
    return value;
}

template<>
inline unsigned int Node<int>::score() {
    return value;
}