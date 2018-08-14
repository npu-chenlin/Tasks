/**
 *  0:1 2
 *  1:3,4   2:5,6
 *  3:7,8   5:9   6:10
 */

#include <iostream>

#include "ThreadBT.hpp"

int main(int argc, char const *argv[])
{
    ThreadBT<int> tree(0);
    ThreadBTNode<int> node[10];
    for (int i = 0; i < 10; ++i)
    {
        node[i].setData(i);
    }
    ThreadBTNode<int> node1(1);
    ThreadBTNode<int> node2(2);
    ThreadBTNode<int> node3(3);
    ThreadBTNode<int> node4(4);
    ThreadBTNode<int> node5(5);
    ThreadBTNode<int> node6(6);
    ThreadBTNode<int> node7(7);
    ThreadBTNode<int> node8(8);
    ThreadBTNode<int> node9(9);
    ThreadBTNode<int> node10(10);

    tree.insertSubBT(&node1, tree.getRoot());
    tree.insertSubBT(&node2, tree.getRoot());
    tree.insertSubBT(&node3, &node1);
    tree.insertSubBT(&node4, &node1);
    tree.insertSubBT(&node5, &node2);
    tree.insertSubBT(&node6, &node2);
    tree.insertSubBT(&node7, &node3);
    tree.insertSubBT(&node8, &node3);
    tree.insertSubBT(&node9, &node5);
    tree.insertSubBT(&node10, &node6);

    tree.preOrder(tree.getRoot());

    tree.inThreading();




    return 0;
}
