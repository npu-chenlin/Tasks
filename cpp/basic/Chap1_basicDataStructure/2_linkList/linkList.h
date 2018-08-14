#ifndef _LINKLIST_H
#define _LINKLIST_H

#include <iostream>

template <typename T> class LinkList;

template <typename T> class ListNode
{
public:
	ListNode()
	{
		next = NULL;
	}
	ListNode(T newData , ListNode<T>* nextNode = NULL)
	{
		data = newData;
		next = nextNode;
	}
	~ListNode()
	{
		next = NULL;
	}
	ListNode<T>* getNext() {return next;}
	T getData() {return data;}

private:
	friend class LinkList<T>; 
	ListNode<T>* next;
	T data;
};

template <typename T> class LinkList
{
public:
	LinkList()
	{
		head = new ListNode<T>();
	}
	~LinkList()
	{
		delete head;
	}

	// FIXME: the argument change to (int i, const T& newData) will be better
	// 		same tips can be applied to following functions
	bool insertNode(int i , T newData);
	bool insertNode(T newData);

	bool removeNode(ListNode<T>* q);
	void removeNode(int n);
	bool cleanLink();

	int getLength();
	ListNode<T>* findNode(T q);

	void printLink(); // FIXME: the function name is not good, 'print' will be better

private:
	ListNode<T>* head;
};

template <typename T> bool LinkList<T>::insertNode(int loc, T newData)
{
	ListNode<T>* p = head;
	int j;
	for (j = 0; j < loc-1; ++j)
	{
		p=p->next;
		if (p == NULL) break;
	}
	if (p == NULL && j < loc - 1)
	{
		return false;
	}
	ListNode<T>* newNode = new ListNode<T>(newData);
	newNode->next = p->next;
	p->next = newNode;
	return true;
}

template <typename T> bool LinkList<T>::insertNode(T newData)
{
	ListNode<T>* p = head;
	int j;
	for (j = 0;; ++j)
	{
		if (p->next == NULL) break;
		p=p->next;
	}
	ListNode<T>* newNode = new ListNode<T>(newData);
	p->next = newNode;
	return true;
}

template <typename T> bool LinkList<T>::removeNode(ListNode<T>* q)
{
	if (q == NULL) return 0;
	ListNode<T>* p = head;
	while(p->next != q) p = p->next;
	p->next = q->next;
	delete q;
	return 1;
}

template <typename T> void LinkList<T>::removeNode(int n)
{
	ListNode<T>* p = head;
	int i = 1;
	for (;p->next != NULL; ++i)
	{
		if (i == n)
		{
			break;
		}
		p = p->next;
	}
	p->next = p->next->next;
}

template <typename T> bool LinkList<T>::cleanLink()
{
	ListNode<T>* currentP;
	while(head->next != NULL)
	{
		currentP = head->next;
		head->next = currentP->next;
		delete currentP;
	}
	return true;
}

template <typename T> ListNode<T>* LinkList<T>::findNode(T q)
{
	ListNode<T>* p = head;
	while(p->data != q)
	{
		if(p->next == NULL) break;
		p=p->next;
	}
	if(p->data != q) return 0;
	return p;
}

template <typename T> void LinkList<T>::printLink()
{
	ListNode<T>* p = head;
	while(p->next != NULL)
	{
		p = p->next;
		std::cout<<p->getData()<<std::endl;
	}
}

template <typename T> int LinkList<T>::getLength()
{
	ListNode<T>* p = head;
	int i = 0;
	for (;p->next != NULL; ++i)
	{
		p = p->next;
	}
	return i;
}
#endif
