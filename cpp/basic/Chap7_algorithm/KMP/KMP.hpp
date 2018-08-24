#include <vector>

template <typename T> std::vector<int> getNext(std::vector<T> p)
{
	int j = 0;
	int k = -1;
    std::vector<int> v(p.size());
    v[0] = -1;
	while (j < p.size() )
	{
		if (k == -1 || p[j] == p[k])
            v[++j] == k++;
		else
			k = v[k];
	}
    return v;
}

template <typename T> int KMP(std::vector<T> string , std::vector<T> pattern)
{
    std::vector<int> next = getNext(pattern);
	int i = 0;
	int j = 0;

    while (i < (int)string.size() && j < (int)pattern.size())
	{
		if (j == -1 || string[i] == pattern [j])
		{
			++i;
			++j;
		}
		else
            j = next[j];
    }

    if (j == (int)pattern.size())
		return i-j;
	else
		return -1;
}
