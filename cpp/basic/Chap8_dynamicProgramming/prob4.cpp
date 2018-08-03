/**
 * 三角形最大路径问题
 * 从三角形的顶部到底部有很多条不同的路径，每个路径上的数字和称为路径和，求得三角形的最大路径
 * 7
 * 3 8
 * 8 1 0
 * 2 7 4 4
 * 4 5 2 6 5
 *
 * 最大路径 30
 *
 */

#include <iostream>
#include <list>

using std::cout;
using std::cin;
using std::endl;
using std::max;
using std::list;

void maxPath(int** tri , int** path, int n)
{
	for (int i = n - 2; i >= 0; i--)
	{
		for (int j = i; j >= 0; j--)
		{
			path[i][j] = tri[i][j] + max(path[i + 1][j], path[i + 1][j + 1]);
		}
	}
}

void printM(int** path, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			if (j == i)
			{
				cout << path[i][j] << endl;
			}
			else
				cout << path[i][j] << " ";
		}
	}
}

int main(int argc, char const *argv[])
{
	int n = 5;
	int** tri  = new int*[n];
	int** path = new int*[n];

	for (int i = 0; i < n; ++i)
	{
		tri[i]  = new int[n];
		path[i] = new int[n];
	}

	/*
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j <= i; ++j)
			{
				cin >> tri[i][j];
			}
		}
	*/

	list<int> examp = {7, 3, 8, 8, 1, 0, 2, 7, 4, 4, 4, 5, 2, 6, 5};
	list<int>::iterator p = examp.begin();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			tri[i][j] = *p;
			++p;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		path[n - 1][i] = tri[n - 1][i];
	}

	maxPath(tri, path, n);//
	printM(path, n);
	cout << endl ;
	cout << path[0][0] << endl;

	for (int i = 0; i < n; ++i)
	{
		delete [] tri[i];
		delete [] path[i];
	}
	delete [] tri;
	delete [] path;
	return 0;
}