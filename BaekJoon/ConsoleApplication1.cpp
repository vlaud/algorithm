#include <iostream>
#include <queue>

using namespace std;
using iPair = pair<int, int>;
#define endl '\n'

int board[500][500];

int bfs(int row, int col, int n, int m) {
	queue<iPair> q;

	q.emplace(row, col);
	board[row][col] = 0;
	int size = 0;

	while (!q.empty()) {
		auto [r, c] = q.front(); q.pop();
		
		size++;
		
		for (int i = -1; i < 2; i += 2) {
			int nr = r + i;
			int nc = c + i;
			if (0 <= nr && nr < n && board[nr][c]) {
				q.emplace(nr, c);
				board[nr][c] = 0;
			}
			if (0 <= nc && nc < m && board[r][nc]) {
				q.emplace(r, nc);
				board[r][nc] = 0;
			}
		}
	}
	return size;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;

	cin >> n >> m;

	int count = 0, res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!board[i][j]) continue;
			count++;
			int a = bfs(i, j, n, m);
			res = max(res, a);
		}
	}

	cout << count << endl;
	cout << res << endl;
	return 0;
}