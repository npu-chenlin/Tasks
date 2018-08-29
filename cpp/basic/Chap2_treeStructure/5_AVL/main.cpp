#include <iostream>
#include <fstream>
#include "AVL.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    AVL<int> tree;
    ifstream fin;
    fin.open("test.in");
    string s;
    int i;
    bool flag = 1;
    while(!fin.eof())
    {
        fin>>s;
        i = atoi(s.c_str());
        if(s == "del:")
        {
            flag = 0;
            continue;
        }
        else if(s == "add:")
        {
            flag = 1;
            continue;
        }
        if(flag)
        {
            tree.addNode(i);
        }
        else
        {
            tree.del(i);
        }
    }
    tree.preOrder(tree.getRoot());
    return 0;
}
