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

    void add(T newData);
    void del(T Data);
    void insertNode(std::shared_ptr<RBTNode<T>> node);
    bool deleteNode(std::shared_ptr<RBTNode<T>> node);

    void insertKeepRBT(std::shared_ptr<RBTNode<T>> node);
    void deleteKeepRBT(std::shared_ptr<RBTNode<T>> node);

    void leftRotated(std::shared_ptr<RBTNode<T>> node);
    void rightRotated(std::shared_ptr<RBTNode<T>> node);
    void RBTTransPlant(std::shared_ptr<RBTNode<T>> be_replaced,std::shared_ptr<RBTNode<T>> replace);

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

template <typename T> void RBT<T>::add(T newData)
{
    std::shared_ptr<RBTNode<T>> p(new RBTNode<T>(newData));
    insertNode(p);
}

template <typename T> void RBT<T>::del(T Data)
{
    deleteNode(RBTSearch(root,Data));
}

template <typename T> std::shared_ptr<RBTNode<T>> RBTSearch(std::shared_ptr<RBTNode<T>> node , T data)
{
    if(data > node->getData()) return RBTSearch(node->getRChild(),data);
    else if(data < node->getData()) return RBTSearch(node->getLChild(),data);
    else return node;
}

template <typename T> std::shared_ptr<RBTNode<T>> RBTFindMinimum(std::shared_ptr<RBTNode<T>> node)
{
    while (node->getLChild() != RBTNode<T>::nil)node = node -> getLChild();
    return node;
}

template <typename T> std::shared_ptr<RBTNode<T>> RBTFindMaximum(std::shared_ptr<RBTNode<T>> node)
{
    while (node->getRChild() != RBTNode<T>::nil)node = node -> rChild;
    return node;
}

template <typename T> std::shared_ptr<RBTNode<T>> RBTFindSuccessor(std::shared_ptr<RBTNode<T>> node)
{
    if(node->getRChild()) return RBTFindMinimum(node->getRChild());
    while( node ->getParent()->getLChild() != node)
    {
        node = node -> getParent();
        if(node = RBTNode<T>::nil) return node;
    }
    return node -> getParent();
}

template <typename T> std::shared_ptr<RBTNode<T>> findUncle(std::shared_ptr<RBTNode<T>> node)
{
    if (node->parent == RBTNode<T>::nil) return NULL;
    if (node->parent->parent->lChild == node->parent) return node->parent->parent->rChild;
    else return node->parent->parent->lChild;
}

template <typename T> void RBT<T>::RBTTransPlant(std::shared_ptr<RBTNode<T>> be_replaced,std::shared_ptr<RBTNode<T>> replace)
{
    if (be_replaced->parent == RBTNode<T>::nil ) root = replace;
    else if ( be_replaced->parent->lChild == be_replaced) be_replaced->parent->lChild = replace;
    else be_replaced->parent->rChild = replace;
    replace->parent = be_replaced -> parent;
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

template <typename T> bool RBT<T>::deleteNode(std::shared_ptr<RBTNode<T>> node)
{
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
            RBTTransPlant(node,node->rChild);
            deleteKeepRBT(node->rChild);
            return true;
        }
        else if ((node->lChild == RBTNode<T>::nil) != (node->rChild == RBTNode<T>::nil))
        {
            std::shared_ptr<RBTNode<T>> next = (node->lChild == RBTNode<T>::nil) ? node->rChild : node->lChild;
            RBTTransPlant(node,next);
            deleteKeepRBT(next);
            return true;
        }
        else
        {
            std::shared_ptr<RBTNode<T>> temp = RBTFindSuccessor(node);
            this->deleteNode(temp);
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
            RBTTransPlant(node,node->rChild);
            return true;
        }
        else
        {
            std::shared_ptr<RBTNode<T>> temp = RBTFindSuccessor(node);
            node->data = temp -> data;
            this->deleteNode(temp);
            return true;
        }
    }
}

template <typename T> void RBT<T>::deleteKeepRBT(std::shared_ptr<RBTNode<T>> node)
{
    while (node != root && node->color == false)
    {
        if(node == node->parent->lChild)
        {
            if(node->parent->rChild->color == true)
            {
                node->parent->color = true;
                node->parent->rChild->color = false;
                leftRotated(node->parent);
            }
            else
            {
                if(node->parent->rChild->lChild->color == false && node->parent->rChild->rChild->color == false)
                {
                    node->parent->rChild->color = true;
                    node = node ->parent;
                }
                else if(node->parent->rChild->lChild->color == true && node->parent->rChild->rChild->color == false)
                {
                    std::swap(node->parent->rChild->color,node->parent->rChild->lChild->color);
                    rightRotated(node->parent->rChild);
                }
                else
                {
                    node->parent->rChild->rChild->color = false;
                    std::swap(node->parent->color,node->parent->rChild->color);
                    leftRotated(node->parent);
                    node = root;
                }
            }
        }
        else
        {
            if(node->parent->rChild->color == true)
            {
                node->parent->color = true;
                node->parent->lChild->color = false;
                rightRotated(node->parent);
            }
            else
            {
                if(node->parent->lChild->rChild->color == false && node->parent->lChild->lChild->color == false)
                {
                    node->parent->lChild->color = true;
                    node = node ->parent;
                }
                else if(node->parent->lChild->rChild->color == true && node->parent->lChild->lChild->color == false)
                {
                    std::swap(node->parent->lChild->color,node->parent->lChild->rChild->color);
                    leftRotated(node->parent->lChild);
                }
                else
                {
                    node->parent->lChild->lChild->color = false;
                    std::swap(node->parent->color,node->parent->lChild->color);
                    rightRotated(node->parent);
                    node = root;
                }
            }
        }
    }
    node->color = false;
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

    if (node->lChild->rChild != RBTNode<T>::nil)
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
