#include <iostream>
#include "Floyd.h"

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

	g.printMinPath(0,5);

	cout<<endl;
	g.printM();
	
	cout<<endl;
	g.printP();

//	g.printMinPath(0);

	return 0;
}