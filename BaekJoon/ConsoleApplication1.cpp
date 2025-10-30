#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

#define endl '\n'
using namespace std;

const int MX = 1000005;
int dat[MX];
int pos = 0;

void push(int x) {
	dat[pos++] = x;
}

void pop() {
	pos--;
}

int top() {
	return dat[pos-1];
}


int main(void) {
	stack<int> st;

	int n;

	cin >> n;

	string input;
	for (int i = 0; i < n; i++) {
		cin >> input;
		if (input == "push") {
			cin >> input;
			st.push(stoi(input));
		}
		else if (input == "pop") {
			if (st.empty()) cout << -1 << endl;
			else {
				cout << st.top() << endl;
				st.pop();
			}
		}
		else if (input == "size") {
			cout << st.size() << endl;
		}
		else if (input == "empty") {
			cout << st.empty() << endl;
		}
		else {
			if (st.empty()) cout << -1 << endl;
			else cout <<  st.top() << endl;
		}
	}

	return 0;
}