#include <iostream>
#include <fstream>
#include "SBT.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream fin;
    ofstream fout;
    fin.open("test.in");
    fout.open("dll.txt");
    string s;
    int i;
    fin>>s;
    i = atoi(s.c_str());
    SBT<int> tree(i);
    while(fin.good())
    {
        fin>>s;
        i = atoi(s.c_str());
        tree.add(i);
    }
    tree.changeIntoLinkedlist();
    std::shared_ptr<SBTNode<int>> cur = tree.getRoot();
    while(cur->getLChild() != NULL) cur = cur->getLChild();

    while(1)
    {
        if(cur->getSucessor() == NULL)
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
