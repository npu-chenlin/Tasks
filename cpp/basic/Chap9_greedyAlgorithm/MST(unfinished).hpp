/**
 * 最小生成树
 */
#include <iostream>
#include <list>

#ifndef _MINIMUMSPANNINGTREE_H
#define _MINIMUMSPANNINGTREE_H

using std::cin;
using std::cout;
using std::endl;
using std::list;
struct Edge
{
	Edge(int s, int e, int w)
	{
		startVertex = s;
		endVertex = e ;
		weight = w;
	}
	int startVertex;
	int endVertex;
	int weight;
};

class MST
{
public:
	MST(int vertex)
	{
		e = 0;
		v = vertex;
		arg = new int*[v];
		for (int i = 0; i < v; ++i)
		{
			arg[i] = new int [v];
		}
		for (int i = 0; i < v; ++i)
		{
			for (int j = 0; j < v; ++j)
			{
				arg[i][j] = 0;
			}
		}
	}
	~MST()
	{
		for (int i = 0; i < v; ++i)
		{
			delete [] arg[i];
		}
		delete [] arg;
	}

	void addV();
	void addE(int s , int e, int w);
	void delV();
	void delE();

private:
	int e;
	int v;
	list<Edge> edge;
	int** arg;
};

void MST::addE(int s, int e, int w)
{
	edge.push_back(Edge(s, e, w));
	arg[s][e] = w;
}




#endif //end of _MINIMUMSPANNINGTREE_H