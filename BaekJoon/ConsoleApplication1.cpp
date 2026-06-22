#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional>

using namespace std;

string mat[3];

struct Coord
{
	int y, x, dist, target;
	Coord(int y, int x, int dist, int target) : y(y), x(x), dist(dist), target(target) {}
};

bool compare(Coord* a, Coord* b)
{
	return a->dist > b->dist;
}

function<bool(Coord*, Coord*)> cmp = compare;

void dijkstra(int& row, int& col, int dist, int target, int& cnt, priority_queue<Coord*, vector<Coord*>, decltype(cmp)>& pq)
{
	if (mat[row][col] - '0' == target) return;

	vector<vector<int>> dists(3, vector<int>(5, INT_MAX));

	dists[row][col] = dist;

	priority_queue<Coord*, vector<Coord*>, decltype(cmp)> q(cmp);
	q.emplace(new Coord(row, col, 0, target));

	while (!q.empty())
	{
		auto& [r, c, d, t] = *q.top();
		q.pop();

		if (mat[r][c] - '0' == target)
		{
			if (target == 4)
			{
				cnt = min(cnt, d);
				break;
			}
			pq.emplace(new Coord(r, c, d, t + 1));
		}

		if (d > dists[r][c]) continue;

		for (int i = -1; i < 2; i += 2)
		{
			int nr = r + i, nc = c + i;
			int newG = dists[r][c] + 1;

			if (0 <= nr && nr < 3 && mat[nr][c] != '#' && dists[nr][c] > newG)
			{
				dists[nr][c] = newG;
				q.emplace(new Coord(nr, c, newG, t));
			}

			if (0 <= nc && nc < 5 && mat[r][nc] != '#' && dists[r][nc] > newG)
			{
				dists[r][nc] = newG;
				q.emplace(new Coord(r, nc, newG, t));
			}
		}
	}
}

int main()
{
	for (int i = 0; i < 3; i++)
	{
		cin >> mat[i];
	}

	priority_queue<Coord*, vector<Coord*>, decltype(cmp)> q(cmp);
	q.emplace(new Coord(0, 0, 0, 1));
	int cnt = INT_MAX;
	while (!q.empty())
	{
		auto [r, c, d, t] = *q.top();
		q.pop();
		dijkstra(r, c, d, t, cnt, q);
	}
	cout << cnt;
	return 0;
}