#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;

#define MAX_DISTANCE 999                // FIXME: if the user input distance exceed 999, how?

struct Dis
{
    string path;
    bool visited;
    int minValue;

    Dis():path(""),visited(false),minValue(MAX_DISTANCE)
    {}
};

class Dijkstra
{
public:
    explicit Dijkstra(int vertex);
    ~Dijkstra() {}
    void addE(int i , int j , int w);
    void delE(int i , int j);

    void printM();

    void minPath(int begin);
    void printMinPath(int begin);

private:
    int v;
    int e;
    std::vector< std::vector<int> > h;
    std::vector<Dis> dis;
};


Dijkstra::Dijkstra(int vertex)
{
    v = vertex;
    h.resize(v);
    for (int i = 0; i < v; ++i)
    {
        h[i].resize(v, MAX_DISTANCE);
        h[i][i] = 0;
    }
    e = 0;
}

void Dijkstra::addE(int i, int j, int w)
{
    h[i][j] = w;
    h[j][i] = w;
    e++;
}

void Dijkstra::delE(int i , int j)
{
    h[i][j] = MAX_DISTANCE;
    h[j][i] = MAX_DISTANCE;
    e--;
}

void Dijkstra::printM()
{
    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            if (j == v - 1)
            {
                cout << h[i][j] << endl;
            }
            else {cout << h[i][j] << ' ';}
        }
    }
}

void Dijkstra::minPath(int begin)
{
    dis.resize(0);
    dis.resize(v);
    for (int i = 0; i < v; ++i)
    {
        dis[i].path     = std::__cxx11::to_string(begin) + "->";
        dis[i].minValue = h[begin][i];
    }

    dis[begin].visited = 1;
    int count = 1;
    while (count != v)
    {
        int min = MAX_DISTANCE;
        int temp;
        for (int i = 0; i < v; ++i)
        {
            if (dis[i].visited == 0 && dis[i].minValue < min)
            {
                min  = dis[i].minValue;
                temp = i;
            }
        }

        dis[temp].visited = 1;
        ++count;

        for (int i = 0; i < v; ++i)
        {
            if (dis[i].visited == 0)
            {
                if (dis[temp].minValue + h[temp][i] < dis[i].minValue)
                {
                    dis[i].minValue = dis[temp].minValue + h[temp][i];
                    dis[i].path     += std::__cxx11::to_string(temp) + "->";
                }
            }
        }
    }

    for (int i = 0; i < v; ++i)
    {
        dis[i].path += std::__cxx11::to_string(i); 
    }
}

void Dijkstra::printMinPath(int begin)
{
    this->minPath(begin);
    for (int i = 0; i < v; ++i)
    {
        cout << dis[i].path << " " << dis[i].minValue << endl;
    }
}

#endif // end of _DIJKSTRA_H

