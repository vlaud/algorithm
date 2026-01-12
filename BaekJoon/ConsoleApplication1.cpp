#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> makeTable(string pattern)
{
	const int n = pattern.size();
	vector<int> table(n);

	int len = 0;

	for (int i = 1; i < n; i++)
	{
		while (0 < len && pattern[i] != pattern[len])
		{
			len = table[len - 1];
		}
		if (pattern[i] == pattern[len])
		{
			table[i] = ++len;
		}
	}
	return table;
}

void KMP(string parent, string pattern)
{
	vector<int> table = makeTable(pattern);
	const int parentSize = parent.size(), patternSize = pattern.size();

	int len = 0;

	for (int i = 0; i < parentSize; i++)
	{
		while (0 < len && parent[i] != pattern[len])
		{
			len = table[len - 1];
		}
		if (parent[i] == pattern[len])
		{
			if (len == patternSize-1)
			{
				printf("%d에서 찾음\n", i - patternSize + 2);
				len = table[len];
			}
			else len++;
		}
	}
}
int main()
{
	string parent = "ababacabacaabacaaba";
	string pattern = "abacaaba";
	KMP(parent, pattern);
	return 0;
}