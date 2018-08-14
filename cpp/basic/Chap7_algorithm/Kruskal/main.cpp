/**
 * Kruskal 计算最小生成树
 */
#include <iostream>

#include "Kruskal.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Kruskal g(5);
    g.addE(0, 1, 7);
    g.addE(0, 2, 2);
    g.addE(0, 4, 5);
    g.addE(1, 2, 3);
    g.addE(1, 3, 5);
    g.addE(2, 4, 3);
    g.addE(3, 4, 6);
    g.printM();
    cout << endl;
    g.MST();
    g.printDAG();
    return 0;
}