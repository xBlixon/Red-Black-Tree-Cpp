#ifndef RBT
#define RBT

template <typename T>
class RedBlackTree {
private:
    Node<T> *root = nullptr;

    void rotateLeft(Node<T> *node);
    void rotateRight(Node<T> *node);

    void recolor();
public:
    RedBlackTree();
    void insert(T value);
};

#include "RedBlackTree.tpp"
#endif //RBT