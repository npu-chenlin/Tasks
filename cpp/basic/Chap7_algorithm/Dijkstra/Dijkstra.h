#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAX 999


struct Dis
{
	string path = "";
	bool visited = 0;
    int minValue = MAX;
};

class Dijkstra
{
public:
	Dijkstra(int vertex);
	~Dijkstra();
	void addE(int i ,int j ,int w);
	void delE(int i ,int j);

	void printM();

	void minPath(int begin);
	void printMinPath(int begin);

private:
	int v;
	int e;
	int** h;
    vector<Dis> dis;
};

Dijkstra::Dijkstra(int vertex)
{
	v = vertex;
	h = new int* [v];
	for (int i = 0; i < v; ++i)
	{
		h[i] = new int [v];
	}
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			h[i][j] = MAX;
		}
	}
	e = 0;
	dis.resize(v);
}

Dijkstra::~Dijkstra()
{
	for (int i = 0; i < v; ++i)
	{
		delete [] h[i];
	}
	delete h;
}

void Dijkstra::addE(int i, int j,int w)
{
	h[i][j] = w;
	e++;
}

void Dijkstra::delE(int i ,int j)
{
	h[i][j] = MAX;
	e--;
}

void Dijkstra::printM()
{
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			if (j == v-1)
			{
				cout<<h[i][j]<<endl;
			}
			else {cout<<h[i][j]<<' ';}
		}
	}
}

void Dijkstra::minPath(int begin)
{
	for (int i = 0; i < v; ++i)
	{
   		dis[i].path = to_string(begin) + "->" + to_string(i);
	    dis[i].minValue = h[begin][i];
	}
	dis[begin].visited = 1;
	
	int count = 1;
	int temp;
	while(count != v)
	{
		int min = MAX;
		for (int i = 0; i < v; ++i)
		{
			if (dis[i].visited == 0 && dis[i].minValue < min)
			{
				min = dis[i].minValue;
				temp = i;
			}
		}
		dis[temp].visited = 1;
		count++;

		for (int i = 0; i < v; ++i)
		{
			if (!dis[i].visited && h[temp][i] != MAX)
			{
				if (dis[temp].minValue + h[temp][i] < dis[i].minValue)
				{
					dis[i].minValue = dis[temp].minValue + h[temp][i];
					dis[i].path = dis[temp].path + "->" + to_string(i);
				}
			}
		}

	}
}

void Dijkstra::printMinPath(int begin)
{
	this->minPath(begin);
	for (int i = 0; i < v; ++i)
	{
		cout<<dis[i].path<<" "<<dis[i].minValue<<endl;
	}
}

#endif // end of _DIJKSTRA_H
 
