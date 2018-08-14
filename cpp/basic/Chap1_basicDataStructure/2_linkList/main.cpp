#include <iostream>

#include "linkList.h"

using namespace std;

int main(int argc, char const *argv[])
{
	LinkList<int> list;
	for (int i = 0; i < 10; ++i)
	{
		list.insertNode(i);
	}

	list.removeNode(3);
	list.printLink();

	return 0;
}
