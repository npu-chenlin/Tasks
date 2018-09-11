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
        lChild = rChild = parent = predecessor = successor =AVLNode<T>::nil;
    }
    explicit AVLNode(T newData)
    {
        data   = newData;
        h      = 1;
        lChild = rChild = parent = predecessor = successor =AVLNode<T>::nil;
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
    std::shared_ptr<AVLNode<T>> getPredecessor() {return predecessor;}
    std::shared_ptr<AVLNode<T>> getSucessor() {return successor;}

private:
    friend class AVL<T>;
    T data;
    int h;
    std::shared_ptr<AVLNode<T>> lChild, rChild, parent ,predecessor,successor;
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
    void addNode(T newData);
    void del(T Data);
    void insertNode(std::shared_ptr<AVLNode<T> > &node);
    void deleteNode(std::shared_ptr<AVLNode<T>> node);

    void insertKeepAVL(std::shared_ptr<AVLNode<T>> node);
    void deleteKeepAVL(std::shared_ptr<AVLNode<T>> node);

    void leftRotated(std::shared_ptr<AVLNode<T>> node);
    void rightRotated(std::shared_ptr<AVLNode<T>> node);
    void leftRightRotated(std::shared_ptr<AVLNode<T>> node);
    void rightLeftRotated(std::shared_ptr<AVLNode<T>> node);

    void inOrder(std::shared_ptr<AVLNode<T>> node);
    void preOrder(std::shared_ptr<AVLNode<T>> node);

    void AVLTransPlant(std::shared_ptr<AVLNode<T> > be_replaced, std::shared_ptr<AVLNode<T> > replace);

    void changeIntoLinkedlist(std::shared_ptr<AVLNode<T>> node);
private:
        std::shared_ptr<AVLNode<T>> root;
};

template <typename T> int getBlanceFactor(std::shared_ptr<AVLNode<T>> node)
{
    if(node != AVLNode<T>::nil)
    return node->getRChild()->getH() - node->getLChild()->getH();
    else return 0;
}

template <typename T> std::shared_ptr<AVLNode<T>> AVLSearch(std::shared_ptr<AVLNode<T>> node , T data)
{
    if(data > node->getData()) return AVLSearch(node->getRChild(),data);
    else if(data < node->getData()) return AVLSearch(node->getLChild(),data);
    else return node;
}

template <typename T> std::shared_ptr<AVLNode<T>> AVLFindMinimum(std::shared_ptr<AVLNode<T>> node)
{
    while (node->getLChild() != AVLNode<T>::nil)node = node -> getLChild();
    return node;
}

template <typename T> std::shared_ptr<AVLNode<T>> AVLFindMaximum(std::shared_ptr<AVLNode<T>> node)
{
    while (node->getRChild() != AVLNode<T>::nil)node = node -> getRChild();
    return node;
}

template <typename T> std::shared_ptr<AVLNode<T>> AVLFindSuccessor(std::shared_ptr<AVLNode<T>> node)
{
    if(node->getRChild() != AVLNode<T>::nil) return AVLFindMinimum(node->getRChild());
    while( node -> getParent() -> getLChild() != node)
    {
        node = node -> getParent();
        if(node == AVLNode<T>::nil) return node;
    }
    return node -> getParent();
}

template <typename T> std::shared_ptr<AVLNode<T>> AVLFindPredecessor(std::shared_ptr<AVLNode<T>> node)
{
    if(node->getLChild() != AVLNode<T>::nil) return AVLFindMaximum(node->getLChild());
    while( node -> getParent() -> getRChild() != node)
    {
        node = node -> getParent();
        if(node == AVLNode<T>::nil) return node;
    }
    return node -> getParent();
}

template <typename T> void AVLRefreshHeight(std::shared_ptr<AVLNode<T>> node)
{
    if(!node->getLChild() && node->getRChild()) {node->setH(node->getRChild()->getH() + 1);return;}
    else if(!node->getRChild() && node->getLChild()) {node->setH(node->getLChild()->getH() + 1);return;}
    else if(!node->getRChild() && !node->getLChild()) node->setH(1);
    else
        node->setH(std::max(node->getLChild()->getH(),node->getRChild()->getH()) + 1);
}

template <typename T> void AVL<T>::preOrder(std::shared_ptr<AVLNode<T>> node)
{
    if (node != AVLNode<T>::nil)
    {
        std::cout << node->data<<" ";
        preOrder(node->lChild);
        preOrder(node->rChild);
    }
}

template <typename T> void AVL<T>::addNode(T newData)
{
    std::shared_ptr<AVLNode<T>> p(new AVLNode<T>(newData));
    insertNode(p);
}

template <typename T> void AVL<T>::del(T Data)
{
    deleteNode(AVLSearch(root,Data));
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

template <typename T> void AVL<T>::insertNode(std::shared_ptr<AVLNode<T>>& node)
{
    if (root == AVLNode<T>::nil)
    {
        root = node;
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
    if(std::abs(getBlanceFactor(node)) == 0)
    {
        while (node != AVLNode<T>::nil)
        {
            node = node ->parent;
            if((std::abs(getBlanceFactor(node))) == 2)
            {
                deleteKeepAVL(node);
                break;
            }
        }
    }
    else if(getBlanceFactor(node) == 2) //Means deleted node is at left
    {
        if(getBlanceFactor(node->rChild) == 0 || getBlanceFactor(node->rChild) == -1)
        {
            leftRotated(node);
        }
        else if(getBlanceFactor(node->rChild) == 1)
        {
            leftRightRotated(node);
        }
    }
    else if(getBlanceFactor(node) == -2)//deleted node is at right
    {
        if(getBlanceFactor(node->lChild) == 0 || getBlanceFactor(node->lChild) == 1)
        {
            rightRotated(node);
        }
        else if(getBlanceFactor(node->rChild) == 1)
        {
            rightLeftRotated(node);
        }
    }
}

template <typename T> void AVL<T>::changeIntoLinkedlist(std::shared_ptr<AVLNode<T>> node)
{
    if (node != AVLNode<T>::nil)
    {
        changeIntoLinkedlist(node->lChild);
        node->predecessor = AVLFindPredecessor(node);
        node->successor = AVLFindSuccessor(node);
        changeIntoLinkedlist(node->rChild);
    }
}

#endif
