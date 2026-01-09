#ifndef RBT
#define RBT

template <typename T>
class RedBlackTree {
private:
    Node<T> *root = nullptr;

    void rotateLeft(Node<T> *node);
    void rotateRight(Node<T> *node);

    void recolor(Node<T> *node);
    void insertCase0();
    void insertCase1(Node<T> *node);
    void insertCase2(Node<T> *node);
    void insertCase3(Node<T> *node);

    void removeNode(Node<T> *node);
    void doubleBlackFix(Node<T> *doubleBlack);
    void removeCase1(Node<T> *db);
    void removeCase2(Node<T> *db);
    void removeCase3(Node<T> *db);
    void removeCase4(Node<T> *db);
    void removeCase5(Node<T> *db);
    void removeCase6(Node<T> *db);

    void connectLeft(Node<T> *parent, Node<T> *node);
    void connectRight(Node<T> *parent, Node<T> *node);
    void colorBlack(Node<T> *node);
    void colorRed(Node<T> *node);

    void transplant(Node<T> *u, Node<T> *v);
public:
    RedBlackTree();
    void insert(T value);
    Node<T>* find(T value);
    Node<T>* findMin(Node<T> *node = nullptr);
    Node<T>* findMax(Node<T> *node = nullptr);
    void remove(T value);

    void displayTree();
};

#include "RedBlackTree.tpp"
#endif //RBT