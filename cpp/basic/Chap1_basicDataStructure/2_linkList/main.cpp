#include "linkList.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	linkList<int> list;
	for (int i = 0; i < 10; ++i)
	{
		list.insertNode(i);
	}
	cout<<list.findNode(3)->getData()<<endl;
	return 0;
}
