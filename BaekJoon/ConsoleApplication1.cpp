#include <iostream>
#include <vector>
#include <queue>

#define endl '\n'

using namespace std;

using int2d = vector<vector<int>>;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n, m;

	cin >> n >> m;

	vector<int> idg(n+1);
	int2d adj(n+1);

	int a, b;
	while (m--) {
		cin >> a >> b;

		adj[a].emplace_back(b);
		idg[b]++;
	}
	queue<int> q;

	for (int i = 1; i <= n; i++) {
		if (!idg[i]) q.emplace(i);
	}

	while (!q.empty()) {
		int x = q.front(); q.pop();

		cout << x << " ";
		for (int& i : adj[x]) {
			if (--idg[i] == 0) q.emplace(i);
		}

	}


	return 0;
}
