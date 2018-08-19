#include <iostream>

#include "RBT.hpp"

int main(int argc, char const *argv[])
{
    RBT<int> tree(1);

    RBTNode<int> node2(2);
    RBTNode<int> node3(3);
    RBTNode<int> node4(4);
    RBTNode<int> node5(5);
    RBTNode<int> node6(6);
    RBTNode<int> node7(7);
    RBTNode<int> node8(8);
    RBTNode<int> node9(9);
    RBTNode<int> node10(10);

    tree.insertNode(&node2);
    tree.insertNode(&node3);
    tree.insertNode(&node4);
    tree.insertNode(&node5);
    tree.insertNode(&node6);
    tree.insertNode(&node7);
    tree.insertNode(&node8);
    tree.insertNode(&node9);
    tree.insertNode(&node10);

    tree.preOrder(tree.getRoot());
    return 0;
}
