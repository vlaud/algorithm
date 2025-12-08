#include <iostream>
#include <algorithm>
using namespace std;

#define endl '\n'

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, k;

	cin >> n >> k;


	int mx = 0;

	while (--n) {
		int x; cin >> x;
		if (mx > x + k) {
			cout << "NO" << endl;
			return 0;
		}
		mx = max(x, mx);
	}

	cout << "YES" << endl;
	return 0;
}