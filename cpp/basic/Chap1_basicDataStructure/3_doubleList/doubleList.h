#ifndef _DOUBLELIST_H
#define _DOUBLELIST_H

#include <iostream>

template <typename T> class doubleListNode;

template <typename T> class doubleList
{
public:
	doubleList()
	{
		head = new doubleListNode<T>();
	}
	~doubleList()
	{
		delete head;
	}

	void insertNode(T newData);
	void insertNode(int loc , T newData);
	void removeNode(doubleListNode<T>* q);
	
	int getLength();
	doubleListNode<T>* findNode(int i);
	doubleListNode<T>* findData(T item);
	
	void clearAll();
	T getData(int i);
	
private:
	doubleListNode<T>* head;
};

template <typename T> class doubleListNode
{
public:
	doubleListNode()
	{
		next = NULL;
	}

	doubleListNode(T newData)
	{
		data = newData;
		next = NULL;
	}

	~doubleListNode()
	{
		next = NULL;
	}


	T getData(){return data;}
	doubleListNode<T>* getNext(){return next;}
	doubleListNode<T>* getPrior(){return prior;}

private:
	friend class doubleList<T>;
	doubleListNode<T>* next;
	doubleListNode<T>* prior;
	T data;
};

template <typename T> void doubleList<T>::insertNode(T newData)
{
	doubleListNode<T>* p = head;
	while(p->next != NULL)
	{
		p = p->next;
	}
	doubleListNode<T>* newNode = new doubleListNode<T>(newData);
	newNode->data=newData;
	p->next = newNode;
}

template <typename T> void doubleList<T>::insertNode(int loc , T newData)
{
	if(loc > this->getLength()){std::cout<<"out of range"<<std::endl;}
	doubleListNode<T>* newNode = new doubleListNode<T>(newData);
	newNode->data=newData;

	doubleListNode<T>* p = head;
	for (int i = 0; i < loc-1; ++i)
		{
			p=p->next;
		}
	newNode->next = p->next;
	p->next = newNode;
}

template <typename T> void doubleList<T>::removeNode(doubleListNode<T>* q)
{
	doubleListNode<T>* p = head;
	while(p->next != q)
	{
		if(p == NULL){
			std::cout<<"cant find node q"<<std::endl;
			return;
		}
		p = p->next;
	}

	p->next == q->next; 
	delete q;
}

template <typename T> int doubleList<T>::getLength()
{
	doubleListNode<T>* p = head;
	int i=0;
	while (p->next != NULL)
	{
		i++;
		p = p->next;
	}
	return i;
}

template <typename T> doubleListNode<T>* doubleList<T>::findNode(int i)
{
	doubleListNode<T>* p = head;
	if(i > this->getLength()) 
	{
		std::cout<<"out of range"<<std::endl;
		return 0;
	}
	int j=0;
	while (p->next != NULL)
	{
		j++;
		if(j == i) return p->next;
		p = p->next;
	}
}

template <typename T> doubleListNode<T>* doubleList<T>::findData(T item)
{
	doubleListNode<T>* p = head;
	while (p->next != NULL)
	{
		p = p->next;
		if(p->data == item)
		{
			return p;
		}
	}	
}

template <typename T> void doubleList<T>::clearAll()
{
	doubleListNode<T>* p;
	while(head->next !=NULL)
	{
		p = head->next;
		head->next = p->next;
		delete p;
	}
}

template <typename T> T doubleList<T>::getData(int i)
{
	doubleListNode<T>* p = this->findNode(i);
	return p->data;
}

#endif
