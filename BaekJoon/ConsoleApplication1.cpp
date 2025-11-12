#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using ll = long long;
using iPair = pair<int, int>;

iPair xa[100000];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, idx = 0;
	ll sum = 0;
	
	cin >> n;
	
	for (int i = 0; i<n; i++){
		cin >> xa[i].first >> xa[i].second;
		sum += xa[i].second;
	}

	sort(xa, xa + n);

	for (int i = 0; i < n; i++) {
		sum -= 2 * xa[i].second;
		if (sum <= 0) {
			cout << xa[i].first;
			break;
		}
	}

	return 0;
}
