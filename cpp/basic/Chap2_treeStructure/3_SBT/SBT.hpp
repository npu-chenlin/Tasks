#ifndef _SBT_H
#define _SBT_H

#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;

template <typename T> class SBT;

template <typename T> class SBTNode
{
public:
    SBTNode()
    {
        data   = 0;
        lChild = rChild = parent = NULL;
    }
    explicit SBTNode(T newData)
    {
        data   = newData;
        lChild = rChild = parent = NULL;
    }

    ~SBTNode() {}

    void setData(T newData) {data = newData;}
    T getData() {return data;}
    SBTNode<T>* getLChild() {return lChild;}
    SBTNode<T>* getRChild() {return rChild;}
    SBTNode<T>* getParent() {return parent;}

private:
    friend class SBT<T>;
    T data;
    SBTNode<T>* lChild, *rChild, *parent;
};

template <typename T> class SBT
{
public:
    SBT()
    {
        root = new SBTNode<T>();
    }
    explicit SBT(T newData)
    {
        root = new SBTNode<T>(newData);
    }
    ~SBT()
    {
        if ( root )
        {
            delete root;
            root = NULL;
        }

    }

    void inOrder(SBTNode<T>* node);
    void insertNode(SBTNode<T>* node);
    void deleteNode(SBTNode<T>* node);
    SBTNode<T>* getRoot() {return root;}

private:
    SBTNode<T>* root;
};

template <typename T> void SBT<T>::inOrder(SBTNode<T>* node)
{
    if (node != NULL)
    {
        inOrder(node->lChild);
        cout << node->data << endl;
        inOrder(node->rChild);
    }
}

template <typename T> void SBT<T>::insertNode(SBTNode<T>* node)
{
    if (root->data == 0)
    {
        root->data = node->data;
        return;
    }

    SBTNode<T>* cur, * temp = root;

    while (temp != NULL)
    {
        cur = temp;
        if (node->data < temp->data)
        {
            temp = temp->lChild;
        }
        else
        {
            temp = temp->rChild;
        }
    }

    node->parent = cur;
    if (node->data < cur->data)
    {
        cur->lChild = node;
    }
    else
        cur->rChild = node;
}

template <typename T> void SBT<T>::deleteNode(SBTNode<T>* node)
{
    SBTNode<T>* p = node->parent;
    if (!node->lChild && !node->rChild)
    {
        if (node->data < p->data)
        {
            p->lChild = NULL;
        }
        else
            p->rChild = NULL;


    }
    else if (node->lChild && !node->rChild)
    {
        if (p == NULL)
        {
            root = node->lChild;
            node->parent = NULL;

            return;
        }
        node->lChild->parent = p;
        if (node == p->lChild)
        {
            p->lChild = node->lChild;
        }
        else
            p->rChild = node->lChild;

        return;
    }
    else if (node->rChild && !node->lChild)
    {
        if (p == NULL)
        {
            root = node->rChild;
            node->parent = NULL;

            return;
        }
        node->rChild->parent = p;
        if (node == p->rChild)
        {
            p->rChild = node->rChild;
        }
        else
            p->lChild = node->rChild;

        return;
    }
    else
    {
        if (p == NULL)
        {
            SBTNode<T>* temp = node->lChild;
            while (temp->rChild)
            {
                temp = temp -> rChild;
            }
            root = temp;
            temp->parent->rChild = temp->lChild;
            temp->parent = p;
            if (temp->lChild)
            {
                temp->lChild->parent = temp->parent;
            }
            temp->lChild = node->lChild;
            temp->rChild = node->rChild;
            return;
        }
        SBTNode<T>* temp = node->lChild;
        while (temp->rChild)
        {
            temp = temp -> rChild;
        }
        temp->parent->rChild = temp->lChild;
        temp->parent = p;
        if (temp->lChild)
        {
            temp->lChild->parent = temp->parent;
        }
        temp->lChild = node->lChild;
        temp->rChild = node->rChild;
    }

}

#endif
