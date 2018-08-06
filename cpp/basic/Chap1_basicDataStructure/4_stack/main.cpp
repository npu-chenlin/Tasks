#include <iostream>

#include "stack.h"

using namespace std;

int main(int argc, char const *argv[])
{
	stack<char> s(27);
	for (int i = 0; i < 26; ++i)
	{
		s.push(char('a'+i));
	}

	for (int i = 0; i < 26; ++i)
	{
		cout<<s.pop()<<endl;
	}

	return 0;
}
