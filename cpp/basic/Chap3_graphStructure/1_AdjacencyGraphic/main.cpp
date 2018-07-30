#include "AdjacencyGraphic.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	AdjacencyGraphic<int> g(10);
	g.add(0,1,1);
	g.add(0,2,1);
	g.add(0,3,1);
	g.add(0,4,1);
	g.add(1,5,1);
	g.add(1,6,1);
	g.add(2,7,1);
	g.add(2,8,1);
	g.add(3,9,1);
	g.printM();
	g.DFS();
	cout<<endl;
	g.BFS();
	return 0;
}