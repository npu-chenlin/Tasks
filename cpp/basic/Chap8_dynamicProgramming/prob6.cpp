/**
 * 某地区要举行一场竞赛，出题老师准备从题库中选取题目来设计考卷。已知题库中有N类题，每种分值不同。请设计一个程序帮助老师决定应该从每一种题目中选取多少题目，使得在一定时间内能够获得的总分最多
 *
 * 样例比赛时间和题目种类：
 * 389 4
 * 每种题目的分数和耗时：
 * 230 60 
 * 120 60 
 * 35 20 
 * 220 70
 *
 * 计算得到能够获得的最大分值是1415分 
 * 
 * 完全背包问题。
 */

#include <iostream>
#include <list>
using namespace std;

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
				dp[i][j] = max(dp[i - 1][j], dp[i][(j - goods[i][0])] + goods[i][1]);
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
		60, 230,
		50, 120,
		20, 35,
		70, 220
	};
	int c = 389;
	int n = 5;
	int** dp = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		dp[i] = new int [c + 1];
	}
	list<int> *path = new list<int>;

	Cbeibao(goods, n, dp, c);
	std::cout<<dp[n-1][c-1]<<std::endl;
	for (int i = 0; i < n; ++i)
	{
		delete [] dp[i];
	}
	delete [] dp;
	delete path;
	return 0;
}
