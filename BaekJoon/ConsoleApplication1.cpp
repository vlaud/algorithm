#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	int result = -1;
	cin >> N;

	for (int i = N / 5; i >= 0; i--) {
		if ((N - i * 5) % 3 == 0) {
			result = i + (N - i * 5) / 3;
			break;
		}
		
	}

	cout << result;

	return 0;
}