#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

#define endl '\n'

using namespace std;

string binary(float num) {
	if (!num) return "0";

	string s;

	int digit = num;
	float small = num - digit;

	if (!digit) s += '0';
	
	while (digit) {
		s += (digit % 2) + '0';
		digit /= 2;
	}
	reverse(begin(s), end(s));
	s += '.';
	int time = 8;
	
	while (small && time) {
		
		small *= 2;
		digit = small;
		
		s += (digit + '0');
		small -= digit;
		time--;
	}
	
	return s;
}
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	float n;

	cin >> n;

	cout << binary(n);
	return 0;
}