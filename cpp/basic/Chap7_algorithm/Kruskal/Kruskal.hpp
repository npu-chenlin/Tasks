#ifndef _KRUSKAL_H
#define _KRUSKAL_H

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::sort;

#define MAX_DISTANCE 999
struct Dis
{
    int v1;
    int v2;
    int w;
    bool visited;
    Dis(int from, int to, int weight): v1(from), v2(to), w(weight), visited(false) {}
};
class Kruskal
{
public:
    explicit Kruskal(int vertex);
    ~Kruskal() {}

    void addE(int i , int j , int w);
    void delE(int i , int j);
    void printM();
    void printDAG();

    int getOutDegree(int i);
    int getInDegree(int i);
    std::vector< std::vector<int> > getM() {return h;}

    bool isDag(int n);
    bool isDAG();

    void MST();

private:
    int v;
    std::vector<Dis> e;
    std::vector< std::vector<int> > h;
    std::vector< std::vector<int> > DAG;
    std::vector<bool> deleted;
};

bool comp(const Dis &a , const Dis &b)
{
    return a.w < b.w;
}

Kruskal::Kruskal(int vertex)
{
    v = vertex;
    h.resize(v);
    for (int i = 0; i < v; ++i)
    {
        h[i].resize(v, MAX_DISTANCE);
        h[i][i] = 0;
    }
    deleted.resize(v, false);
}

void Kruskal::addE(int i, int j, int w)
{
    h[i][j] = w;
    h[j][i] = w;
    e.push_back(Dis(i, j, w));
}

void Kruskal::delE(int i, int j)
{
    h[i][j] = MAX_DISTANCE;
    h[j][i] = MAX_DISTANCE;
    for (std::vector<Dis>::iterator n = e.begin(); n != e.end(); ++n)
    {
        if ((n->v1 == i && n->v2 == j) || (n->v1 == j && n->v2 == i))
        {
            e.erase(n);
            break;
        }
    }
}

void Kruskal::printM()
{
    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            if (j == v - 1)
            {
                cout << h[i][j] << endl;
            }
            else {cout << h[i][j] << '\t';}
        }
    }
}

void Kruskal::printDAG()
{
    for (int i = 0; i < v; ++i)
    {
        cout<<i+1<<":";
        for (int j = 0; j < v; ++j)
        {
            if (DAG[i][j] != 0 && DAG[i][j] != MAX_DISTANCE)
            {
                cout<<j+1<<" ";
            }
        }
        cout<<endl;
    }
}

int Kruskal::getInDegree(int n)
{
    int count = 0;

    for (int i = 0; i < v; ++i)
    {
        if (deleted[i] == false && i != n && h[i][n] != MAX_DISTANCE)
        {
            ++count;
        }
    }

    return count;
}

int Kruskal::getOutDegree(int n)
{
    int count = 0;
    for (int i = 0; i < v; ++i)
    {
        if (deleted[i] == false && i != n && h[n][i] != MAX_DISTANCE)
        {
            ++count;
        }
    }
    return count;
}


bool Kruskal::isDag(int n)
{
    for (int i = n; i < v; ++i)
    {
        if (deleted[i] == false && (getOutDegree(i) == 1 || getOutDegree(i) == 0))
        {
            deleted[i] = true;
            return true;
        }
    }
    return false;
}

bool Kruskal::isDAG()
{
    while (1)
    {
        int n = -1;
        for (int i = 0; i < v; ++i)
        {
            if (deleted[i] == false)
            {
                n = i;
                break;
            }
        }
        if (n == -1)
        {
            for (int i = 0; i < v; ++i)
            {
                deleted[i] = false;
            }
            return true;
        }
        if (!isDag(n))
        {
            for (int i = 0; i < v; ++i)
            {
                deleted[i] = false;
            }
            return false;
        }
    }
}

void Kruskal::MST()
{
    Kruskal graphic(v);
    sort(e.begin(), e.end(), comp);
    for (std::vector<Dis>::iterator i = e.begin(); i != e.end(); ++i)
    {
        graphic.addE(i->v1, i->v2, i->w);
        if (!graphic.isDAG())
        {
            graphic.delE(i->v1, i->v2);
        }
    }
    DAG = graphic.getM();
}

#endif //end of _Kruskal_H