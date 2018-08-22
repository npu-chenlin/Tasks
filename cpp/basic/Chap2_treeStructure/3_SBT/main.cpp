#include <iostream>

#include "AVL.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    AVL<int> tree(4);

    shared_ptr<AVLNode<int>> node1 = make_shared<AVLNode<int>>(1);
    shared_ptr<AVLNode<int>> node2 = make_shared<AVLNode<int>>(2);
    shared_ptr<AVLNode<int>> node3 = make_shared<AVLNode<int>>(3);
    shared_ptr<AVLNode<int>> node5 = make_shared<AVLNode<int>>(5);
    shared_ptr<AVLNode<int>> node6 = make_shared<AVLNode<int>>(6);
    shared_ptr<AVLNode<int>> node7 = make_shared<AVLNode<int>>(7);
    shared_ptr<AVLNode<int>> node8 = make_shared<AVLNode<int>>(8);
    shared_ptr<AVLNode<int>> node9 = make_shared<AVLNode<int>>(9);
    shared_ptr<AVLNode<int>> node10 = make_shared<AVLNode<int>>(10);

    tree.insertNode(node3);
    tree.insertNode(node1);
    tree.insertNode(node2);
    tree.insertNode(node5);
    tree.insertNode(node6);
    tree.insertNode(node7);
    tree.insertNode(node8);
    tree.insertNode(node9);
    tree.insertNode(node10);

    tree.deleteNode(tree.getRoot());
    tree.deleteNode(node64);
    tree.inOrder(tree.getRoot());
 
    return 0;
}
