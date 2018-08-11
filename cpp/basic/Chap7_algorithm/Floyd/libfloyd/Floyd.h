#ifndef _FLOYD_H
#define _FLOYD_H

#include <vector>
#include <list>

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

    void printMinPath(int i , int j);//i,j行程
    void findPath(int i , int j);

private:
    std::vector< std::vector<int> > d;
    std::vector< std::vector<int> > p;
    int v;
    int e;
    std::list<int> path;
    int Gtype;
    bool isDone;
};

#endif//end of _FLOYD_H