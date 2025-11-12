#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using ll = long long;
using iPair = pair<int, int>;

iPair xa[static_cast<int>(1e5)];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, idx = 0;
	ll sum = 0;
	
	cin >> n;
	
	for (int i = 0; i<n; i++){
		cin >> xa[i].first >> xa[i].second;
		xa[i].first += 1e9;
	}

	ll s, l = 0, r = 2e9;
	ll mid = l + (r - l) / 2;

	while (l < r) {
		s = 0;
		for (int i = 0; i < n; i++) {
			s += (abs(xa[i].first - mid - 1) - abs(xa[i].first - mid)) * xa[i].second;
		}
		if (s >= 0) r = mid;
		else l = mid + 1;

		mid = l + (r - l) / 2;
	}

	mid -= 1e9;
	cout << mid;

	return 0;
}
