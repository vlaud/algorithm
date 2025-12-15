#include <iostream>
#include <queue>
#include <tuple>

using namespace std;
using int3 = tuple<int, int, int>;
#define endl '\n'

int bfs(vector<string>& s, int n, int m) {
	queue<int3> q;

	int time = 1;
	q.emplace(0, 0, 1);
	s[0][0] = '0';

	while (!q.empty()) {
		auto [r, c, t] = q.front(); q.pop();
		time = t;

		if (r == n - 1 && c == m - 1) break;
		for (int i = -1; i < 2; i += 2) {
			int nr = r + i, nc = c + i;
			
			if (0 <= nr && nr < n && s[nr][c] == '1') {
				q.emplace(nr, c, t + 1);
				s[nr][c] = '0';
			}
			if (0 <= nc && nc < m && s[r][nc] == '1') {
				q.emplace(r, nc, t + 1);
				s[r][nc] = '0';
			}
		}
		
	}

	return time;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;

	cin >> n >> m;
	vector<string> s(n);

	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}

	cout << bfs(s, n, m);
	return 0;
}