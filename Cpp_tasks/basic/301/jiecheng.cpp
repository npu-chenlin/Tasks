#include <iostream>
using namespace std;

int jiecheng(int n)
{
	if (n == 1) return 1;
	else return jiecheng(n-1)*n;
}

int main(int argc, char const *argv[])
{
	int n;
	cin>>n;
	cout<<jiecheng(n);
	return 0;
}
