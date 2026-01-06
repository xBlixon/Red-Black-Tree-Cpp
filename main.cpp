#include "Node.h"
#include "include/RedBlackTree.h"
#include "include/Color.h"

int main() {
    RedBlackTree<int> tree;
    tree.insert(10);
    // tree.displayTree();
    tree.insert(11);
    // tree.displayTree();
    tree.insert(8);
    // tree.displayTree();
    tree.insert(7);
    // tree.displayTree();
    tree.insert(9);
    // tree.displayTree();
    tree.insert(12);
    // tree.displayTree();
    tree.insert(13);
    // tree.displayTree();
    tree.insert(14);
    tree.displayTree();
    std::cout<< "text\n";
    return 0;
}