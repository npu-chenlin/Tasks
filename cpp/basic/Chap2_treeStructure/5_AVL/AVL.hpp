#ifndef _AVL_H
#define _AVL_H

#include <iostream>
#include <list>
#include <cmath>
#include <memory>

template <typename T> class AVL;

template <typename T> class AVLNode
{
public:
    AVLNode()
    {
        data   = 0;
        h      = 0;
        lChild = rChild = parent = NULL;
    }
    explicit AVLNode(T newData)
    {
        data   = newData;
        h      = 1;
        lChild = rChild = parent = AVLNode<T>::nil;
    }

    ~AVLNode() {}

    static std::shared_ptr<AVLNode<T>> nil;

    void setData(T newData) {data = newData;}
    void setH(int height) {h = height;}
    T getData() {return data;}
    int getH() {return h;}

    std::shared_ptr<AVLNode<T>> getLChild() {return lChild;}
    std::shared_ptr<AVLNode<T>> getRChild() {return rChild;}
    std::shared_ptr<AVLNode<T>> getParent() {return parent;}

private:
    friend class AVL<T>;
    T data;
    int h;
    std::shared_ptr<AVLNode<T>> lChild, rChild, parent;
};

template <typename T> std::shared_ptr<AVLNode<T>> AVLNode<T>::nil = std::make_shared<AVLNode<T>>();

template <typename T> class AVL
{
public:
    AVL()
    {
        root = AVLNode<T>::nil;
    }
    explicit AVL(T newData)
    {
        root = std::make_shared<AVLNode<T>>(newData);
    }
    ~AVL()
    {
        root = AVLNode<T>::nil;
    }

    std::shared_ptr<AVLNode<T>> getRoot() {return root;}
    void insertNode(std::shared_ptr<AVLNode<T>> node);
    void deleteNode(std::shared_ptr<AVLNode<T>> node);

    void insertKeepAVL(std::shared_ptr<AVLNode<T>> node);
    void deleteKeepAVL(std::shared_ptr<AVLNode<T>> node);

    void leftRotated(std::shared_ptr<AVLNode<T>> node);
    void rightRotated(std::shared_ptr<AVLNode<T>> node);
    void leftRightRotated(std::shared_ptr<AVLNode<T>> node);
    void rightLeftRotated(std::shared_ptr<AVLNode<T>> node);

    void inOrder(std::shared_ptr<AVLNode<T>> node);

    void AVLTransPlant(std::shared_ptr<AVLNode<T> > be_replaced, std::shared_ptr<AVLNode<T> > replace);

private:
        std::shared_ptr<AVLNode<T>> root;
};
template <typename T> std::shared_ptr<AVLNode<T>> AVLFindMinimum(std::shared_ptr<AVLNode<T>> node)
{
    while (node->getLChild() != AVLNode<T>::nil)node = node -> getLChild();
    return node;
}

template <typename T> std::shared_ptr<AVLNode<T>> AVLFindMaximum(std::shared_ptr<AVLNode<T>> node)
{
    while (node->getRChild() != AVLNode<T>::nil)node = node -> rChild;
    return node;
}

template <typename T> std::shared_ptr<AVLNode<T>> AVLFindSuccessor(std::shared_ptr<AVLNode<T>> node)
{
    if(node->rChild) return AVLFindMinimum(node->rChild);
    while( node -> parent -> lChild != node)
    {
        node = node -> parent;
        if(node = AVLNode<T>::nil) return node;
    }
    return node -> parent;
}

template <typename T> void AVLRefreshHeight(std::shared_ptr<AVLNode<T>> node)
{
    node->setH(std::max(node->getLChild()->getH(),node->getRChild()->getH()) + 1);
}

template <typename T> void AVL<T>::inOrder(std::shared_ptr<AVLNode<T>> node)
{
    if (node != AVLNode<T>::nil)
    {
        inOrder(node->lChild);
        std::cout << node->data<<" "<<std::abs(node->lChild->h - node->rChild->h) << std::endl;
        inOrder(node->rChild);
    }
}

template <typename T> void AVL<T>::insertNode(std::shared_ptr<AVLNode<T>> node)
{
    if (root->data == 0)
    {
        root->data = node->data;
        return;
    }

    std::shared_ptr<AVLNode<T>> cur, temp = root;

    while (temp != AVLNode<T>::nil)
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
    /*
     * refresh tree height
     */
    temp = node->parent;
    while(temp != AVLNode<T>::nil)
    {
        temp->h = std::max(temp->lChild->h,temp->rChild->h)+1;
        temp = temp->parent;
    }

    insertKeepAVL(node);
}

template <typename T> void AVL<T>::AVLTransPlant(std::shared_ptr<AVLNode<T>> be_replaced,std::shared_ptr<AVLNode<T>> replace)
{

    if (be_replaced->parent == AVLNode<T>::nil ) root = replace;
    else if ( be_replaced->parent->lChild == be_replaced) be_replaced->parent->lChild = replace;
    else be_replaced->parent->rChild = replace;
    if(replace != AVLNode<T>::nil)
    {
        replace->parent = be_replaced -> parent;

        while(true)
        {
            be_replaced = be_replaced->parent;
            if(be_replaced != AVLNode<T>::nil)
            {
                be_replaced->h = std::max(be_replaced->lChild->h,be_replaced->rChild->h) + 1;
            }
            else
                break;
        }
    }
}

template <typename T> void AVL<T>::deleteNode(std::shared_ptr<AVLNode<T>> node)
{
    if (node->lChild == AVLNode<T>::nil)
    {
        AVLTransPlant(node,node->rChild);
    }
    else if (node->rChild == AVLNode<T>::nil)
    {
        AVLTransPlant(node,node->lChild);
    }
    else
    {
        std::shared_ptr<AVLNode<T>> y = AVLFindMinimum(node->rChild);
        node->data = y->data;
        node = y;
        AVLTransPlant(node,node->rChild);
    }

    std::shared_ptr<AVLNode<T>> p = node->parent;
    while (p != AVLNode<T>::nil)
    {
        AVLRefreshHeight(p);
        p = p->parent;
    }

    deleteKeepAVL(node->parent);
}

template <typename T> void AVL<T>::leftRotated(std::shared_ptr<AVLNode<T>> node)
{
    if (node->parent == AVLNode<T>::nil)
    {
        node->rChild->parent = AVLNode<T>::nil;
        root = node->rChild;
    }
    else
    {
        node->rChild->parent = node->parent;
        if (node->parent->lChild == node) node->parent->lChild = node->rChild;
        else node->parent->rChild = node->rChild;
    }

    node->parent = node->rChild;

    if (node->rChild->lChild != AVLNode<T>::nil)
    {
        node->rChild->lChild->parent = node;
    }
    node->rChild = node->rChild->lChild;
    node->parent->lChild = node;

    while (node != AVLNode<T>::nil)
    {
        AVLRefreshHeight(node);
        node = node->parent;
    }
}

template <typename T> void AVL<T>::rightRotated(std::shared_ptr<AVLNode<T>> node)
{
    if (node->parent == AVLNode<T>::nil)
    {
        node->lChild->parent = AVLNode<T>::nil;
        root = node->lChild;
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
    }

    node->lChild = node->lChild->rChild;
    node->parent->rChild = node;

    while (node != AVLNode<T>::nil)
    {
        AVLRefreshHeight(node);
        node = node->parent;
    }
}

template <typename T> void AVL<T>::rightLeftRotated(std::shared_ptr<AVLNode<T>> node)
{
    rightRotated(node->rChild);
    leftRotated(node);
}

template <typename T> void AVL<T>::leftRightRotated(std::shared_ptr<AVLNode<T>> node)
{
    leftRotated(node->lChild);
    rightRotated(node);
}

template <typename T> void AVL<T>::insertKeepAVL(std::shared_ptr<AVLNode<T>> node)
{
    int value = node->data;
    while(node->parent != AVLNode<T>::nil)
    {
        if(std::abs(node->parent->lChild->h - node->parent->rChild->h) == 2)
        {
            if(value > node->parent->data)
            {
                if(value > node->data) leftRotated(node->parent);
                else rightLeftRotated(node->parent);
            }
            else
            {
                if(value > node->data) leftRightRotated(node->parent);
                else rightRotated(node->parent);
            }
            return;
        }
        node = node->parent;
    }
}

template <typename T> void AVL<T>::deleteKeepAVL(std::shared_ptr<AVLNode<T>> node)
{

}

#endif
