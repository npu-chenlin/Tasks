#include <iostream>
#include <stdio.h>
using namespace std;

template <typename T> int partition(T* d,int p,int r);
template <typename T> void quickSort(T* d,int p,int r)
{
	int pos = r;
	if (r > p)
	{
		pos = partition(d , p ,r);
		quickSort(d , pos + 1,r);
		quickSort(d , p , pos-1);
	}
}
template <typename T> int partition(T* d,int p,int r)
{
	int pos = p;
	for (int i = p; i < r; ++i)
	{
		if (d[i] < d[r])
		{
			swap(d[i],d[pos]);
			pos++;
		}
	}
	swap(d[pos],d[r]);
	return pos;
}

int main(int argc, char const *argv[])
{
	int d[] = {9,8,7,6,5,4,3,2,1,10};
	quickSort<int>(d,0,9);
	for (int i = 0; i < 10; ++i)
		{
			printf("%d\n", d[i]);
		}	
	return 0;
}