#ifndef _RBT_H
#define _RBT_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::string;

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
        root  = new RBTNode<T>(newData, false);
        count = 0;
    }
    ~RBT()
	{
		delete root;
		root = NULL;
	}

    void insertNode(RBTNode<T>* node);
    void deleteNode(RBTNode<T>* node);

    void insertKeepRBT(RBTNode<T>* node);
    void leftRotated(RBTNode<T>* node);
    void rightRotated(RBTNode<T>* node);

    RBTNode<T>* getRoot() {return root;}
    void inOrder(RBTNode<T>* node);
    void preOrder(RBTNode<T>* node);

private:
    RBTNode<T>* root;
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
    ~RBTNode() {}

	static RBTNode<T>* nil;

    void setData(T newData) {data = newData;}
    T getData() {return data;}
    string getColor()
    {
        if(color) return "red";
    	else return "black";
	}
    void setColor(bool color) {this->color = color;}
    RBTNode<T>* getLChild() {return lChild;}
    RBTNode<T>* getRChild() {return rChild;}
    RBTNode<T>* getParent() {return parent;}

private:
    friend class RBT<T>;
    template <typename TT> friend RBTNode<TT>* findUncle(RBTNode<TT>*);
    
    T data;
    RBTNode<T> *lChild, *rChild, *parent;
    bool color; //Black is 0, red is 1;
};
template <typename T> RBTNode<T>* RBTNode<T>::nil = new RBTNode<T>();

template <typename T> RBTNode<T>* findUncle(RBTNode<T>* node)
{
    if (node->parent == RBTNode<T>::nil) return NULL;
    if (node->parent->parent->lChild == node->parent) return node->parent->parent->rChild;
    else return node->parent->parent->lChild;
}

template <typename T> void RBT<T>::insertNode(RBTNode<T>* node)
{
    ++count;
    if (root == RBTNode<T>::nil)
    {
        root = node;
        return;
    }
    
    RBTNode<T>* cur, * temp = root;
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

template <typename T> void RBT<T>::rightRotated(RBTNode<T> *node)
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

template <typename T> void RBT<T>::insertKeepRBT(RBTNode<T> *node)
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
        else if(node->parent == node->parent->parent->rChild) //node's parent node is node's grand node's right child
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

template <typename T> void RBT<T>::inOrder(RBTNode<T>* node)
{
	if(node == RBTNode<T>::nil) return;
    inOrder(node->lChild);
    cout<<node->data<<" "<<node->getColor()<<endl;
 	inOrder(node->rChild);
}

template <typename T> void RBT<T>::preOrder(RBTNode<T>* node)
{
	if(node == RBTNode<T>::nil) return;
    cout<<node->data<<" "<<node->getColor()<<endl;
    preOrder(node->lChild);
    preOrder(node->rChild);
}
#endif //end of _RBT_H
