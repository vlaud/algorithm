#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

int logg[10000];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	int n;
	while (t--) {
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> logg[i];
		}
		sort(logg, logg + n);

		int size = logg[1] - logg[0];
		size = max(size, logg[n - 1] - logg[n - 2]);

		for (int i = 0; i < n-2; i++) {
			size = max(size, logg[i + 2] - logg[i]);
		}

		cout << size << endl;
	}
	return 0;
}