#ifndef _RBT_H
#define _RBT_H

#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;

template <typename T> class RBT;

template <typename T> class RBTNode
{
public:
    RBTNode()
    {
        data   = NULL;
        lChild = rChild = parent = NULL;
        color  = true;
    }
    explicit RBTNode(T newData, bool color = true)
    {
        data   = newData;
        lChild = rChild = parent = NULL;
        this->color  = color;
    }

    ~RBTNode() {}

    void setData(T newData) {data = newData;}
    T getData() {return data;}
    void setColor(bool color) {this->color = color;}
    RBTNode<T>* getLChild() {return lChild;}
    RBTNode<T>* getRChild() {return rChild;}
    RBTNode<T>* getParent() {return parent;}

private:
    friend class RBT<T>;
    T data;
    RBTNode<T> *lChild, *rChild, *parent;
    bool color; //Black is 0, red is 1;
};

template <typename T> class RBT
{
public:
    RBT()
    {
        root  = NULL;
        count = 0;
    }
    explicit RBT(T newData)
    {
        root = RBTNode<T>(newData, false);
        count = 0;
    }
    ~RBT()
    {
        root = NULL;

    }

    void insertNode(RBTNode<T>* node);
    void deleteNode(RBTNode<T>* node);

    void insertKeepRBT(RBTNode<T>* node);
    void leftRotated(RBTNode<T>* node);
    void rightRotated(RBTNode<T>* node);

private:
    RBTNode<T>* root;
    int count; //number of nodes
};

template <typename T> void RBT<T>::insertNode(RBTNode<T>* node)
{
    if (!root)
    {
        root = node;
        root->color = false;
        return;
    }
    ++count;
    RBTNode<T>* cur, * temp = root;

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

template <typename T> void RBT<T>::deleteNode(RBTNode<T>* node)
{
    RBTNode<T>* p = node->parent;
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
            RBTNode<T>* temp = node->lChild;
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
        RBTNode<T>* temp = node->lChild;
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

template <typename T> void RBT<T>::leftRotated(RBTNode<T> *node)
{
    if (node->parent == NULL)
    {
        node->rChild->parent = NULL;
    }
    else
    {
        node->rChild->parent = node->parent;
        if (node->parent->lChild == node) node->parent->lChild = node->rChild;
        else node->parent->rChild = node->rChild;
    }

    node->parent = node->rChild;

    if (node->rChild->lChild)
    {
        node->rChild->lChild->parent = node;
        node->rChild                 = node->rChild->lChild;
    }
    node->parent->lChild = node;
}

template <typename T> void RBT<T>::rightRotated(RBTNode<T> *node)
{
    if (node->parent == NULL)
    {
        node->lChild->parent = NULL;
    }
    else
    {
        node->lChild->parent = node->parent;
        if (node->parent->lChild == node) node->parent->lChild = node->lChild;
        else node->parent->rChild = node->lChild;
    }

    node->parent = node->lChild;

    if (node->lChild->rChild)
    {
        node->lChild->rChild->parent = node;
        node->lChild = node->lChild->rChild;
    }
    node->parent->rChild = node;
}

template <typename T> void RBT<T>::insertKeepRBT(RBTNode<T> *node)
{
    

}

#endif //end of _RBT_H
