#ifndef _LINKEDGRAPHIC_H
#define _LINKEDGRAPHIC_H

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class LinkedGraphic
{
public:
	LinkedGraphic(int vertices,int type = 1)
	{
		v = vertices;
		e = 0;
		Gtype = type;
		h = new list<int>[v];
	}
	~LinkedGraphic()
	{
		delete[] h;
	}

	int getE(){return e;}
	int getV(){return v;}

	int outDegree(int i){return h[i].size();}
	int inDegree(int i);

	bool exist(int i ,int j);

	void addE(int i , int j);//添加边
	void delE(int i , int j);
	void delV(int i);

	void dfs(int* visited , int num);
	void DFS();

	list<int> topo();

private:
	int v;
	int e;
	list<int>* h;
	int Gtype;
};

int LinkedGraphic::inDegree(int i)
{
	int n = 0;
	for (int j = 0; j < v; ++j)
	{
		if(i != j)
		{
			list<int>::iterator p = find(h[j].begin(), h[j].end(),i);
			if (p != h[j].end()) {n++;}
		}
	}
	return n;
}

bool LinkedGraphic::exist(int i ,int j)
{
	list<int>::iterator p = find(h[i].begin(), h[i].end(), j);
	if (p != h[i].end()){return true;}
	else {return false;}
}

void LinkedGraphic::add(int i , int j)
{
	h[i].push_back(j);
	if (Gtype == 0)
	{
		h[j].push_back(i);
	}
	e++;
}

void LinkedGraphic::del(int i , int j)
{
	h[i].remove(j);
	if (Gtype == 0)
	{
		h[j].remove(i);
	}
	e--;
}

void LinkedGraphic::dfs(int* visited , int num)
{	
	if (visited[num] == 0)
	{
		cout<<num<<endl;
		visited[num] = 1;
		if (h[num].empty() == 0)
		{
			list<int>::iterator p = h[num].begin();
			while( p != h[num].end() )
			{	
				dfs(visited , *p);
				p++ ;
			}
		}

	}

}


#endif