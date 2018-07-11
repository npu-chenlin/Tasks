#include <iostream>
using namespace std;
int find(int n, int k)
{
	int cont[n];
	for (int i = 0; i < n; ++i)
	{
		cin>>cont[i];
	}
	for (int i = 0; i < n; ++i)
	{
		for (int m = 0; m < n; ++m)
		{
			if(m == i) continue;
			if( cont[m] == k-cont[i] ) return 1;
		}
	}
	return 0;
}
int main()
{
	int n,k;
	cin>>n>>k;
	if(find(n,k))
	{
		cout<<"yes"<<endl;
	}
	else cout<<"no";
	return 0;
}
