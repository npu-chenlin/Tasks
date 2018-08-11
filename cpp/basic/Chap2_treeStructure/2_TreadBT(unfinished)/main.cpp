/**
 *  0:1 2
 *  1:3,4   2:5,6
 *  3:7,8   5:9   6:10
 */

#include <iostream>

#include "BinaryTree.hpp"

int main(int argc, char const *argv[])
{
	BinaryTree<int> tree(0);
	BinaryTreeNode<int> node[10];
	for (int i = 0; i < 10; ++i)
	{
		node[i].setData(i);
	}
	BinaryTreeNode<int> node1(1);
	BinaryTreeNode<int> node2(2);
	BinaryTreeNode<int> node3(3);
	BinaryTreeNode<int> node4(4);
	BinaryTreeNode<int> node5(5);
	BinaryTreeNode<int> node6(6);
	BinaryTreeNode<int> node7(7);
	BinaryTreeNode<int> node8(8);
	BinaryTreeNode<int> node9(9);
	BinaryTreeNode<int> node10(10);

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





	return 0;
}