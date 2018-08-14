/**
 * 有一个汽车公司，有两条生产线，我们用字母i表示这两条生产线编号(i=1,2)，每条生产线上有n个装配站，用字母j表示其编号，j=1,2,3,……,n。将生产线i的第j个装配站
 * 表示为Sij。两条生产线的第j个装配站的功能相同。但是这两条生产线的产能不同，生产效率也是不同的，比如S1，j和S2，j的生产效率就不相同。我们将每个生产线的第j个装配站
 * 的生产时间记为Cij。当汽车底盘进入生产线之后，可以在它完成任意一道装配工序j之后将其挪到另一条生产线的j+1装配站上。移动汽车底盘的时间消耗为ti,j,表示底盘完成了
 * 在装配站Sij上的工作之后，送到另一条生产线上的装配站j+1上的时间，所以在t中，i=1,2，但是j=1.2,.,n-1。ei表示各条生产线上底盘的进入时间，Xi表示生产完成后的离开时间。
 * 问题是我们可以在两条生产线上分别选择哪些转配站组成的生产工序能使生产效率最高，汽车生产所耗的总时间最小。
 */


#include <iostream>
#include <list>

using namespace std;

void fastestWay(int exitA , int entraA , int exitB, int entraB, int** a , int** t, int** line, int n)
{
	//entraA,entraB,exitA,exitB 进入，离开A,B生产线用时
	//a[i][j] 存储第i条生产线第j装配站用时
	//t[i][j] 从第i条生产线第j装配站转移到另一条生产线j+1个装配站用时
	//line    存储路线
	//n        装配站数量
	int **f = new int*[2];
	f[1] = new int[n];
	f[2] = new int[n];				// FIXME: better way to generate 2D array?
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			f[i][j] = -1;
		}
	}

	f[0][0] = entraA + a[0][0];
	f[1][0] = entraB + a[1][0];
	line[0][0] = -1;
	line[1][0] = -1;

	for (int i = 1; i < n; ++i)
	{
		if (f[0][i - 1] + a[0][i] > f[1][i - 1] + t[1][i - 1] + a[0][i])
		{
			f[0][i] = f[1][i - 1] + t[1][i - 1] + a[0][i];
			line[0][i] = 1;
		}
		else
		{
			f[0][i] = f[0][i - 1] + a[0][i];
			line[0][i] = 0;
		}
		if (f[1][i - 1] + a[1][i] > f[0][i - 1] + t[0][i - 1] + a[1][i])
		{
			f[1][i] = f[0][i - 1] + t[0][i - 1] + a[1][i];
			line[1][i] = 0;
		}
		else
		{
			f[1][i] = f[1][i - 1] + a[1][i];
			line[1][i] = 1;
		}
	}
	f[0][n - 1] += exitA;
	f[1][n - 1] += exitB;

	if (f[0][n - 1] < f[1][n - 1])
	{
		line[0][0] = 0;
	}
	else
	{
		line[1][0] = 1;
	}

	delete f[1];
	delete f[0];
	delete [] f;
}

void findPath(int** line, int n)
{
	if (line[0][0] ==0)
	{
		/* code */
	}
	if (line[0][0] == 1)
	{
		/* code */
	}
}


int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}