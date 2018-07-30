#include <iostream>
template <typename T> void insertSort(T* d , int n)
{
	T key;
	int i , j;
	for (j = 1; j < n; ++j)
	{
		key = d[j];
                i = j;
		while(key < d[i-1])
		{
			d[i] = d[i-1];
			i--;
		}
		d[i] = key;

	}
}
int main(int argc, char const *argv[])
{
	num = 10
	int data[num];
	for (int i = 0; i < num; ++i)
	{
        std::cin>>data[i];
	}
	insertSort<int>(data,num);
	for (int i = 0; i < num; ++i)
	{
        std::cout<<data[i]<<std::endl;
	}
	return 0;
}