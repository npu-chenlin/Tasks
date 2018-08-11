/**
 * 全排列
 */

#include <iostream>

using namespace std;
int a[]={1,2,3,4,5,6,7,8,9};
void permutation(int n)
{
        if (n == 9)
        {
            for (int i = 0; i < n; ++i)cout<<a[i];
            cout<<endl;
        return;
        }
        for (int i = n; i < 9; ++i)
        {
            swap(a[n], a[i]);
            permutation(n+1);
            swap(a[n], a[i]);
        }
}

int main(int argc, char const *argv[])
{
    permutation(0);
    return 0;
}