#include <iostream>
#include <fstream>
#include <memory.h>
#include <limits>

using namespace std;

#define INF 9999999999

long init_path(long dis_price[][2],long *dis,long i,long j)
{
    if(i > j) swap(i,j);
    if(i == j) return 0;
    if(dis[j] - dis[i] <= dis_price[0][0]) return dis_price[0][1];
    if(dis[j] - dis[i] <= dis_price[1][0]) return dis_price[1][1];
    if(dis[j] - dis[i] <= dis_price[2][0]) return dis_price[2][1];
    else return INF;
}

int main(long argc, char const *argv[])
{
	ifstream fin;
    fin.open("railway.in");
    long Dis_Price[3][2]; //0 is dis, 1 is price
    long n; 				 //Number of station
    long start,end;
    for (long i = 0; i < 3; ++i) fin>>Dis_Price[i][0];
    for (long i = 0; i < 3; ++i) fin>>Dis_Price[i][1];
	fin>>n;
	fin>>start;
	fin>>end;
	if (start > end) swap(start,end);
    long dis[n];
    dis[0] = 0;
    long* d = &dis[0];
    for (long i = 1; i < n; ++i) fin>>dis[i];
    //dis 0 means No1 station
    n = end - start + 1;
    long dp[n][n];
    for (long i = 0; i < n; ++i)
	{
        for(long j = 0; j < n; ++j)
            dp[i][j] = init_path(Dis_Price,d,start + i - 1,start + j - 1);
	}
    for (long i = 0; i < n; ++i)
	{
        for (long j = 0; j < i; ++j)
		{
            for (long k = i+1; k < n; ++k)
			{
                dp[j][k] = min(dp[j][k],dp[j][i]+dp[i][k]);
			}
		}
	}
    cout<<dp[0][n-1]<<endl;
    fin.close();
	return 0;
}
