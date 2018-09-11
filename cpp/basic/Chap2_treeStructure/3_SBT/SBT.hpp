#ifndef _SBT_H
#define _SBT_H

#include <iostream>
#include <list>
#include <vector>
#include <list>
#include <memory>

#define pSBTNode std::shared_ptr<SBTNode<T>>

template <typename T> class SBT;

template <typename T> class SBTNode
{
public:
    SBTNode()
    {
        data   = std::make_shared<T>(-9999999);
        lChild = rChild = parent = predecessor = successor =NULL;
    }
    explicit SBTNode(T newData)
    {
        data   = std::make_shared<T>(newData);
        lChild = rChild = parent = predecessor = successor =NULL;
    }

    ~SBTNode() {}

    void setData(T newData) {data   = std::make_shared<T>(newData);}
    T getData() {return *data;}
    pSBTNode getLChild() {return lChild;}
    pSBTNode getRChild() {return rChild;}
    pSBTNode getParent() {return parent;}
    std::shared_ptr<SBTNode<T>> getPredecessor() {return predecessor;}
    std::shared_ptr<SBTNode<T>> getSucessor() {return successor;}

    pSBTNode predecessor,successor;

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
        root = std::shared_ptr<SBTNode<T>>();
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
    void insertNode(pSBTNode& node);
    void deleteNode(pSBTNode node);

    void inOrder(std::vector<std::shared_ptr<SBTNode<T> > > &l, pSBTNode node);

    void SBTTransPlant(pSBTNode be_replaced, pSBTNode replace);

    void changeIntoLinkedlist();
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

template <typename T> void SBT<T>::inOrder(std::vector<pSBTNode>& l,pSBTNode node)
{
    if (node != NULL)
    {
        inOrder(l,node->lChild);
        l.push_back(node);
        inOrder(l,node->rChild);
    }
}

template <typename T> void SBT<T>::insertNode(pSBTNode& node)
{
    if (*(root->data) == -9999999)
    {
        *(root->data) = *(node->data);
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
    while (node->getRChild() != NULL)node = node -> getRChild();
    return node;
}

template <typename T> std::shared_ptr<SBTNode<T>> SBTFindSuccessor(std::shared_ptr<SBTNode<T>> node)
{
    if(node->getRChild() != NULL) return SBTFindMinimum(node->getRChild());
    while( node -> getParent() -> getLChild() != node)
    {
        node = node -> getParent();
        if(node->getParent() == NULL) return node;
    }
    return node -> getParent();
}

template <typename T> std::shared_ptr<SBTNode<T>> SBTFindPredecessor(std::shared_ptr<SBTNode<T>> node)
{
    if(node->getLChild() != NULL) return SBTFindMaximum(node->getLChild());
    while( node -> getParent() -> getRChild() != node)
    {
        node = node -> getParent();
        if(node->getParent() == NULL) return NULL;
    }
    return node -> getParent();
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

template <typename T> void SBT<T>::changeIntoLinkedlist()
{
    std::vector<pSBTNode> l;
    inOrder(l,root);
    for(int i = 0;i<l.size();++i)
    {
        if(i == l.size()-1)
        {
            l[i]->successor = NULL;
            return;
        }
        l[i]->successor = l[i+1];
        l[i+1]->predecessor = l[i];
    }
}
#endif

