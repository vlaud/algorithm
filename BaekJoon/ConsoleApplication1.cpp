#include <iostream>
#include <string>
#include <stack>

using namespace std;

#define endl '\n'

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	string j;
	while (true) {
		getline(cin, j);
		if (j == ".") break;
		stack<char> st;

		bool v = true;
		for (char c : j) {
			if (c == '[' || c == '(') {
				st.emplace(c);
				continue;
			}

			if (c == ']' || c == ')') {
				if (st.empty()) {
					v = false;
					break;
				}
				else if (c == ']' && st.top() != '[') {
					v = false;
					break;
				}
				else if (c == ')' && st.top() != '(') {
					v = false;
					break;
				}
				st.pop();
			}
			
		}
		if (!st.empty()) v = false;
		string res = v ? "yes" : "no";
		cout << res << endl;
	}
	return 0;
}