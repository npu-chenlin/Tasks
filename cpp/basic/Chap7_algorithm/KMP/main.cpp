#include <iostream>
#include "KMP.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
	vector<char> v = {'a','b','c','d','e','a','b','c','d'};
    vector<char> p = {'d','a'};

    cout<< KMP(v, p)<<endl;

	return 0;
}
