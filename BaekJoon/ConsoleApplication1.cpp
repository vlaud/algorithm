#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;

	cin >> N >> K;

	vector<int> coins(N);

	for (int i = 0; i < N; i++) {
		cin >> coins[i];
	}

	int result = 0;

	for (int i = N - 1; i >= 0; i--) {
		if (K <= 0) break;

		if (K >= coins[i]) {
			result += K / coins[i];
			K = K % coins[i];
			
		}
	}

	cout << result;

	return 0;
}