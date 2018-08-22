#include <iostream>

#include "SBT.hpp"

int main(int argc, char const *argv[])
{
    // FIXME: how to test the algorithm using recorded data
    //         using file to test the algorithm, maybe some bugs can be found
    
    SBT<int> tree(4);

    SBTNode<int> node1(1);
    SBTNode<int> node2(2);
    SBTNode<int> node3(3);
    SBTNode<int> node5(5);
    SBTNode<int> node6(6);
    SBTNode<int> node7(7);
    SBTNode<int> node8(8);
    SBTNode<int> node9(9);
    SBTNode<int> node10(10);

    tree.insertNode(&node3);
    tree.insertNode(&node1);
    tree.insertNode(&node2);
    tree.insertNode(&node5);
    tree.insertNode(&node6);
    tree.insertNode(&node7);
    tree.insertNode(&node8);
    tree.insertNode(&node9);
    tree.insertNode(&node10);

    tree.deleteNode(tree.getRoot());

    tree.inOrder(tree.getRoot());
 
    return 0;
}
