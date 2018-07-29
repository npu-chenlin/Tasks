#include "seqlist.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	seqList<int> list(10);
	for (int i = 0; i < 10; ++i)
	{
		list.insertElement(i);
	}
	list.deleteElement(5);
	for (int i = 0; i < 10; ++i)
	{
		cout<<list.getElement(i)<<endl;
	}
	return 0;
}
