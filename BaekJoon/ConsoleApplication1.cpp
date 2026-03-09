#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
#define SIZE 7

using diPair = pair<double, int>;
using diPair2D = vector<vector<diPair>>;
using distAndCoord = tuple<double, int, int>;


void ConnectNode(vector<distAndCoord>& roads, diPair2D& graph)
{
	for (auto [dist, u, v] : roads)
	{
		graph[u].emplace_back(dist, v);
		graph[v].emplace_back(dist, u);
	}
}
int main()
{
	vector<distAndCoord> roads = // 거리, u, v
	{
		{6.0, 0, 1},
		{4.0, 0, 2},
		{5.0, 1, 2},
		{7.0, 1, 3},
		{6.0, 1, 4},
		{3.0, 2, 3},
		{8.0, 2, 4},
		{3.0, 3, 5},
		{3.0, 4, 6},
		{2.0, 5, 6},
	};

	diPair2D graph(SIZE);

	ConnectNode(roads, graph);

	priority_queue<diPair, vector<diPair>, greater<diPair>> q;
	bool visited[SIZE] = {};
	q.emplace(0, 0);

	double cost = 0;
	while (!visited[6] && !q.empty())
	{
		auto [dist, u] = q.top();

		q.pop();

		if (visited[u]) continue;

		visited[u] = true;
		cost += dist;
		printf("현재 노드: %c\n", u + 'a');
		printf("누적 거리: %lf\n\n", cost);
		for (auto [d, node] : graph[u])
		{
			if (visited[node]) continue;
			q.emplace(d, node);
		}
	}

	cout << cost;
	return 0;
}