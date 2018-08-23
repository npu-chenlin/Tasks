#include <iostream>
#include <memory>
#include "RBT.hpp"

using namespace std;

/*
 * 12 1 9 2 0 11 7 19 4 15 18 5 14 13 10 16 6 3 8 17
 */

int main(int argc, char const *argv[])
{
    RBT<int> tree(12);

    tree.add(1);
    tree.add(9);
    tree.add(2);
    tree.add(-1);
    tree.add(11);
    tree.add(7);
    tree.add(19);
    tree.add(4);
    tree.add(15);
    tree.add(18);
    tree.add(5);
    tree.add(14);
    tree.add(13);
    tree.add(10);
    tree.add(16);
    tree.add(6);
    tree.add(3);
    tree.add(8);
    tree.add(17);

    tree.del(12);
    tree.del(1);

    tree.inOrder(tree.getRoot());

    return 0;
}
