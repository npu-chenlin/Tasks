#ifndef _BINARRYTREE_H
#define _BINARRYTREE_H
#include <iostream>
template <typename T> class binaryTreeNode
{
public:
	binaryTreeNode()
	{
		data = NULL;
		lChild = NULL;
		rChild = NULL;
	}
	binaryTreeNode(T newData)
	{
		data = newData;
		lChild = rChild = NULL;
	}
	~binaryTreeNode();
	T getData() return data;
	binaryTreeNode<T>* getLChild()return lChild;
	binaryTreeNode<T>* getRChild()return rChild;
private:
	friend class binaryTree<T>;
	T data;
	binaryTreeNode<T>* lChild;
	binaryTreeNode<T>* rChild;
};

template <typename T> class binaryTree
{
public:
	binaryTree()
	{
		root = new binaryTreeNode<T>();
	}
	~binaryTree()
	{
		delete root;
	}
	void preOrder();
	void inOrder();
	void postOrder();
	void layOrder();
private:
	binaryTreeNode<T>* root;
};

template <typename T> void binaryTree::preOrder(binaryTreeNode<T>* node)
{
	if(node != NULL)
	{
		std::cout<<node->getData()<<std::endl;
		preOrder(node->getLChild());
		preOrder(node->getRChild());
	}
}
template <typename T> void binaryTree::inOrder(binaryTreeNode<T>* node)
{
	if(node != NULL)
	{
		inOrder(node->getLChild());
		std::cout<<node->getData()<<std::endl;
		inOrder(node->getRChild());
	}
}
template <typename T> void binaryTree::postOrder(binaryTreeNode<T>* node)
template <typename T> void binaryTree::layOrder(binaryTreeNode<T>* node)
#endif