#include <iostream>
using namespace std;
int main()
{
	for (int i = 0; i < 7; ++i)
	{
		if (i != 3)
		{
			for (int n = 0; n < 8; ++n)
			{
				if(n == i) cout<<"*";
				else if(n == (7-i)) cout<<"*"<<endl;
				else cout<<" ";
			}
		}
		else cout<<"   *"<<endl;
	}
}
