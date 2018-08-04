/**
 * 对于从1到N的连续整数集合，能划分成两个子集合，且保证每个集合中数字之和相等。举个例子，如果N=3，对于{1，2，3}能划分成两个子集合，他们的每个集合所有数字和是相等的：3和{1,2}
 * 如果对于7，则有4中分法
 * {1,6,7}和{2,3,4,5}
 * {2,5,7}和{1,3,4,6}
 * {3,4,7}和{1,2,5,6}
 * {1,2,4,7}和{3,5,6}
 * 试求出对于任意数N有多少种分法。
 */
#include <iostream>
#include <string>
#include <vector>

using std::endl;
using std::string;

void findNum(int n , int m, int** M)
{
	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < m + 1; ++j)
		{
			if (j - i < 0)
			{
				M[i][j] = M[j-1][j] + 1;
				continue;
			}     
			M[i][j] = M[i - 1][j] + M[i - 1][j - i];
		}
	}
}

void printM(int m,int n ,int** M)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (j == n-1)
			{
				std::cout << M[i][j] << std::endl;
			}
			else
				std::cout << M[i][j] << " ";
		}
	}
}

int main(int argc, char const *argv[])
{
	int n;
	std::cout<<"输入数字N:"<<endl;
	std::cin>>n;
	int m = n * (n + 1);
	if (m % 4 != 0)
	{
		std::cout << 0 << endl;
		return 0;
	}
	m /= 4;

	int** M = new int* [n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		M[i] = new int[m + 1];
	}

	for (int i = 0; i < n + 1; ++i)
	{
		M[i][0] = 1;
	}
	for (int i = 1; i < m + 1; ++i)
	{
		M[0][i] = 0;
	}

	findNum(n, m, M);
	
	std::cout<<M[n][m]/2<<endl;
	for (int i = 0; i < n + 1; ++i)
	{
		delete []  M[i];
	}
	delete [] M;
	return 0;
}