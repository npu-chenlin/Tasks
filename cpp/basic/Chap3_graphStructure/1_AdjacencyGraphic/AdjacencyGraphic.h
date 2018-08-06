#ifndef _ADJACENCYGRAPHIC_H
#define _ADJACENCYGRAPHIC_H

#include<iostream>
#include <vector>

// FIXME: do not use namespace in header files
using namespace std;

template <typename T> class AdjacencyGraphic
{
public:
	AdjacencyGraphic(int vertice, T noEdge = 0 , int type = 0);
	~AdjacencyGraphic()
	{
		delete2DArray();
	}

	bool exist(int i ,int j);
	int edges(){return e;}
	int vertices(){return v;}

	void add(int i,int j, T w=1);
	void deleteEdge(int i,int j);

	int outDegree(int i);
	int inDegree(int i);

	void make2DArray();
	void delete2DArray();

	void dfs(int* visited , int num = 0);
	void DFS();

	void BFS();
	void bfs(int* visited , vector<T> &vec);

	void printM();
	
private:
	T NoEdge;
	int v;
	int e;
	T** a;
	int Gtype;
};

template <typename T> void AdjacencyGraphic<T>::make2DArray()
{
	a = new T*[v];
	for (int i = 0; i < v; ++i)
	{
		a[i] = new T[v];
	}
}

template <typename T> void AdjacencyGraphic<T>::delete2DArray()
{
	for (int i = 0; i < v; ++i)
	{
		delete [] a[i];
	}
	delete [] a;
}

template <typename T> AdjacencyGraphic<T>::AdjacencyGraphic(int vertice, T noEdge , int type )
{
	Gtype = type;
	v = vertice;
	e = 0;
	NoEdge = noEdge;
	make2DArray();
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			a[i][j] = NoEdge;
		}
	}
}

template <typename T> bool AdjacencyGraphic<T>::exist(int i ,int j)
{
	if(i<0 || j<0 || i>v-1 || j>v-1 || a[i][j] == NoEdge) return false;
	else return true;
}

template <typename T> void AdjacencyGraphic<T>::add(int i, int j , T data)
{
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
}

// FIXME: if delete a edge failed? How to make the caller know the failure?
template <typename T> void AdjacencyGraphic<T>::deleteEdge(int i,int j)
{
	if(exist(i ,j))
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

template <typename T> int AdjacencyGraphic<T>::outDegree(int i)
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

template <typename T> int AdjacencyGraphic<T>::inDegree(int i)
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

template <typename T> void AdjacencyGraphic<T>::DFS()
{
	int* visited = new int[v];
	for (int i = 0; i < v; ++i)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < v; ++i)
	{
		if(visited[i] == 0)
		{
			dfs(visited , i);
		}
	}
	delete [] visited;
}

template <typename T> void AdjacencyGraphic<T>::dfs(int* visited , int num)
{
	cout<<num<<endl;
	visited[num] = 1;
	for (int i = 0; i < v; ++i)
	{
		if(a[num][i] != NoEdge && visited[i] == 0)
		{
			dfs(visited , i);
		}
	}
}

template <typename T> void AdjacencyGraphic<T>::BFS()
{
	vector<T> vec(v);
	int* visited = new int[v];
	for (int i = 0; i < v; ++i)
	{
		visited[i] = 0;
	}
	cout<<0<<endl;
	vec.push_back(0);
	visited[0]=1;
	bfs(visited,vec);
}

template <typename T> void AdjacencyGraphic<T>::bfs(int* visited , vector<T> &vec)
{
	if (!vec.empty())
	{
		int num;
		num = vec.at(vec.size()-1);
		vec.pop_back();
		for (int i = 0; i < v; ++i)
		{
			if (a[num][i] != 0 && visited[i] == 0)
			{
				cout<<i<<endl;
				visited[i] = 1;
				vec.push_back(i);
			}
		}
		bfs(visited,vec);
	}
}


template <typename T> void AdjacencyGraphic<T>::printM()
{
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			if (j == v-1)
			{
				cout<<a[i][j]<<endl;
			}
			else {cout<<a[i][j]<<' ';}
		}
	}
}

#endif