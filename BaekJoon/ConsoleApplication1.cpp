#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define endl '\n'

unsigned int count_trailing_zeros(unsigned int x) {
	unsigned long index;
	if (x == 0) {
		// __builtin_ctz(0)는 undefined behaviour 이므로
		return /* 원하는 값, 예컨대 sizeof(x)*8 */ 32;
	}
	_BitScanForward(&index, x);
	return static_cast<unsigned int>(index);
}

void dfs(vector<vector<int>> &grp, bool *visited, int idx)
{
	if (visited[idx])
		return;
	visited[idx] = true;
	cout << idx << " ";
	for (int &i : grp[idx])
	{
		dfs(grp, visited, i);
	}
}

// 큐 안쓰고
void bitbfs(vector<vector<int>> &grp, bool *visited, int idx)
{
	int bit = 0;
	bit |= (1 << idx);

	while (bit)
	{
		int x = count_trailing_zeros(bit);
		bit &= ~(1 << x);
		visited[x] = true;
		cout << x << " ";
		for (int &i : grp[x])
		{
			if (visited[i])
				continue;
			bit |= (1 << i);
		}
	}
}

void bfs(vector<vector<int>> &grp, bool *visited, int idx)
{
	queue<int> q;
	q.emplace(idx);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		visited[x] = true;
		cout << x << " ";
		for (int &i : grp[x])
		{
			if (visited[i])
				continue;
			q.emplace(i);
		}
	}
}

int main()
{
	int n = 7;
	vector<vector<int>> grp(n);
	bool visited[7];

	grp[0].emplace_back(1);
	grp[1].emplace_back(0);
	grp[0].emplace_back(2);
	grp[2].emplace_back(0);

	grp[1].emplace_back(3);
	grp[3].emplace_back(1);
	grp[1].emplace_back(4);
	grp[4].emplace_back(1);

	grp[2].emplace_back(5);
	grp[2].emplace_back(6);
	grp[5].emplace_back(2);
	grp[6].emplace_back(2);

	fill(visited, visited + 7, false);

	dfs(grp, visited, 0);
	cout << endl;
	fill(visited, visited + 7, false);
	bitbfs(grp, visited, 0);
	return 0;
}