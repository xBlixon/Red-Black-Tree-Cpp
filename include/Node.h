#ifndef NODE
#define NODE
#include "Color.h"

template <typename T>
struct Node {
public:
    Color color = Color::RED;
    Node<T> *parent = nullptr;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    T value;

    Node(T value);

    unsigned int score();
    Node<T> *grandparent();
    Node<T> *uncle();
    Node<T> *sibling();
    Node<T> *closeNephew();
    Node<T> *distantNephew();
    Node<T> *hasOnlyOneChild();
    bool isLeftChild();
    bool isRightChild();
    bool hasChildren();
    bool hasTwoChildren();
    bool isLeaf();
    Color leftChildColor();
    Color rightChildColor();
    bool hasRedChild();
    void detachFromParent();
    Color uncleColor();
};

#include "Node.tpp"
#endif //NODE