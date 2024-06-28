#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// S(1 ≤ S ≤ 4,294,967,295)
// 범위로 인해 long long 사용
#define ll long long

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ll S;
	ll N = 0;
	ll idx = 0;

	cin >> S;

	while (N <= S) {
		idx++;
		N += idx;
	}

	cout << idx - 1;

	return 0;
}