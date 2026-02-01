#include "include/RedBlackTree.h"

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
    tree.erase(tree.begin());
    for (auto v: tree) { // Iterators work
        std::cout << v << std::endl;
    }
    tree.remove(12);
    tree.displayTree();
    return 0;
}