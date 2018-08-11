#ifndef _BINARRYTREE_H
#define _BINARRYTREE_H

#include <iostream>
#include <list>
#include <vector>
template <typename T> class BinaryTree;

template <typename T> class BinaryTreeNode
{
public:
	BinaryTreeNode() // Initialize node without param
	{
		data = NULL;
		lChild = NULL;
		rChild = NULL;
	}
	explicit BinaryTreeNode(T newData) //Initialize node with param
	{
		data = newData;
		lChild = rChild = NULL;
	}

	void setData(T newData) {data = newData;}
	T getData() {return data;}
	BinaryTreeNode<T>* getLChild() {return lChild;}
	BinaryTreeNode<T>* getRChild() {return rChild;}

private:
	friend class BinaryTree<T>;
	T data;
	BinaryTreeNode<T>* lChild;
	BinaryTreeNode<T>* rChild;
};

template <typename T> class BinaryTree
{
public:
	BinaryTree()
	{
		root = new BinaryTreeNode<T>();
	}
	explicit BinaryTree(T newData)
	{
		root = new BinaryTreeNode<T>(newData);
	}
	~BinaryTree()
	{
		if ( root )
		{
			delete root;
			root = NULL;
		}

	}

	void preOrder(BinaryTreeNode<T>* node);// 前序中序后序遍历
	void layOrder(BinaryTreeNode<T>* node);// 层序遍历

	BinaryTreeNode<T>* getRoot(){return root;}
	BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* node);
	BinaryTreeNode<T>* getLChild(BinaryTreeNode<T>* node);
	BinaryTreeNode<T>* getRChild(BinaryTreeNode<T>* node);
	BinaryTreeNode<T>* getBrother(BinaryTreeNode<T>* node);

	int getDepth();
	void insertSubBT(BinaryTreeNode<T>* subBT , BinaryTreeNode<T>* node);
	void deleteNodes(BinaryTreeNode<T>* node);
	void destroyBT();

private:
	BinaryTree<T>(const BinaryTree<T>&);
	BinaryTree<T>& operator=(const BinaryTree<T>&);

private:
	BinaryTreeNode<T>* root;
};

template <typename T> void BinaryTree<T>::preOrder(BinaryTreeNode<T>* node)
{
	if (node != NULL)
	{
		std::cout << node->getData() << std::endl;
		preOrder(node->getLChild());
		preOrder(node->getRChild());
	}
}

template <typename T> void BinaryTree<T>::layOrder(BinaryTreeNode<T>* node)
{
	if ( node != NULL)
	{
		BinaryTreeNode<T>* current = node;
		std::list<BinaryTreeNode<T>*> tempList;
		std::cout << current->getData() << std::endl;
		while ( tempList.empty() || current != NULL)
		{
			if (current->lChild != NULL)
			{
				tempList.push_back(current->lChild);
			}
			if (current->rChild != NULL)
			{
				tempList.push_back(current->rChild);
			}
			current = tempList.front();
			std::cout << current->getData() << std::endl;
			tempList.pop_front();
		}
	}
}

template <typename T> BinaryTreeNode<T>* BinaryTree<T>::getParent(BinaryTreeNode<T>* node)
{
	if (node == root)
	{
		return NULL;
	}

	if ( node != NULL)
	{
		BinaryTreeNode<T>* current = root;
		std::list<BinaryTreeNode<T>*> tempList;
		while ( tempList.empty() || current != NULL)
		{
			if (current->lChild != node && current->lChild != NULL)
			{
				tempList.push_back(current->lChild);
			}
			else if ( current->lChild == node)
			{
				return current;
			}

			if (current->rChild != node && current->rChild != NULL)
			{
				tempList.push_back(current->rChild);
			}
			else if ( current->rChild == node)
			{
				return current;
			}

			current = tempList.front();
			tempList.pop_front();
		}

		return NULL;
	}
}

template <typename T> BinaryTreeNode<T>* BinaryTree<T>::getLChild(BinaryTreeNode<T> *node)
{
	if (node != NULL) {return node->lChild;}
	else return NULL;
}

template <typename T> BinaryTreeNode<T>* BinaryTree<T>::getRChild(BinaryTreeNode<T>* node)
{
	if (node != NULL) {return node->rChild;}
	else return NULL;
}

template <typename T> BinaryTreeNode<T>* BinaryTree<T>::getBrother(BinaryTreeNode<T> *node)
{
	if (node == NULL)return NULL;
	BinaryTreeNode<T>* parentNode = getParent(node);
	if (parentNode == NULL)
	{
		return NULL;
	}
	if (parentNode->getLChild() == node)
	{
		return parentNode->getRChild();
	}
	if (parentNode->getRChild() == node)
	{
		return parentNode->getLChild();
	}
}

template <typename T> int BinaryTree<T>::getDepth()
{
	std::list<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* node = root;
	nodeStack->push_back(node);
	int maxDepth = 1;
	while (!nodeStack.empty())
	{
		while (node -> lChild != NULL)
		{
			node = node -> lChild;
			nodeStack.push_back(node);
		}
		if (node -> rChild == NULL)
		{
			if (nodeStack.size() > maxDepth)
			{
				maxDepth = nodeStack.size();
			}
			node = nodeStack.back();
			nodeStack.pop_back();
		}
		else
		{
			node = node -> rChild;
			nodeStack.push_back(node);
		}
	}
	return maxDepth;
}

template <typename T> void BinaryTree<T>::insertSubBT(BinaryTreeNode<T>* subBT , BinaryTreeNode<T> *node)
{
	if (node == NULL) return;
	if (node -> lChild == NULL)
	{
		node -> lChild = subBT;
	}
	else if (node -> rChild == NULL)
	{
		node -> rChild = subBT;
	}
}
template <typename T> void BinaryTree<T>::deleteNodes(BinaryTreeNode<T>* node)
{
	if (node != NULL)
	{
		deleteNodes(node->lChild);
		deleteNodes(node->rChild);
		delete node;
	}
}
template <typename T> void BinaryTree<T>::destroyBT()
{
	deleteNodes(root->lChild);
	deleteNodes(root->rChild);
	root = NULL;
}

#endif
