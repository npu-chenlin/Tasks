#include <iostream>
#include <memory>
#include "RBT.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    RBT<int> tree(1);

    shared_ptr<RBTNode<int>> node2(new RBTNode<int>(2));
    shared_ptr<RBTNode<int>> node3(new RBTNode<int>(3));
    shared_ptr<RBTNode<int>> node4(new RBTNode<int>(4));
    shared_ptr<RBTNode<int>> node5(new RBTNode<int>(5));
    shared_ptr<RBTNode<int>> node6(new RBTNode<int>(6));
    shared_ptr<RBTNode<int>> node7(new RBTNode<int>(7));
    shared_ptr<RBTNode<int>> node8(new RBTNode<int>(8));
    shared_ptr<RBTNode<int>> node9(new RBTNode<int>(9));
    shared_ptr<RBTNode<int>> node10(new RBTNode<int>(10));

    tree.insertNode(node2);
    tree.insertNode(node3);
    tree.insertNode(node4);
    tree.insertNode(node5);
    tree.insertNode(node6);
    tree.insertNode(node7);
    tree.insertNode(node8);
    tree.insertNode(node9);
    tree.insertNode(node10);

    tree.preOrder(tree.getRoot());
    return 0;
}
