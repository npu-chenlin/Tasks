/**
 * 背包问题。设背包总重为c，货物数为n，货物重量为goods[][0]，货物价值为[][1],如何向背包中放置货物才能保证价值最大。
 */

#include <iostream>
#include <list>

using namespace std;

// FIXME: `Cbeibao` is a bad name
void Cbeibao(int goods[][2] , int n, int** dp, int c)
{
	for (int i = 0; i < n; ++i)
	{
		dp[i][0] = 0;
	}
	for (int i = 0; i < c + 1; ++i)
	{
		dp[0][i] = 0;
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < c + 1; ++j)
		{
			if (j - goods[i][0] < 0)
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][(j - goods[i][0])] + goods[i][1]);
		}
	}
}

void printM(int** dp , int n , int c)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < c + 1; ++j)
		{
			if (j == c)
			{
				cout << dp[i][j] << endl;
			}
			else
				cout << dp[i][j] << " ";
		}
	}
}

void findPath(int** dp, int n, int c, list<int>* path, int goods[][2])
{
	int a = n - 1, b = c;
	while (a >= 1 && b >= 1)
	{
		if ((b - goods[a][0] >= 0) && (dp[a][b] == dp[a - 1][b - goods[a][0]] + goods[a][1]))
		{
			path->push_back(a);
			b -= goods[a][0];
			a--;
		}
		else if (dp[a][b] == dp[a - 1][b])
		{
			a--;
		}
	}
	for (list<int>::iterator p = path->begin(); p != path->end(); ++p)
	{
		cout << *p << endl;
	}
}

int main(int argc, char const *argv[])
{
	int goods[][2] =
	{
		0, 0,
		2, 3,
		3, 4,
		4, 5,
		5, 6
	};
	int c = 10;
	int n = 5;
	int** dp = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		dp[i] = new int [c + 1];
	}
	list<int> *path = new list<int>;

	Cbeibao(goods, n, dp, c);
	printM(dp, n, c);
	findPath(dp, n, c, path, goods);

	for (int i = 0; i < n; ++i)
	{
		delete [] dp[i];
	}
	delete [] dp;
	delete path;
	
	return 0;
}
