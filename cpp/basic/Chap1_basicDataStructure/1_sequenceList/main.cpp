#include <iostream>

#include "seqlist.h" // put local header below system headers

using namespace std;

int main(int argc, char const *argv[])
{
	// generate a list
	seqList<int> list(10);
	for (int i = 0; i < 10; ++i)
	{
		list.insertElement(i);
	}

	// delete one element and print the list
	list.deleteElement(5);
	for (int i = 0; i < 10; ++i)
	{
		cout<<list.getElement(i)<<endl;
	}
	
	return 0;
}
