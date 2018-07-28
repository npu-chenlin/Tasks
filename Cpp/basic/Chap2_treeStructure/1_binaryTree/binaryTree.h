#ifndef _BINARRYTREE_H
#define _BINARRYTREE_H

#include <iostream>
#include <queue>

template <typename T> class binaryTree;

template <typename T> class binaryTreeNode
{
public:
	binaryTreeNode()//无参数初始化节点
	{
		data = NULL;
		lChild = NULL;
		rChild = NULL;
	}
	binaryTreeNode(T newData)//有参数初始化节点
	{
		data = newData;
		lChild = rChild = NULL;
	}
	~binaryTreeNode();
	
	T getData() {return data;}
	binaryTreeNode<T>* getLChild(){return lChild;}
	binaryTreeNode<T>* getRChild(){return rChild;}
	
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
	binaryTree(binaryTreeNode<T>* node)
	{
		root = node;
		root->lChild = node->lChild;
		root->rChild = node->rChild;
	}
	~binaryTree()
	{
		delete root;
	}
	
	void preOrder(binaryTreeNode<T>* node);// 前序中序后序遍历
	void layOrder(binaryTreeNode<T>* node);// 层序遍历

	binaryTreeNode<T>* parentNode(binaryTreeNode<T>* node);
	binaryTreeNode<T>* lChildNode(binaryTreeNode<T>* node);
	binaryTreeNode<T>* rChildNode(binaryTreeNode<T>* node);
	binaryTreeNode<T>* brotherNode(binaryTreeNode<T>* node);

	int getDepth(int numberOfNodes);
	void insertSubBT(binaryTreeNode<T>* node);

private:
	binaryTreeNode<T>* root;
};

template <typename T> void binaryTree<T>::preOrder(binaryTreeNode<T>* node)
{ 
	if(node != NULL)
	{
		std::cout<<node->getData()<<std::endl;
		preOrder(node->getLChild());
		preOrder(node->getRChild());
	}
}

template <typename T> void binaryTree<T>::layOrder(binaryTreeNode<T>* node)
{
	int max = 50;
	int front = 0;
	int rear = 0;
	int count = 0;
	if( node != NULL)
	{
		binaryTreeNode<T>* current;
		T* queue = new T[max];
		queue[rear]=node;
		rear++;
		count++;
		while( count != 0)
		{
			current = queue[front];
			front++;
			count--;
			std::cout<<current->getData()<<std::endl;
			if(current->getLChild() != NULL)
			{
				queue[rear] = current->getLChild();
				rear++;
				count++;
			}
			if(current->getRChild() != NULL)
			{
				queue[rear] = current->getRChild();
				rear++;
				count++;
			}

		}
	}
}

template <typename T> binaryTreeNode<T>* binaryTree<T>::parentNode(binaryTreeNode<T>* node)
{
	int max = 50;
	int front = 0;
	int rear = 0;
	int count = 0;
	if (node == root)
	{
		return NULL;
	}
	if( node != NULL)
	{
		binaryTreeNode<T>* current,leftChild,rightChild;
		T* queue = new T[max];
		queue[rear]=root;
		rear++;
		count++;
		while( count != 0)
		{
			current = queue[front];
			front++;
			count--;
			leftChild = current->getLChild();
			rightChild = current->getRChild();
			if(leftChild != NULL)
			{
				if(leftChild == node) return current;
				queue[rear] = leftChild;
				rear++;
				count++;
			}
			if(rightChild != NULL)
			{
				if(rightChild == node) return current;
				queue[rear] = leftChild;
				rear++;
				count++;
			}
		}
		return NULL;
	}
}

template <typename T> binaryTreeNode<T>* binaryTree<T>::lChildNode(binaryTreeNode<T>* node)
{
	if (node != NULL) {return node->getLChild;}
	else return NULL;
}

template <typename T> binaryTreeNode<T>* binaryTree<T>::rChildNode(binaryTreeNode<T>* node)
{
	if (node != NULL) {return node->getRChild;}
	else return NULL;
}

template <typename T> binaryTreeNode<T>* binaryTree<T>::brotherNode(binaryTreeNode<T>* node)
{
	if (node == NULL)return NULL;
	binaryTreeNode<T>* parentNode = binaryTree<T>::parentNode(node);
	if(parentNode == NULL)
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

template <typename T> int binaryTree<T>::getDepth(int numberOfNodes)
{
	binaryTreeNode<T>* nodeStack = new binaryTreeNode<T>[numberOfNodes];
	binaryTreeNode<T>* node;
	int top = -1;
	int maxDepth = 0 , currentDepth = 0;

}

template <typename T> void binaryTree<T>::insertSubBT(binaryTreeNode<T>* node)
{

}

#endif
