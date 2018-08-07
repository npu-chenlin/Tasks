#include <iostream>
#include "Floyd.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Floyd g(6);

    g.addE(0,1,6);
    g.addE(0,2,3);
    g.addE(1,3,5);
    g.addE(2,1,2);
    g.addE(2,3,3);
    g.addE(2,4,4);
    g.addE(3,4,2);
    g.addE(3,5,3);
    cout<<"距离矩阵"<<endl;
    g.printM();

    cout<<endl;
    cout<<"0->5路径"<<endl;
    g.printMinPath(0,5);

    cout<<endl;
    cout<<"最短距离矩阵"<<endl;
    g.printM();
    
    cout<<endl;
    cout<<"路径矩阵"<<endl;
    g.printP();

    return 0;
}