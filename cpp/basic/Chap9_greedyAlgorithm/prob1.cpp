#include <iostream>
#include <list>

using std::cin;
using std::cout;
using std::endl;

class Activity
{
public:
    Activity(int startT, int endT)
    {
        startTime = startT;
        endTime   = endT;
    }
    ~Activity() {}

    getStartTime() return startTime;
    setStartTime(int T) startTime = T;

    getEndTime() return endTime;
    setEndTime(int T) endTime = T;


private:
    int startTime;
    int endTime;
};




