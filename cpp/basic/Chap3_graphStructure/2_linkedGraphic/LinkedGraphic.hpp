#ifndef _LINKEDGRAPHIC_H
#define _LINKEDGRAPHIC_H

#include <iostream>

#include <list>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

using std::vector;
using std::list;
using std::find;

class LinkedGraphic
{
public:
    LinkedGraphic(int vertices, int type = 0)
    {
        v = vertices;
        e = 0;
        Gtype = type;
        h.resize(v);
    }
    ~LinkedGraphic() {}

    int getE() {return e;}
    int getV() {return v;}

    int outDegree(int i) {return h[i].size();}
    int inDegree(int i);

    bool exist(int i , int j);

    void addE(int i , int j);
    void delE(int i , int j);

    void dfs(vector<int>& visited , int num);
    void DFS();

    void bfs(list<int> &l , vector<int> &visited);
    void BFS();

    list<int> topo();

private:
    int v;
    int e;
    int Gtype;

    vector< list<int> > h;
};

int LinkedGraphic::inDegree(int i)
{
    int n = 0;
    for (int j = 0; j < v; ++j)
    {
        if (i != j)
        {
            list<int>::iterator p = find(h[j].begin(), h[j].end(), i);
            if (p != h[j].end()) {n++;}
        }
    }
    return n;
}

bool LinkedGraphic::exist(int i , int j)
{
    list<int>::iterator p = find(h[i].begin(), h[i].end(), j);
    if (p != h[i].end()) {return true;}
    else {return false;}
}

void LinkedGraphic::addE(int i , int j)
{
    h[i].push_back(j);
    if (Gtype == 0)
    {
        h[j].push_back(i);
    }
    e++;
}

void LinkedGraphic::delE(int i , int j)
{
    h[i].remove(j);
    if (Gtype == 0)
    {
        h[j].remove(i);
    }
    e--;
}

void LinkedGraphic::dfs(vector<int>& visited , int num)
{
    if (visited[num] == 0)
    {
        cout << num << endl;
        visited[num] = 1;
        if (h[num].empty() == 0)
        {
            list<int>::iterator p = h[num].begin();
            while ( p != h[num].end() )
            {
                dfs(visited , *p);
                ++p;
            }
        }

    }
}

void LinkedGraphic::DFS()
{
    vector<int> visited(v, 0);
    dfs(visited, 0);
}

void LinkedGraphic::bfs(list<int> &l , vector<int> &visited)
{
    if (l.empty() == 0)
    {
        int num = l.front();
        cout<<num<<endl;
        l.pop_front();
        for (list<int>::iterator i = h[num].begin(); i != h[num].end(); ++i)
        {
            if (visited[*i] == 0)
            {
                visited[*i] = 1;
                l.push_back(*i);
            }

        }
        bfs(l,visited);
    }
}

void LinkedGraphic::BFS()
{
    list<int> l;
    vector<int> visited(v,0);
    l.push_back(0);
    visited[0] = 1;
    bfs(l,visited);
}

#endif //end of _LINKEDGRAPHIC_H