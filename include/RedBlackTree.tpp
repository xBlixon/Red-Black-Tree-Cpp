#pragma once
#include <exception>

template<typename T>
RedBlackTree<T>::RedBlackTree() {}

template<typename T>
void RedBlackTree<T>::insert(T value) {
    Node<T> node = new Node<T>(value);
    // Inserted node is the very first one.
    if (root == nullptr) {
        root = node;
        root->color = Color::BLACK;
        return;
    }

    Node<T> *parent = root;
    while (true) {
        if (node.score() < parent->score()) {
           if (parent->left == nullptr) {
               parent->left = node;
               break;
           }
           // Deeper
           parent = parent->left;

        } else { // Greater
            if (parent->right == nullptr) {
                parent->right = node;
                break;
            }
            // Deeper
            parent = parent->right;
        }
    }

    recolor();
}

template<typename T>
void RedBlackTree<T>::recolor(Node<T> *node) {
    // Case 1 (red uncle)
    if (node->uncleColor() == Color::RED) {
        case1(&node);
    } else { // Uncle = Black
        case2(&node);
        case3(&node);
    }
}

template<typename T>
void RedBlackTree<T>::case1(Node<T> *node) {
    // Red Uncle Case
    node->parent->color = Color::BLACK;
    node->uncle()->color = Color::BLACK;
    node->parent->parent->color = Color::RED;
}

template<typename T>
void RedBlackTree<T>::case2(Node<T> *node) {
    // Uncle Black

    // Left Triangle (>)
    if (node->parent->left == node && node->parent->parent->right == node->parent) {
        rotateRight(node->parent);
    }
    // Right Triangle (<)
    if (node->parent->right == node && node->parent->parent->left == node->parent) {
        rotateLeft(node->parent);
    }
}

template<typename T>
void RedBlackTree<T>::case3(Node<T> *node) {
    // Uncle Black

    // Left Line (\)
    if (node->parent->right == node && node->parent->parent->right == node->parent) {
        node->parent->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        rotateLeft(node->parent->parent);
    }
    // Right Line (/)
    if (node->parent->left == node && node->parent->parent->left == node->parent) {
        node->parent->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        rotateRight(node->parent->parent);
    }

}

template<typename T>
void RedBlackTree<T>::rotateLeft(Node<T> *node) {
    Node<T> *parent = node->parent;
    Node<T> *rightNode = node->right;

    if (rightNode != nullptr) {
        rightNode->parent = parent;
        if (parent->left == node) {
            parent->left = rightNode;
        } else {
            parent->right = rightNode;
        }

        node->parent = rightNode;
        node->right = rightNode->left;
        rightNode->left = node;

    } else {
        throw R"(Unable to rotate left over nullptr.)";
    }

}

template<typename T>
void RedBlackTree<T>::rotateRight(Node<T> *node) {
    Node<T> *parent = node->parent;
    Node<T> *leftNode = node->left;

    if (leftNode != nullptr) {
        leftNode->parent = parent;
        if (parent->left == node) {
            parent->left = leftNode;
        } else {
            parent->right = leftNode;
        }

        node->parent = leftNode;
        node->left = leftNode->right;
        leftNode->right = node;

    } else {
        throw R"(Unable to rotate right over nullptr.)";
    }

}