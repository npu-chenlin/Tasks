#include <iostream>

#include "AVL.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    AVL<int> tree(4);

    for(int i = 1;i<10;i++)
    {
        if(i!=4)
        {tree.add(i);}
    }

    tree.del(4);
    tree.del(3);
    tree.inOrder(tree.getRoot());
 
    return 0;
}
