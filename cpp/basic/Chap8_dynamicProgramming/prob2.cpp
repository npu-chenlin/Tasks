/**
 * 最长公共子序列问题,给定序列x,y，求其最长公共子序列。
 * x,y为给定序列，m,n为长度
 * c[i][j]存储LCS长度
 */
#include <iostream>
#include <list>

using namespace std;

void LCSlength(int*x , int *y, int m, int n, int **c)
{
	bool temp = false;

	for (int i = 0; i < m; ++i)
	{
		if (x[i] == y[0] || temp)
		{
			temp = true;
			c[i][0] = 1;
		}
		else
			c[i][0] = 0;
	}

	temp = false;

	for (int i = 0; i < n; ++i)
	{
		if (x[0] == y[i] || temp)
		{
			temp = true;
			c[0][i] = 1;
		}
		else
			c[0][i] = 0;
	}

	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else
			{
				c[i][j] = max(c[i - 1][j], c[i][j - 1]);
			}
		}
	}
}

void printM(int **c, int m, int n)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (j == n - 1) { cout << c[i][j] << endl;}
			else {cout << c[i][j] << " ";}
		}
	}
}

void findPath(int*x , int *y, int m, int n, int **c, list<int>* path)
{
	int a = m - 1;
	int b = n - 1;
	while (a >= 0 && b >= 0)
	{
		if (x[a] != y[b])
		{
			if (c[a - 1][b] >= c[a][b - 1])a--;
			else b--;
		}
		else
		{
			path->push_back(x[a]);
			a--;
			b--;
		}
	}

	for (list<int>::iterator p = path->begin(); p != path->end(); ++p)
	{
		cout << *p << endl;
	}

}

int main(int argc, char const *argv[])
{
	int x[] = {1, 3, 4, 5, 6, 7, 7, 8};
	int y[] = {3, 5, 7, 4, 8, 6, 7, 8, 2};
	int m = 8, n = 9;
	int** c = new int* [m];
	for (int i = 0; i < m; ++i)
	{
		c[i] = new int [n];
	}

	list<int>* path = new list<int>;

	LCSlength(x, y, m, n, c);

	printM(c, m, n);
	findPath(x, y, m, n, c, path);
	for (int i = 0; i < m; ++i)
	{
		delete [] c[i];
	}
	delete [] c;
	delete path;
	
	return 0;
}