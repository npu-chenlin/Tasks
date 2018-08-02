
#ifndef _DP_H
#define _DP_H value

#include <iostream>
#include <list>
using namespace std;

void fastestWay(int exitA,int entraA ,int exitB,int entraB, int** a ,int** t,int** line,int n)
{
	int **f = new int*[2];
	f[1] = new int[n];
	f[2] = new int[n];
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			f[i][j] == -1;
		}
	}

	f[0][0] = entraA + a[0][0];
	f[1][0] = entraB + a[1][0];
	line[0][0] = -1;
	line[1][0] = -1;

	for (int i = 1; i < n; ++i)
	{
		if (f[0][i-1] +a[0][i] > f[1][i-1] + t[1][i-1] + a[0][i])
		{
			f[0][i] = f[1][i-1] + t[1][i-1] + a[0][i];
			line[0][i] = 1;
		}
		else
		{
			f[0][i] = f[0][i-1] +a[0][i];
			line[0][i] = 0;
		}
		if (f[1][i-1] +a[1][i] > f[0][i-1] + t[0][i-1] + a[1][i])
		{
			f[1][i] = f[0][i-1] + t[0][i-1] + a[1][i];
			line[1][i] = 0;
		}
		else
		{
			f[1][i] = f[1][i-1] +a[1][i];
			line[1][i] = 1;
		}
	}
	f[0][n-1]+=exitA;
	f[1][n-1]+=exitB;

	if (f[0][n-1] < f[0][n-1])
	{
		line[0][0] = 1;
	}
	else
	{
		line[1][0] = 1;
	}
}





#endif //end of _DP_H