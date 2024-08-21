#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#define endl "\n"
using namespace std;

bool dVisited[1001];
bool bVisited[1001];
vector<vector<int>> graph(1001);

void bfs(int source) {
	queue<int> q;
	q.push(source);
	bVisited[source] = true;
	int current = 0;

	while (!q.empty()) {
		current = q.front();
		cout << current << " ";
		q.pop();

		for (int next : graph[current]) {
			if (!bVisited[next]) {
				q.push(next);
				bVisited[next] = true;
			}
		}
	}
}
void dfs(int current) {

	dVisited[current] = true;
	cout << current << " ";

	for (int next : graph[current]) {
		if (!dVisited[next]) {
			dfs(next);
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M, V;

	cin >> N >> M >> V;

	int a, b;
	for (int i = 0; i <= M; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 0; i <= N; i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	dfs(V);
	cout << endl;
	bfs(V);
	cout << endl;

	return 0;
}