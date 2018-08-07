#ifndef _ADJACENCYGRAPHIC_H
#define _ADJACENCYGRAPHIC_H

#include<iostream>
#include <vector>
#include <list>

using std::cout;
using std::vector;
using std::endl;
using std::list;

class AdjacencyGraphic
{
public:
	AdjacencyGraphic(int vertice, int noEdge = 0 , int type = 0);
	~AdjacencyGraphic() {}

	bool exist(int i , int j);
	int edges() {return e;}
	int vertices() {return v;}

	bool add(int i, int j, int w = 1);
	void deleteEdge(int i, int j);

	int outDegree(int i);
	int inDegree(int i);

	void dfs(vector<int>& visited , int num = 0);
	void DFS();

	void BFS();
	void bfs(vector<int>& visited , list<int> &l);

	void printM();

private:
	int NoEdge;
	int v;
	int e;
	vector< vector<int> > a;
	int Gtype;
};

AdjacencyGraphic::AdjacencyGraphic(int vertice, int noEdge , int type )
{
	Gtype = type;
	v = vertice;
	e = 0;
	NoEdge = noEdge;

	a.resize(v);
	for (int i = 0; i < v; ++i)
	{
		a[i].resize(v, 0);
	}
}

bool AdjacencyGraphic::exist(int i , int j)
{
	if (i < 0 || j < 0 || i > v - 1 || j > v - 1 || a[i][j] == NoEdge) return false;
	else return true;
}

bool AdjacencyGraphic::add(int i, int j , int data)
{
	if (i < 0 || j < 0 || i > v - 1 || j > v - 1)
	{
		return false;
	}
	if (Gtype == 0)
	{
		a[i][j] = data;
		a[j][i] = data;
	}
	else
	{
		a[i][j] = data;
	}
	e++;
	return true;
}

void AdjacencyGraphic::deleteEdge(int i, int j)
{
	if (exist(i , j))
	{
		if (Gtype == 0)
		{
			a[i][j] = NoEdge;
			a[j][i] = NoEdge;
		}
		else
		{
			a[i][j] = NoEdge;
		}
		e--;
	}
}

int AdjacencyGraphic::outDegree(int i)
{
	int sum = 0;
	for (int j = 0; j < v; ++j)
	{
		if (a[i][j] != NoEdge)
		{
			sum++;
		}
	}
	return sum;
}

int AdjacencyGraphic::inDegree(int i)
{
	int sum = 0;
	for (int j = 0; j < v; ++j)
	{
		if (a[j][i] != NoEdge)
		{
			sum++;
		}
	}
	return sum;
}

void AdjacencyGraphic::DFS()
{
	vector<int> visited(v, 0);
	for (int i = 0; i < v; ++i)
	{
		if (visited[i] == 0)
		{
			dfs(visited , i);
		}
	}
}

void AdjacencyGraphic::dfs(vector<int>& visited , int num)
{
	cout << num << endl;
	visited[num] = 1;
	for (int i = 0; i < v; ++i)
	{
		if (a[num][i] != NoEdge && visited[i] == 0)
		{
			dfs(visited, i);
		}
	}
}

void AdjacencyGraphic::BFS()
{
	list<int> l;
	vector<int> visited(v, 0);

	l.push_back(0);
	bfs(visited, l);
}

void AdjacencyGraphic::bfs(vector<int> &visited , list<int> &l)
{
	if (!l.empty())
	{
		int num = l.front();
		cout << num << endl;
		visited[num] = 1;

		l.pop_front();
		for (int i = 1; i < v; ++i)
		{
			if (a[num][i] != 0 && visited[i] == 0)
			{
				l.push_back(i);
			}
		}
		bfs(visited, l);
	}
}


void AdjacencyGraphic::printM()
{
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			if (j == v - 1)
			{
				cout << a[i][j] << endl;
			}
			else {cout << a[i][j] << ' ';}
		}
	}
}

#endif