#ifndef _SBT_H
#define _SBT_H

#include <iostream>
#include <list>
#include <vector>
#include <memory>

#define pSBTNode std::shared_ptr<SBTNode<T> >

template <typename T> class SBT;

template <typename T> class SBTNode
{
public:
    SBTNode()
    {
        data   = NULL;
        lChild = rChild = parent = NULL;
    }
    explicit SBTNode(T newData)
    {
        data   = std::make_shared<T>(newData);
        lChild = rChild = parent = NULL;
    }

    ~SBTNode() {}

    void setData(T newData) {data   = std::make_shared<T>(newData);}
    T getData() {return *data;}
    pSBTNode getLChild() {return lChild;}
    pSBTNode getRChild() {return rChild;}
    pSBTNode getParent() {return parent;}

private:
    friend class SBT<T>;
    std::shared_ptr<T> data;
    pSBTNode lChild, rChild, parent;
};

template <typename T> class SBT
{
public:
    SBT()
    {
        root = pSBTNode();
    }
    explicit SBT(T newData)
    {
        root = pSBTNode(new SBTNode<T>(newData));
    }
    ~SBT()
    {
        if ( root )
        {
            root = NULL;
        }
    }

    pSBTNode getRoot() {return root;}

    void add(T newData);
    void del(T Data);
    void insertNode(pSBTNode node);
    void deleteNode(pSBTNode node);

    void inOrder(pSBTNode node);

    void SBTTransPlant(pSBTNode be_replaced, pSBTNode replace);

private:
        pSBTNode root;
};

template <typename T> pSBTNode SBTSearch(pSBTNode node, T data)
{
    if(data > node->getData()) return SBTSearch(node->getRChild(),data);
    else if(data < node->getData()) return SBTSearch(node->getLChild(),data);
    else return node;
}

template <typename T> void SBT<T>::add(T newData)
{
    pSBTNode p(new SBTNode<T>(newData));
    insertNode(p);
}

template <typename T> void SBT<T>::del(T Data)
{
    deleteNode(SBTSearch(root,Data));
}

template <typename T> void SBT<T>::inOrder(pSBTNode node)
{
    if (node != NULL)
    {
        inOrder(node->lChild);
        std::cout << *(node->data) << std::endl;
        inOrder(node->rChild);
    }
}

template <typename T> void SBT<T>::insertNode(pSBTNode node)
{
    if (root->data == NULL)
    {
        root->data = node->data;
        return;
    }

    pSBTNode cur, temp = root;

    while (temp != NULL)
    {
        cur = temp;
        if (*(node->data) < *(temp->data))
        {
            temp = temp->lChild;
        }
        else
        {
            temp = temp->rChild;
        }
    }

    node->parent = cur;
    if (*(node->data) < *(cur->data))
    {
        cur->lChild = node;
    }
    else
        cur->rChild = node;
}

template <typename T> pSBTNode SBTFindMinimum(pSBTNode node)
{
    while (node->getLChild() != NULL)node = node -> getLChild();
    return node;
}

template <typename T> pSBTNode SBTFindMaximum(pSBTNode node)
{
    while (node->getRChild() != NULL)node = node -> rChild;
    return node;
}

template <typename T> pSBTNode SBTFindSuccessor(pSBTNode node)
{
    if(node->rChild) return SBTFindMinimum(node->rChild);
    while( node -> parent -> lChild != node)
    {
        node = node -> parent;
        if(node = NULL) return node;
    }
    return node -> parent;
}

template <typename T> void SBT<T>::SBTTransPlant(pSBTNode be_replaced,pSBTNode replace)
{

    if (be_replaced->parent == NULL ) root = replace;
    else if ( be_replaced->parent->lChild == be_replaced) replace->parent->lChild = replace;
    else be_replaced->parent->rChild = replace;
    if(replace != NULL)
        replace->parent = be_replaced -> parent;
}

template <typename T> void SBT<T>::deleteNode(pSBTNode node)
{
    pSBTNode p = node->parent;

    if (node->lChild == NULL)
    {
        SBTTransPlant(node,node->rChild);
    }
    else if (node->rChild == NULL)
    {
        SBTTransPlant(node,node->lChild);
    }
    else
    {
        pSBTNode y = SBTFindMinimum(node->rChild);
        node->data = y->data;
        SBTTransPlant(y,y->rChild);
    }
}

#endif

