#include <iostream>
#include "LinkedGraphic.h"
using namespace std;

int main(int argc, char const *argv[])
{
	LinkedGraphic g(8);
	g.add(0,1);
	g.add(0,2);
	g.add(1,3);
	g.add(1,4);
	g.add(2,3);
	g.add(2,6);
	g.add(3,5);
	g.add(3,7);
	g.add(4,5);
	g.add(6,7);
	g.DFS();
	cout<<endl;
	return 0;
}