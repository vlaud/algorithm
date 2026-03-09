#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
#define SIZE 7

using diPair = pair<double, int>;
using diPair2D = vector<vector<diPair>>;
using distAndCoord = tuple<double, int, int>;

enum NODE
{
	A,B,C,D,E,F,G
};
void ConnectNode(vector<distAndCoord>& roads, diPair2D& graph)
{
	for (auto [dist, u, v] : roads)
	{
		graph[u].emplace_back(dist, v);
		graph[v].emplace_back(dist, u);
	}
}

double FindShortest(diPair2D& graph, int start, int end)
{
	priority_queue<diPair, vector<diPair>, greater<diPair>> q;
	vector<double> dists(SIZE, DBL_MAX); // 누적거리 배열, 시작 지점 제외 전부 INF로 고정
	vector<int> prevs(SIZE, -1); // 이전 노드 주소 저장

	dists[start] = 0.0; // 시작 지점 거리 = 0

	q.emplace(0, start);

	while (!q.empty())
	{
		auto [dist, u] = q.top();
		q.pop();

		if (u == end) break; // 다익스트라 알고리즘과의 유일한 차이 => 목적지에 도달하면 break
		if (dist > dists[u]) continue;

		for (auto [d, node] : graph[u])
		{
			if (dists[node] > d + dists[u]) // 기존 누적 거리 > 현재 노드 누적 거리 + 다음 노드 거리면 갱신
			{
				dists[node] = d + dists[u];
				prevs[node] = u;
				q.emplace(dists[node], node);
			}
		}
	}

	int arrive = end;

	printf("역추적: %c ", arrive+'A');
	arrive = prevs[arrive];

	while (arrive != -1)
	{
		printf("- %c ", arrive+'A');
		arrive = prevs[arrive];
	}
	cout << endl;
	return dists[end];
}

int main()
{
	vector<distAndCoord> roads = // 거리, u, v
	{
		{6.0, 0, 1},
		{3.0, 0, 2},
		{6.5, 1, 2},
		{7.0, 1, 3},
		{7.5, 1, 4},
		{2.0, 2, 3},
		{8.0, 2, 4},
		{3.0, 3, 5},
		{3.0, 4, 6},
		{2.0, 5, 6},
	};

	diPair2D graph(SIZE);

	ConnectNode(roads, graph);

	cout << FindShortest(graph, NODE::E, NODE::A);
	return 0;
}