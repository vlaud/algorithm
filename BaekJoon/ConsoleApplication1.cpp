#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <string>

using namespace std;

#define endl "\n"

int maximumLength(string s) {
	int n = s.size();
	int l = 1, r = n;

	auto getSpecial = [s, n](int size) {
		int p = 0;
		vector<int> letters(26, 0);

		for (int i = 0; i < n; i++) {
			if (s[i] != s[p]) p = i;
			if (i - p + 1 >= size) letters[s[i] - 'a']++;
			if (letters[s[i] - 'a'] > 2) return true;
		}
		return false;
		};

	if (!getSpecial(1)) return -1;

	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (getSpecial(mid)) l = mid;
		else r = mid;
	}
	return l;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	string s = "aabccc";
	cout << maximumLength(s) << endl;
	return 0;
}