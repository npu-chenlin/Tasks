#ifndef _FLOYD_H
#define _FLOYD_H

#include <iostream>
#include <string>
#include <list>

// FIXME: the define of 'MAX' is good, can be changed to `DIST_MAX`. 
//		Because `MAX` is common, the name will be conflict to other programs.
#define MAX 999

using namespace std;

class Floyd
{
public:
	Floyd(int vertex,int type);
	~Floyd();

	void addE(int i ,int j, int w);
	void delE(int i ,int j);

	void printM();
	void printP();

	void minPath();
	void minPath(int i , int j);  //i,j最短距

	void printMinPath(int i , int j);//i,j行程
	void findPath(int i ,int j);

private:
	int** d;
	int** p;
	int v;
	int e;
	list<int> path;
	int Gtype;
	bool isDone = false;
};

Floyd::Floyd(int vertex,int type = 1)
{
	v = vertex;

	d = new int* [v];
	p = new int* [v];
	for (int i = 0; i < v; ++i) 
	{
		d[i] = new int [v];
		p[i] = new int [v];
	}
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)	
		{
			d[i][j] = MAX;
			p[i][j] = j;
		}
	}

	e = 0;
	Gtype = type;
}

Floyd::~Floyd()
{
	for (int i = 0; i < v; ++i)
	{
		delete [] d[i];
		delete [] p[i];
	}
	delete [] d;
	delete [] p;
}

void Floyd::addE(int i, int j,int w)
{
	d[i][j] = w;
	d[j][i] = w;
	e++;
}

void Floyd::delE(int i ,int j)
{
	d[i][j] = MAX;
	d[j][i] = MAX;
	e--;
}

void Floyd::printM()
{
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			if (j == v-1)
			{
				cout<<d[i][j]<<endl;
			}
			else {cout<<d[i][j]<<' ';}
		}
	}
}

void Floyd::minPath()
{
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			for (int k = j+1; k < v; ++k)
			{
				if (d[j][i]+d[i][k] < d[j][k])	
				{
					int temp = (d[j][i] == MAX || d[i][k] == MAX)? MAX : (d[j][i]+d[i][k]);
					d[j][k] = temp;
					d[k][j] = d[j][k];
					p[j][k] = p[j][i];
					//p[k][j] = p[j][k];
				}
			}
		}
	}
}

void Floyd::minPath(int i, int j)
{
	if (!isDone) { minPath();}
	cout<<d[i][j]<<endl;
}

void Floyd::printMinPath(int i,int j)
{
	if (!isDone) { minPath();}
	findPath(i,j);
	for (list<int>::iterator ptr = path.begin(); ptr != path.end(); ptr++)
	{
		cout<<*ptr<<endl;
	}

}

void Floyd::findPath(int i,int j)
{
	path.push_back(i);
	if (j == p[i][j]) 
	{
		path.push_back(j);
		return;
	}
	findPath(p[i][j],j);
}

void Floyd::printP()
{
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			if (j == v-1)
			{
				cout<<p[i][j]<<endl;
			}
			else {cout<<p[i][j]<<' ';}
		}
	}
}

#endif//end of _FLOYD_H