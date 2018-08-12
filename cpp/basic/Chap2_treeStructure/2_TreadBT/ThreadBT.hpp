#ifndef _THREADBT_H
#define _THREADBT_H

#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;

template <typename T> class ThreadBT;

template <typename T> class ThreadBTNode
{
public:
    ThreadBTNode() // Initialize node without param
    {
        data   = NULL;
        lChild = NULL;
        rChild = NULL;
        ltag   = false;
        rtag   = false;
    }
    explicit ThreadBTNode(T newData) //Initialize node with param
    {
        data   = newData;
        lChild = rChild = NULL;
        ltag   = false;
        rtag   = false;
    }

    void setData(T newData) {data = newData;}
    T getData() {return data;}
    ThreadBTNode<T>* getLChild() {return lChild;}
    ThreadBTNode<T>* getRChild() {return rChild;}

private:
    friend class ThreadBT<T>;
    T data;
    ThreadBTNode<T>* lChild;
    ThreadBTNode<T>* rChild;
    bool ltag;
    bool rtag;
};

template <typename T> class ThreadBT
{
public:
    ThreadBT()
    {
        root = new ThreadBTNode<T>();
    }
    explicit ThreadBT(T newData)
    {
        root = new ThreadBTNode<T>(newData);
    }
    ~ThreadBT()
    {
        if ( root )
        {
            delete root;
            root = NULL;
        }

    }

    void preOrder(ThreadBTNode<T>* node);// 前序中序后序遍历
    void inOrder(ThreadBTNode<T>* node, ThreadBTNode<T>* &pre);
    void inThreading();
    void layOrder(ThreadBTNode<T>* node);// 层序遍历

    ThreadBTNode<T>* getRoot(){return root;}
    ThreadBTNode<T>* getParent(ThreadBTNode<T>* node);
    ThreadBTNode<T>* getLChild(ThreadBTNode<T>* node);
    ThreadBTNode<T>* getRChild(ThreadBTNode<T>* node);
    ThreadBTNode<T>* getBrother(ThreadBTNode<T>* node);

    int getDepth();
    void insertSubBT(ThreadBTNode<T>* subBT , ThreadBTNode<T>* node);
    void deleteNodes(ThreadBTNode<T>* node);
    void destroyBT();

private:
    ThreadBT<T>(const ThreadBT<T>&);
    ThreadBT<T>& operator=(const ThreadBT<T>&);

private:
    ThreadBTNode<T>* root;
};

template <typename T> void ThreadBT<T>::preOrder(ThreadBTNode<T>* node)
{
    if (node != NULL)
    {
        std::cout << node->getData() << std::endl;
        preOrder(node->getLChild());
        preOrder(node->getRChild());
    }
}

template <typename T> void ThreadBT<T>::inOrder(ThreadBTNode<T>* node, ThreadBTNode<T>* &pre)
{
    if (node != NULL)
    {
        inOrder(node->lChild,pre);
        if (!node->lChild)
        {
            node->ltag = true;
            node->lChild = pre;
            if (!pre)
            {
                cout<<node->getData()<<"prior node is NULL"<<endl;
            }
            else
                cout<<node->getData()<<"prior node is "<<pre->getData()<<endl;
        }
        if (pre != NULL && !pre->rChild)
        {
            pre->rtag = true;
            pre->rChild = node;
            cout<<pre->getData()<<"succeeding node is"<<node->getData()<<endl;
        }

        pre = node;
        inOrder(node->rChild,pre);
    }
}

template<typename T> void ThreadBT<T>::inThreading()
{
    ThreadBTNode<T>* pre;
    pre = NULL;
    inOrder(root,pre);

}

template <typename T> void ThreadBT<T>::layOrder(ThreadBTNode<T>* node)
{
    if ( node != NULL)
    {
        ThreadBTNode<T>* current = node;
        std::list<ThreadBTNode<T>*> tempList;
        std::cout << current->getData() << std::endl;
        while ( tempList.empty() || current != NULL)
        {
            if (current->lChild != NULL)
            {
                tempList.push_back(current->lChild);
            }
            if (current->rChild != NULL)
            {
                tempList.push_back(current->rChild);
            }
            current = tempList.front();
            std::cout << current->getData() << std::endl;
            tempList.pop_front();
        }
    }
}

template <typename T> ThreadBTNode<T>* ThreadBT<T>::getParent(ThreadBTNode<T>* node)
{
    if (node == root)
    {
        return NULL;
    }

    if ( node != NULL)
    {
        ThreadBTNode<T>* current = root;
        std::list<ThreadBTNode<T>*> tempList;
        while ( tempList.empty() || current != NULL)
        {
            if (current->lChild != node && current->lChild != NULL)
            {
                tempList.push_back(current->lChild);
            }
            else if ( current->lChild == node)
            {
                return current;
            }

            if (current->rChild != node && current->rChild != NULL)
            {
                tempList.push_back(current->rChild);
            }
            else if ( current->rChild == node)
            {
                return current;
            }

            current = tempList.front();
            tempList.pop_front();
        }

        return NULL;
    }
}

template <typename T> ThreadBTNode<T>* ThreadBT<T>::getLChild(ThreadBTNode<T> *node)
{
    if (node != NULL) {return node->lChild;}
    else return NULL;
}

template <typename T> ThreadBTNode<T>* ThreadBT<T>::getRChild(ThreadBTNode<T>* node)
{
    if (node != NULL) {return node->rChild;}
    else return NULL;
}

template <typename T> ThreadBTNode<T>* ThreadBT<T>::getBrother(ThreadBTNode<T> *node)
{
    if (node == NULL)return NULL;
    ThreadBTNode<T>* parentNode = getParent(node);
    if (parentNode == NULL)
    {
        return NULL;
    }
    if (parentNode->getLChild() == node)
    {
        return parentNode->getRChild();
    }
    if (parentNode->getRChild() == node)
    {
        return parentNode->getLChild();
    }
}

template <typename T> int ThreadBT<T>::getDepth()
{
    std::list<ThreadBTNode<T>*> nodeStack;
    ThreadBTNode<T>* node = root;
    nodeStack->push_back(node);
    int maxDepth = 1;
    while (!nodeStack.empty())
    {
        while (node -> lChild != NULL)
        {
            node = node -> lChild;
            nodeStack.push_back(node);
        }
        if (node -> rChild == NULL)
        {
            if (nodeStack.size() > maxDepth)
            {
                maxDepth = nodeStack.size();
            }
            node = nodeStack.back();
            nodeStack.pop_back();
        }
        else
        {
            node = node -> rChild;
            nodeStack.push_back(node);
        }
    }
    return maxDepth;
}

template <typename T> void ThreadBT<T>::insertSubBT(ThreadBTNode<T>* subBT , ThreadBTNode<T> *node)
{
    if (node == NULL) return;
    if (node -> lChild == NULL)
    {
        node -> lChild = subBT;
    }
    else if (node -> rChild == NULL)
    {
        node -> rChild = subBT;
    }
}
template <typename T> void ThreadBT<T>::deleteNodes(ThreadBTNode<T>* node)
{
    if (node != NULL)
    {
        deleteNodes(node->lChild);
        deleteNodes(node->rChild);
        delete node;
    }
}
template <typename T> void ThreadBT<T>::destroyBT()
{
    deleteNodes(root->lChild);
    deleteNodes(root->rChild);
    root = NULL;
}

#endif
