// 描述
//     Fungi is going to hold a game among his friends. In the game his n (n is even) friends will be divided into two opponent groups. 
//     The two groups have exactly the same number of players. To make the game more exciting, 
//     it would be better to split the players in such a way that the absolute level difference between the two groups is minimum. 
//     Each player has a known level Li, and the level of a group is defined by the sum of all the levels of the group members. 
//     Can you help Fungi?
// 输入
//     The first line has an integer T, the number of test cases (T<=20).
//     Each test case has one even integer n on the first line (2<=n<=50). The next line has n integers, the i-th representing Li. 0<=Li<=100.
// 输出
//     For each case, output the the minimum level difference Fungi can achieve for the game.
// Sample input
// 2
// 4
// 1 2 8 9
// 6
// 2 3 1 5 2 4
// Sample output
// 0
// 1
#include <iostream>
#include <memory.h>
#include <cmath>
#include <vector>
using namespace std;

int beibao(vector<int> nums, int n)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += nums[i];
	}
	int capacity = sum / 2;
	int ** d = new int*[n + 1];
	for (int i = 0; i < n+1; ++i)
	{
		d[i] = new int[capacity + 1];
		memset(d[i], 0, capacity + 1);
	}

	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < capacity + 1; ++j)
		{
			if (j-nums[i-1] < 0) 
			{
				d[i][j] = d[i-1][j];
				continue;
			}
			d[i][j] = max(d[i-1][j-nums[i-1]]+nums[i-1], d[i-1][j]);
		}
	}
	int value = abs(sum - 2*d[n][capacity]);

	for (int i = 0; i < n+1; ++i)
	{
		delete [] d[i];
	}
	delete [] d;
	return value;
}

int main(int argc, char const *argv[])
{
	int testCases;
    cin >> testCases;
	int n;
	int ans[testCases];
	std::vector<int> nums;
	for (int i = 0; i < testCases; ++i)
	{
		cin >> n;
		nums.resize(n,0);
		for (int j = 0; j < n; ++j)
		{
			cin>>nums[j];
		}
		ans[i] = beibao(nums, n);
	}
	for (int i = 0; i < testCases; ++i)
	{
		cout<<ans[i]<<endl;
	}
	return 0;
}
