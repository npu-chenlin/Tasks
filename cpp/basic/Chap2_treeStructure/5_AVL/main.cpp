#include <iostream>
#include <fstream>
#include "AVL.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    AVL<int> tree;
    ifstream fin;
    ofstream fout;
    fin.open("test.in");
    fout.open("dll.txt");
    string s;
    int i;
    while(fin.good())
    {
        fin>>s;
        i = atoi(s.c_str());
        tree.addNode(i);
    }
    tree.changeIntoLinkedlist(tree.getRoot());
    std::shared_ptr<AVLNode<int>> cur = tree.getRoot();
    while(cur->getLChild() != AVLNode<int>::nil) cur = cur->getLChild();

    while(1)
    {
        if(cur->getSucessor() == AVLNode<int>::nil)
        {
            fout<<cur->getData();
            break;
        }
        fout<<cur->getData()<<"<=>";
        cur = cur->getSucessor();
    }
    fin.close();
    fout.close();
    return 0;
}
