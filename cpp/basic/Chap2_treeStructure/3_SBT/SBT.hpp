#ifndef _SBT_H
#define _SBT_H

#include <iostream>
#include <list>
#include <vector>

// FIXME: it is better to avoid using namespace in header
using std::cout;
using std::endl;

#include <memory>

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
    std::shared_ptr<SBTNode<T>> getLChild() {return lChild;}
    std::shared_ptr<SBTNode<T>> getRChild() {return rChild;}
    std::shared_ptr<SBTNode<T>> getParent() {return parent;}

private:
    friend class SBT<T>;
    T data;
    std::shared_ptr<SBTNode<T>> lChild, rChild, parent;
};

template <typename T> class SBT
{
public:
    SBT()
    {
        root = std::make_shared<SBTNode<T>>();
    }
    explicit SBT(T newData)
    {
        root = std::make_shared<SBTNode<T>>(newData);
    }
    ~SBT()
    {
        if ( root )
        {
            root = NULL;
        }

    }

<<<<<<< HEAD
    void inOrder(SBTNode<T>* node);
    void insertNode(SBTNode<T>* node); // FIXME: the function can be change to 
    void insertNode(const T& v);      //         will be better, user do not care the SBTNode class
    void deleteNode(SBTNode<T>* node);
    SBTNode<T>* getRoot() {return root;}
=======
    std::shared_ptr<SBTNode<T>> getRoot() {return root;}
    void insertNode(std::shared_ptr<SBTNode<T>> node);
    void deleteNode(std::shared_ptr<SBTNode<T>> node);

    void inOrder(std::shared_ptr<SBTNode<T>> node);

    void SBTTransPlant(std::shared_ptr<SBTNode<T> > be_replaced, std::shared_ptr<SBTNode<T> > replace);
    void search();
>>>>>>> b49e028c63a53c07002eaaa2051f67b40f338a1f

private:
        std::shared_ptr<SBTNode<T>> root;
};

template <typename T> void SBT<T>::inOrder(std::shared_ptr<SBTNode<T>> node)
{
    if (node != NULL)
    {
        inOrder(node->lChild);
        std::cout << node->data << std::endl;
        inOrder(node->rChild);
    }
}

template <typename T> void SBT<T>::insertNode(std::shared_ptr<SBTNode<T>> node)
{
    if (root->data == 0)
    {
        root->data = node->data;
        return;
    }

    std::shared_ptr<SBTNode<T>> cur, temp = root;

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

template <typename T> std::shared_ptr<SBTNode<T>> SBTFindMinimum(std::shared_ptr<SBTNode<T>> node)
{
    while (node->getLChild() != NULL)node = node -> getLChild();
    return node;
}

template <typename T> std::shared_ptr<SBTNode<T>> SBTFindMaximum(std::shared_ptr<SBTNode<T>> node)
{
    while (node->getRChild() != NULL)node = node -> rChild;
    return node;
}

template <typename T> std::shared_ptr<SBTNode<T>> SBTFindSuccessor(std::shared_ptr<SBTNode<T>> node)
{
    if(node->rChild) return SBTFindMinimum(node->rChild);
    while( node -> parent -> lChild != node)
    {
        node = node -> parent;
        if(node = NULL) return node;
    }
    return node -> parent;
}

template <typename T> void SBT<T>::SBTTransPlant(std::shared_ptr<SBTNode<T>> be_replaced,std::shared_ptr<SBTNode<T>> replace)
{

    if (be_replaced->parent == NULL ) root = replace;
    else if ( be_replaced->parent->lChild == be_replaced) replace->parent->lChild = replace;
    else be_replaced->parent->rChild = replace;
    if(replace != NULL)
        replace->parent = be_replaced -> parent;
}

template <typename T> void SBT<T>::deleteNode(std::shared_ptr<SBTNode<T>> node)
{
    std::shared_ptr<SBTNode<T>> p = node->parent;

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
        std::shared_ptr<SBTNode<T>> y = SBTFindMinimum(node->rChild);
        node->data = y->data;
        SBTTransPlant(y,y->rChild);
    }
}

#endif
