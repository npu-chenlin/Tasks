#include <iostream>
using namespace std;

int paixu(int n, char a, char b)
{
	if (n == 1)
	{
		cout<<n<<":"<<a<<"->"<<b<<endl;
		return 0; 
	}
	switch(b)
	{
		case 'c':	
		{
			paixu(n-1,'a','b');
			cout<<n<<":"<<a<<"->"<<b<<endl;
			paixu(n-1,'b','c');
		}
		case 'b':
		{
			paixu(n-1,'a','c');
			cout<<n<<":"<<a<<"->"<<b<<endl;
			paixu(n-1,'c','b');	
		}
	}
}
int main(int argc, char const *argv[])
{
	paixu(2,'a','c');
	return 0;
}
