#include <iostream>

#include "Floyd.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Floyd g(6);
    std::list<int> path;
    g.addE(0,1,6);
    g.addE(0,2,3);
    g.addE(1,3,5);
    g.addE(2,1,2);
    g.addE(2,3,3);
    g.addE(2,4,4);
    g.addE(3,4,2);
    g.addE(3,5,3);
    cout<<"Matrix distance"<<endl;
    g.printM();

    cout<<endl;
    cout<<"path:0->5"<<endl;
    g.printMinPath(path,0,5);

    cout<<endl;
    cout<<"Matrix shortest path"<<endl;
    g.printM();
    
    cout<<endl;
    cout<<"Matrix path"<<endl;
    g.printP();

    return 0;
}
