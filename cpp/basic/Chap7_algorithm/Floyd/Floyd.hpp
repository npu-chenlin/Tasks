#ifndef _FLOYD_H
#define _FLOYD_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

#define MAX_DISTANCE 999

using std::cout;
using std::endl;
using std::string;
using std::list;

class Floyd
{
public:
    Floyd(int vertex, int type = 0);
    ~Floyd() {}

    void addE(int i , int j, int w);
    void delE(int i , int j);

    void printM();
    void printP();

    void minPath();
    void minPath(int i , int j);  //i,j最短距

    void printMinPath(std::list<int>& path,int i , int j);//i,j行程
    void findPath(std::list<int>& path,int i , int j);

private:
    std::vector< std::vector<int> > d;
    std::vector< std::vector<int> > p;
    int v_n;
    int e_n;
    int Gtype;
    bool isDone;
};

Floyd::Floyd(int vertex, int type)
{
    v_n = vertex;
    isDone = false;

    d.resize(v_n);
    p.resize(v_n);
    for (int i = 0; i < v_n; ++i)
    {
        d[i].resize(v_n, MAX_DISTANCE);
        p[i].resize(v_n);
        for (int j = 0; j < v_n; ++j)
        {
            p[i][j] = j;
        }
    }
    for (int i = 0; i < v_n; ++i)
    {
        d[i][i] = 0;
    }

    e_n = 0;
    Gtype = type;
}

void Floyd::addE(int i, int j, int w)
{
    d[i][j] = w;
    d[j][i] = w;
    e_n++;
}

void Floyd::delE(int i , int j)
{
    d[i][j] = MAX_DISTANCE;
    d[j][i] = MAX_DISTANCE;
    e_n--;
}

void Floyd::printM()
{
    for (int i = 0; i < v_n; ++i)
    {
        for (int j = 0; j < v_n; ++j)
        {
            if (j == v_n - 1)
            {
                cout << d[i][j] << endl;
            }
            else {cout << d[i][j] << ' ';}
        }
    }
}

void Floyd::minPath()
{
    for (int i = 0; i < v_n; ++i)
    {
        for (int j = 0; j < v_n; ++j)
        {
            for (int k = 0; k < v_n; ++k)
            {
                if (d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[i][k];
                }
            }
        }
    }
}

void Floyd::minPath(int i, int j)
{
    if (!isDone) { minPath();}
    cout << d[i][j] << endl;
}

void Floyd::printMinPath(std::list<int>& path,int i, int j)
{
    if (!isDone) { minPath();}
    findPath(path,i, j);
    for (list<int>::iterator ptr = path.begin(); ptr != path.end(); ++ptr)
    {
        cout << *ptr << endl;
    }
}

void Floyd::findPath(std::list<int>& path,int i, int j)
{
    path.push_back(i);
    if (j == p[i][j])
    {
        path.push_back(j);
        return;
    }
    findPath(path,p[i][j], j);
}

void Floyd::printP()
{
    for (int i = 0; i < v_n; ++i)
    {
        for (int j = 0; j < v_n; ++j)
        {
            if (j == v_n - 1)
            {
                cout << p[i][j] << endl;
            }
            else {cout << p[i][j] << ' ';}
        }
    }
}

#endif //end of _FLOYD_H

