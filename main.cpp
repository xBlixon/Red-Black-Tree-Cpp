#include "Node.h"
#include "include/RedBlackTree.h"
#include "include/Color.h"

int main() {
    RedBlackTree<int> tree;
    tree.insert(12);
    tree.insert(5);
    tree.insert(15);
    tree.insert(13);
    tree.insert(3);
    tree.insert(17);
    tree.insert(10);
    tree.insert(14);
    tree.insert(4);
    tree.insert(11);
    tree.insert(7);
    tree.insert(6);
    tree.displayTree();
    tree.remove(17);
    tree.displayTree();
    std::cout<< "text\n";
    for (auto v: tree) { // Iterators work
        std::cout << v << std::endl;
    }
    return 0;
}