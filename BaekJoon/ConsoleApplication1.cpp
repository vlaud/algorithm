#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#define endl "\n"
using namespace std;

bool dVisited[1001];
bool bVisited[1001];
vector<vector<int>> graph(1001);
int from[1001];
stack<int> track;

void bfs(int source, int destination) {
	queue<int> q;
	q.push(source);
	bVisited[source] = true;
	from[source] = 0;
	int current = 0;

	while (!q.empty()) {
		current = q.front();
		cout << current << " ";
		q.pop();

		for (int next : graph[current]) {
			if (!bVisited[next]) {
				q.push(next);
				bVisited[next] = true;
				from[next] = current;
			}
		}
	}
	cout << "final: " << current << endl;
	cout << endl;
	cout << endl;
	current = destination;

	while (current != 0) {
		cout << current << " is from: " << from[current] << endl;
		track.push(current);
		current = from[current];
	}
	while (!track.empty()) {
		cout << track.top() << " ";
		track.pop();
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
	
	int N, M, V, D;

	cin >> N >> M >> V >> D;
	
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	for (int i = 0; i <= N; i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	bfs(V, D);
	cout << endl;
	
	return 0;
}