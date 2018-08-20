#ifndef _RBT_H
#define _RBT_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <memory>

template <typename T> class RBTNode;

template <typename T> class RBT
{
public:
    RBT()
    {
        root  = RBTNode<T>::nil;
        count = 0;
    }
    explicit RBT(T newData)
    {
        root  = std::make_shared<RBTNode<T>>(newData, false);
        count = 0;
    }
    ~RBT()
    {
        root = NULL;
    }

    void insertNode(std::shared_ptr<RBTNode<T>> node);
    bool deleteNode(T data);

    void insertKeepRBT(std::shared_ptr<RBTNode<T>> node);
    void deleteKeepRBT(std::shared_ptr<RBTNode<T>> node);

    void leftRotated(std::shared_ptr<RBTNode<T>> node);
    void rightRotated(std::shared_ptr<RBTNode<T>> node);

    std::shared_ptr<RBTNode<T>> getRoot() {return root;}
    void inOrder(std::shared_ptr<RBTNode<T>> node);
    void preOrder(std::shared_ptr<RBTNode<T>> node);

private:
    std::shared_ptr<RBTNode<T>> root;
    int count; //number of nodes
};

template <typename T> class RBTNode
{
public:
    RBTNode()
    {
        data   = 0;
        lChild = rChild = parent = NULL;
        color  = false;
    }
    explicit RBTNode(T newData, bool color = true)
    {
        data   = newData;
        lChild = rChild = parent = nil;
        this->color  = color;
    }
    ~RBTNode() {
        lChild = rChild = parent = NULL;
    }

    static std::shared_ptr<RBTNode<T>> nil;

    void setData(T newData) {data = newData;}
    T getData() {return data;}
    std::string getColor()
    {
        if (color) return "red";
        else return "black";
    }
    void setColor(bool color) {this->color = color;}
    std::shared_ptr<RBTNode<T>> getLChild() {return lChild;}
    std::shared_ptr<RBTNode<T>> getRChild() {return rChild;}
    std::shared_ptr<RBTNode<T>> getParent() {return parent;}

private:
    friend class RBT<T>;
    template <typename TT> friend std::shared_ptr<RBTNode<TT>> findUncle(std::shared_ptr<RBTNode<TT>>);

    T data;
    std::shared_ptr<RBTNode<T>> lChild, rChild, parent;
    bool color; //Black is 0, red is 1;
};
template <typename T> std::shared_ptr<RBTNode<T>> RBTNode<T>::nil = std::make_shared<RBTNode<T>>();

template <typename T> std::shared_ptr<RBTNode<T>> findUncle(std::shared_ptr<RBTNode<T>> node)
{
    if (node->parent == RBTNode<T>::nil) return NULL;
    if (node->parent->parent->lChild == node->parent) return node->parent->parent->rChild;
    else return node->parent->parent->lChild;
}

template <typename T> void RBT<T>::insertNode(std::shared_ptr<RBTNode<T>> node)
{
    ++count;
    if (root == RBTNode<T>::nil)
    {
        root = node;
        return;
    }

    std::shared_ptr<RBTNode<T>> cur, temp = root;
    while (temp != RBTNode<T>::nil)
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

    insertKeepRBT(node);
}

template <typename T> bool RBT<T>::deleteNode(T data)
{
    std::shared_ptr<RBTNode<T>> node = root;
    while (node->data != data)
    {
        node = node->data > data ? node->lChild : node->rChild;
        if (node == RBTNode<T>::nil) return false;
    }

    std::shared_ptr<RBTNode<T>> p = node->parent;
    /**
     * If the deleted node is balck
     */
    if (node->color == false)
    {
        /**
         * If the node has no child.
         */
        if ( node->lChild == RBTNode<T>::nil && node->rChild == RBTNode<T>::nil)
        {
            if (p == RBTNode<T>::nil)
            {
                root = p;
                return true;
            }
            deleteKeepRBT(node);
            if (data < p->data)
            {
                p->lChild = RBTNode<T>::nil;
            }
            else
                p->rChild = RBTNode<T>::nil;

            return true;
        }
        else if ((node->lChild == RBTNode<T>::nil) != (node->rChild == RBTNode<T>::nil))
        {
            std::shared_ptr<RBTNode<T>> next = (node->lChild == RBTNode<T>::nil) ? node->rChild : node->lChild;
            next->color = false;
            if (p == RBTNode<T>::nil)
            {
                root = next;
                next->parent = RBTNode<T>::nil;
                return true;
            }
            next->parent = p;
            if (node == p->lChild)
            {
                p->lChild = next;
            }
            else
                p->rChild = next;

            return true;
        }

        else
        {
            std::shared_ptr<RBTNode<T>> temp = node->rChild;
            while (temp->lChild != RBTNode<T>::nil)
            {
                temp = temp -> lChild;
            }
            T tempData = temp->data;
            this->deleteNode(temp->data);
            node->data = temp->data;
            return true;
        }
    }

    /**
     * If the deleted node is red
     */
    else
    {
        /**
         * If the node doesn't have any child
         */
        if ( node->lChild == RBTNode<T>::nil && node->rChild == RBTNode<T>::nil)
        {
            if (data < p->data)
            {
                p->lChild = RBTNode<T>::nil;
            }
            else
                p->rChild = RBTNode<T>::nil;
            return true;
        }
        /**
         * It is imposible that the node only has one child(according to RBT defination).
         * If the node has both children.
         */
        else
        {
            std::shared_ptr<RBTNode<T>> temp = node->rChild;
            while (temp->lChild != RBTNode<T>::nil)
            {
                temp = temp -> lChild;
            }
            T tempData = temp->data;
            this->deleteNode(temp->data);
            node->data = temp->data;
            return true;
        }
    }
}

template <typename T> void RBT<T>::deleteKeepRBT(std::shared_ptr<RBTNode<T>> node)
{
    findUncle(node)
}

template <typename T> void RBT<T>::leftRotated(std::shared_ptr<RBTNode<T>> node)
{
    if (node->parent == RBTNode<T>::nil)
    {
        node->rChild->parent = RBTNode<T>::nil;
        root = node->rChild;
    }
    else
    {
        node->rChild->parent = node->parent;
        if (node->parent->lChild == node) node->parent->lChild = node->rChild;
        else node->parent->rChild = node->rChild;
    }

    node->parent = node->rChild;

    if (node->rChild->lChild != RBTNode<T>::nil)
    {
        node->rChild->lChild->parent = node;
    }
    node->rChild = node->rChild->lChild;
    node->parent->lChild = node;
}

template <typename T> void RBT<T>::rightRotated(std::shared_ptr<RBTNode<T>> node)
{
    if (node->parent == RBTNode<T>::nil)
    {
        node->lChild->parent = RBTNode<T>::nil;
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
}

template <typename T> void RBT<T>::insertKeepRBT(std::shared_ptr<RBTNode<T>> node)
{
    /**
     * Current node is root
     */
    if (node->parent == RBTNode<T>::nil)
    {
        node->color = false;
        return;
    }
    /**
     * Current node is red
     */
    if (node->parent->color == true)
    {
        /**
         * Current node 's father node is red while uncle is also red.
         */
        if (findUncle(node)->color == true)
        {
            node->parent->parent->color = true;
            node->parent->color = false;
            findUncle(node)->color = false;

            insertKeepRBT(node->parent->parent);
        }
        else if (node->parent == node->parent->parent->rChild) //node's parent node is node's grand node's right child
        {
            /**
              * Current node is its father's right child while uncle is black
              */
            if (node == node->parent->rChild && findUncle(node)->color == false )
            {
                node->parent->color = false;
                node->parent->parent->color = true;
                leftRotated(node->parent->parent);
            }

            /**
              * Current node is its father's left child while uncle is black
              */
            else if (node == node->parent->lChild && findUncle(node)->color == false )
            {
                rightRotated(node->parent);
                insertKeepRBT(node->rChild);
            }
        }
        else
        {
            /**
              * Current node is its father's right child while uncle is black
              */
            if (node == node->parent->rChild && findUncle(node)->color == false )
            {
                leftRotated(node->parent);
                insertKeepRBT(node->lChild);
            }

            /**
              * Current node is its father's left child while uncle is black
              */
            else if (node == node->parent->lChild && findUncle(node)->color == false )
            {
                node->parent->color = false;
                node->parent->parent->color = true;
                rightRotated(node->parent->parent);
            }
        }
    }
    else
        return;
}

template <typename T> void RBT<T>::inOrder(std::shared_ptr<RBTNode<T>> node)
{
    if (node == RBTNode<T>::nil) return;
    inOrder(node->lChild);
    std::cout << node->data << " " << node->getColor() << std::endl;
    inOrder(node->rChild);
}

template <typename T> void RBT<T>::preOrder(std::shared_ptr<RBTNode<T>> node)
{
    if (node == RBTNode<T>::nil) return;
    std::cout << node->data << " " << node->getColor() << std::endl;
    preOrder(node->lChild);
    preOrder(node->rChild);
}
#endif //end of _RBT_H
