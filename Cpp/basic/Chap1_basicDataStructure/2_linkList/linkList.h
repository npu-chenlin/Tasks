#ifndef _LINKLIST_H
#define _LINKLIST_H
#include <iostream>
template <typename T> class linkList;
template <typename T> class listNode
{
public:
	listNode()
	{
		next = NULL;
	}
	listNode(T newData , listNode<T>* nextNode = NULL)
	{
		data = newData;
		next = nextNode;
	}
	~listNode()
	{
		next = NULL;
	}
	listNode<T>* getNext() {return next;}
	T getData() {return data;}
private:
	friend class linkList<T>; 
	listNode<T>* next;
	T data;
};

template <typename T> class linkList
{
public:
	linkList()
	{
		head = new listNode<T>();
	}
	~linkList()
	{
		delete head;
	}
	bool insertNode(int i , T newData);
	bool insertNode(T newData);
	bool removeNode(listNode<T>* q);
	bool cleanLink();
	listNode<T>* findNode(T q);
private:
	listNode<T>* head;
};

template <typename T> bool linkList<T>::insertNode(int loc ,T newData)
{
	listNode<T>* p = head;
	int j;
	for (j = 0; j < loc; ++j)
	{
		p=p->next;
		if (p == NULL) break;
	}
	if (p == NULL && j < loc)
	{
		return false;
	}
	listNode<T>* newNode = new listNode<T>(newData);
	newNode->next = p->next;
	p->next = newNode;
	return true;
}
template <typename T> bool linkList<T>::insertNode(T newData)
{
	listNode<T>* p = head;
	int j;
	for (j = 0;; ++j)
	{
		if (p->next == NULL) break;
		p=p->next;
	}
	listNode<T>* newNode = new listNode<T>(newData);
	p->next = newNode;
	return true;
}
template <typename T> bool linkList<T>::removeNode(listNode<T>* q)
{
	if (q == NULL) return 0;
	listNode<T>* p = head;
	while(p->next != q) p = p->next;
	p->next = q->next;
	delete q;
	return 1;
}
template <typename T> bool linkList<T>::cleanLink()
{
	listNode<T>* currentP;
	while(head->next != NULL)
	{
		currentP = head->next;
		head->next = currentP->next;
		delete currentP;
	}
	return true;
}
template <typename T> listNode<T>* linkList<T>::findNode(T q)
{
	listNode<T>* p = head;
	while(p->data != q)
	{
		if(p->next == NULL) break;
		p=p->next;
	}
	if(p->data != q) return 0;
	return p;
}
#endif
