#ifndef RBT
#define RBT

template <typename T>
class RedBlackTree {
private:
    Node<T> *root = nullptr;

    void rotateLeft(Node<T> *node);
    void rotateRight(Node<T> *node);

    void recolor(Node<T> *node);
    void case1(Node<T> *node);
    void case2(Node<T> *node);
    void case3(Node<T> *node);

    void displayTree(Node<T> *node = nullptr);
public:
    RedBlackTree();
    void insert(T value);
};

#include "RedBlackTree.tpp"
#endif //RBT