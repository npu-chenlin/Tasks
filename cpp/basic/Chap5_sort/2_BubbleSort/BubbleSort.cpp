#include <iostream>
#include <fstream>
#include <iostream>

using namespace std;

template<typename T> void bubbleSort(T* d, int n)
{
    int flag = 1;
    for (int j = 0; j < n-1 && flag; ++j)
    {
        flag = 0;
        for (int i = 0; i < n-j-1; ++i)
        {
            if (d[i] > d[i+1])
            {
                swap(d[i],d[i+1]);
                flag = 1;
            }           
        }

    }
}
int main(int argc, char const *argv[])
{
    int a[]={7,6,5,4,3,2,1,0};
    bubbleSort<int>(a,8);

    for (int i = 0; i < 8; ++i)
    {
        cout<<a;
    }
    
    return 0;
}