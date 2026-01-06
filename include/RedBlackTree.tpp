#pragma once
#include <iostream>
#include "stdlib.h"
#include <queue>

template<typename T>
RedBlackTree<T>::RedBlackTree() {}

template<typename T>
void RedBlackTree<T>::insert(T value) {
    auto *node = new Node<T>(value);
    // Inserted node is the very first one.
    if (root == nullptr) {
        root = node;
        root->color = Color::BLACK;
        return;
    }

    Node<T> *parent = root;
    while (true) {
        if (node->score() < parent->score()) {
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

    node->parent = parent;
    recolor(node);
}

template<typename T>
void RedBlackTree<T>::recolor(Node<T> *node) {
    // Case 1 (red uncle)
    if (node->parent &&
        node->parent->color == Color::RED) { // Violation

        if (node->uncleColor() == Color::RED) {
            case1(node);
        } else { // Uncle = Black
            case2(node);
            case3(node);
        }
    }

}

template<typename T>
void RedBlackTree<T>::case0() {
    if (root->color == Color::RED) {
        root->color = Color::BLACK;
    }
}

template<typename T>
void RedBlackTree<T>::case1(Node<T> *node) {
    // Red Uncle Case
    node->parent->color = Color::BLACK;
    node->uncle()->color = Color::BLACK;
    node->grandparent()->color = Color::RED;
    case0();
}

template<typename T>
void RedBlackTree<T>::case2(Node<T> *node) {
    // Uncle Black
    auto grandparent = node->grandparent();

    // Left Triangle (>)
    if (node->parent &&
        node->parent->left == node &&
        grandparent &&
        grandparent->right == node->parent) {

        rotateRight(node->parent);
        case3(node->right);
    }
    // Right Triangle (<)
    if (node->parent &&
        node->parent->right == node &&
        grandparent &&
        grandparent->left == node->parent) {

        rotateLeft(node->parent);
        case3(node->left);
    }
}

template<typename T>
void RedBlackTree<T>::case3(Node<T> *node) {
    // Uncle Black
    auto grandparent = node->grandparent();

    // Left Line (\)
    if (node->parent &&
        node->parent->right == node &&
        grandparent &&
        grandparent->right == node->parent) {

        node->parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        rotateLeft(grandparent);
        case0();
    }
    // Right Line (/)
    if (node->parent &&
        node->parent->left == node &&
        grandparent &&
        grandparent->left == node->parent) {

        node->parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        rotateRight(grandparent);
        case0();
    }

}

template<typename T>
void RedBlackTree<T>::rotateLeft(Node<T> *node) {
    Node<T> *parent = node->parent;
    Node<T> *rightNode = node->right;

    if (parent) {
        if (parent->left == node) {
            connectLeft(parent, rightNode);
        } else {
            connectRight(parent, rightNode);
        }
    } else {
        rightNode->parent = nullptr;
    }

    node->right = rightNode->left;
    connectLeft(rightNode, node);

    if (node == root) {
        root = rightNode;
    }

}

template<typename T>
void RedBlackTree<T>::rotateRight(Node<T> *node) {
    Node<T> *parent = node->parent;
    Node<T> *leftNode = node->left;

    if (parent) {
        if (parent->left == node) {
            connectLeft(parent, leftNode);
        } else {
            connectRight(parent, leftNode);
        }
    } else {
        leftNode->parent = nullptr;
    }

    node->left = leftNode->right;
    connectRight(leftNode, node);

    if (node == root) {
        root = leftNode;
    }

}

template<typename T>
void RedBlackTree<T>::displayTree() {
    system("");
    std::queue<Node<T>*> Q1;
    std::queue<Node<T>*> Q2;
    bool whichQueue = true;
    char level = '0';
    Q1.push(root);
    bool wasLevelNumberPrinted = false;
    while (!Q1.empty() || !Q2.empty()) {
        if (!wasLevelNumberPrinted) {
            std::cout<<"["<<level<<"] ";
            wasLevelNumberPrinted = true;
        }
        auto que = whichQueue ? &Q1 : &Q2;
        auto otherQue = whichQueue ? &Q2 : &Q1;
        auto current = que->front();
        if (current->left != nullptr) {
            otherQue->push(current->left);
        }
        if (current->right != nullptr) {
            otherQue->push(current->right);
        }
        if (current->color == Color::RED) {
            std::cout << "\033[91m" << current->value << "\033[0m" << " ";
        } else {
            std::cout << "\033[90m" << current->value << "\033[0m" << " ";
        }
        que->pop();
        if (!que->empty()) {
            continue;
        }
        std::cout<<"\n";
        wasLevelNumberPrinted = false;
        level++;
        whichQueue = !whichQueue;
    }
    std::cout<<"----\n";
}

template<typename T>
void RedBlackTree<T>::connectLeft(Node<T> *parent, Node<T> *node) {
    parent->left = node;
    node->parent = parent;
}

template<typename T>
void RedBlackTree<T>::connectRight(Node<T> *parent, Node<T> *node) {
    parent->right = node;
    node->parent = parent;
}

template<typename T>
void RedBlackTree<T>::transplant(Node<T> *u, Node<T> *v) {
    if (u == root) {
        root = v;
    } else if (u->parent->left == u) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template<typename T>
void RedBlackTree<T>::remove(T value) {
    //TODO
}

template<>
inline Node<int> *RedBlackTree<int>::find(const int value) {
    Node<int> *current = root;
    while (current) {
        if (current->value == value) {
            return current;
        }

        if (current->value < value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

//Identical for int and char

template<>
inline Node<char> *RedBlackTree<char>::find(const char value) {
    Node<char> *current = root;
    while (current) {
        if (current->value == value) {
            return current;
        }

        if (current->value < value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

template<typename T>
Node<T> *RedBlackTree<T>::findMin() {
    Node<T> *current = root;
    while (current->left) {
        current = current->left;
    }
    return current;
}

template<typename T>
Node<T> *RedBlackTree<T>::findMax() {
    Node<T> *current = root;
    while (current->right) {
        current = current->right;
    }
    return current;
}