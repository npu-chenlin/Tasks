#include <iostream>

#include "LinkedGraphic.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    LinkedGraphic g(8);
    g.addE(0,1);
    g.addE(0,2);
    g.addE(1,3);
    g.addE(1,4);
    g.addE(2,3);
    g.addE(2,6);
    g.addE(3,5);
    g.addE(3,7);
    g.addE(4,5);
    g.addE(6,7);

    g.DFS();
    cout<<endl;
    g.BFS();
    return 0;
}