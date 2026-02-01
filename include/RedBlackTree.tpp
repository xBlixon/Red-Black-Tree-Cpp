#pragma once
#include <iostream>
#include <queue>
#include "Node.h"

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
    insertCase0();
}

template<typename T>
void RedBlackTree<T>::recolor(Node<T> *node) {
    // Case 1 (red uncle)
    if (node->parent &&
        node->parent->color == Color::RED) { // Violation

        if (node->uncleColor() == Color::RED) {
            insertCase1(node);
        } else { // Uncle = Black
            insertCase2(node);
            insertCase3(node);
        }
    }

}

template<typename T>
void RedBlackTree<T>::insertCase0() {
    if (root->color == Color::RED) {
        root->color = Color::BLACK;
    }
}

template<typename T>
void RedBlackTree<T>::insertCase1(Node<T> *node) {
    auto grandparent = node->grandparent();
    // Red Uncle Case
    node->parent->color = Color::BLACK;
    node->uncle()->color = Color::BLACK;
    grandparent->color = Color::RED;
    recolor(grandparent);
}

template<typename T>
void RedBlackTree<T>::insertCase2(Node<T> *node) {
    // Uncle Black
    auto grandparent = node->grandparent();

    // Left Triangle (>)
    if (node->parent &&
        node->parent->left == node &&
        grandparent &&
        grandparent->right == node->parent) {

        rotateRight(node->parent);
        insertCase3(node->right);
    }
    // Right Triangle (<)
    if (node->parent &&
        node->parent->right == node &&
        grandparent &&
        grandparent->left == node->parent) {

        rotateLeft(node->parent);
        insertCase3(node->left);
    }
}

template<typename T>
void RedBlackTree<T>::insertCase3(Node<T> *node) {
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
        insertCase0();
    }
    // Right Line (/)
    if (node->parent &&
        node->parent->left == node &&
        grandparent &&
        grandparent->left == node->parent) {

        node->parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        rotateRight(grandparent);
        insertCase0();
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
    if (!root) {
        std::cout << "\033[91mEMPTY TREE!\033[0m\n";
        return;
    }
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
    if (v) {
        v->parent = u->parent;
    }
}

template<typename T>
void RedBlackTree<T>::remove(T value) {
    auto node = find(value);
    if (!node) {
        return;
    }

    removeNode(node);
}

template<typename T>
void RedBlackTree<T>::removeNode(Node<T> *node) {
    if (node == root ) {
        if (auto child = node->hasOnlyOneChild()) {
            root = child;
            child->parent = nullptr;
            delete node;
            return;
        } else if (!child) {
            root = nullptr;
            delete node;
            return;
        }
    }


    if (node->isLeaf()) {
        if (node->color == Color::RED) {
            node->detachFromParent();
            delete node;
            return;
        }

        // Node is black
        doubleBlackFix(node);
        node->detachFromParent();
        delete node;
        return;
    }

    if (auto child = node->hasOnlyOneChild()) {
        child->color = Color::BLACK;
        if (node->isLeftChild()) {
            connectLeft(node->parent, child);
        } else {
            connectRight(node->parent, child);
        }
        delete node;
    }

    if (node->hasTwoChildren()) {
        auto replacement = findMin(node->right);
        while (replacement->left || replacement->right) {
            if (replacement->left) {
                replacement = replacement->left;
            } else if (replacement->right) {
                replacement = replacement->right;
            }
        }
        // Replacing contents of the memory address with
        // the replacement value
        node->value.~T();
        new (&node->value) T(replacement->value);
        removeNode(replacement);
    }
}

template<typename T>
void RedBlackTree<T>::doubleBlackFix(Node<T> *doubleBlack) {
    if (doubleBlack == root) {
        return;
    }

    auto sibling = doubleBlack->sibling();
    if (doubleBlack->parent->color == Color::RED) {
        // Case 1
        if (sibling->color == Color::BLACK &&
            sibling->leftChildColor() == Color::BLACK &&
            sibling->rightChildColor() == Color::BLACK) {

            removeCase1(doubleBlack);
            return;
        }
    }
    // Parent is Black
    // Case 3
    if (sibling->color == Color::RED) {
        removeCase3(doubleBlack);
        return;
    }
    // Parent and Sibling are Black
    // Case 4
    if (sibling->leftChildColor() == Color::BLACK &&
        sibling->rightChildColor() == Color::BLACK) {
        removeCase4(doubleBlack);

        return;
    }

    // Case 5 (becomes case 6)
    if (doubleBlack->closeNephew()->color == Color::RED) {
        removeCase5(doubleBlack);
        return;
    }

    // Far nephew must be Red
    // Case 6
    removeCase6(doubleBlack);

}

template<typename T>
void RedBlackTree<T>::removeCase1(Node<T> *db) {
    db->parent->color = Color::BLACK;
    db->sibling()->color = Color::RED;
}

template<typename T>
void RedBlackTree<T>::removeCase2(Node<T> *db) {
    db->sibling()->color = Color::RED;
    // doubleBlackFix(db);
}

template<typename T>
void RedBlackTree<T>::removeCase3(Node<T> *db) {
    db->sibling()->color = Color::BLACK;
    db->parent->color = Color::RED;
    if (db->isLeftChild()) {
        rotateLeft(db->parent);
    } else {
        rotateRight(db->parent);
    }
    removeCase1(db);
}

template<typename T>
void RedBlackTree<T>::removeCase4(Node<T> *db) {
    db->sibling()->color = Color::RED;
    doubleBlackFix(db->parent);
}


template<typename T>
void RedBlackTree<T>::removeCase5(Node<T> *db) {
    db->closeNephew()->color = Color::BLACK;
    db->sibling()->color = Color::RED;
    if (db->isLeftChild()) {
        rotateRight(db->sibling());
    } else {
        rotateLeft(db->sibling());
    }
    removeCase6(db);
}


template<typename T>
void RedBlackTree<T>::removeCase6(Node<T> *db) {
    db->sibling()->color = db->parent->color;
    db->parent->color = Color::BLACK;
    db->distantNephew()->color = Color::BLACK;

    if (db->isLeftChild()) {
        rotateLeft(db->parent);
    } else {
        rotateRight(db->parent);
    }
}

template<typename T>
inline Node<T> *RedBlackTree<T>::find(const T value) {
    Node<T> *current = root;
    unsigned int searchedScore = value.score();
    while (current) {
        if (current->value.score() == searchedScore) {
            return current;
        }

        if (searchedScore < current->value.score()) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

template<>
inline Node<int> *RedBlackTree<int>::find(const int value) {
    Node<int> *current = root;
    while (current) {
        if (current->value == value) {
            return current;
        }

        if (value < current->value) {
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
Node<T> *RedBlackTree<T>::findMin(Node<T> *node) {
    Node<T> *current = node ? node : root;
    while (current->left) {
        current = current->left;
    }
    return current;
}

template<typename T>
Node<T> *RedBlackTree<T>::findMax(Node<T> *node) {
    Node<T> *current = node ? node : root;
    while (current->right) {
        current = current->right;
    }
    return current;
}

template<typename T>
void RedBlackTree<T>::colorBlack(Node<T> *node) {
    if (!node) {
        return;
    }
    node->color = Color::BLACK;
}

template<typename T>
void RedBlackTree<T>::colorRed(Node<T> *node) {
    if (!node) {
        return;
    }
    node->color = Color::RED;
}

template<typename T>
Node<T> *RedBlackTree<T>::_getRoot() {
    return root;
}

template<typename T>
Iterator<T> RedBlackTree<T>::begin() {
    if (root != nullptr) {
        return Iterator<T>(findMin(root), root);
    }
    return Iterator<T>(nullptr, nullptr);
}

template<typename T>
Iterator<T> RedBlackTree<T>::end() {
    return Iterator<T>(nullptr, root);
}

template<typename T>
void RedBlackTree<T>::erase(Iterator<T> it) {
    if (it.ptr) {
        removeNode(it.ptr);
    }
}
