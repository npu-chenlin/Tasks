#include <iostream>
#include "doubleList.h"
using namespace std;
int main(int argc, char const *argv[])
{
	doubleList<int> list;
	for (int i = 0; i < 20; ++i)
	{
		list.insertNode(i);
	}
	cout<<list.findData(4)->getData()<<endl;
	return 0;
}
