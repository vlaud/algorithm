#include <iostream>
#include <string>
#include <algorithm>

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
	int n;

	cin >> n;

	string input;
	for (int i = 0; i < n; i++) {
		cin >> input;
		if (input == "push") {
			cin >> input;
			push(stoi(input));
		}
		else if (input == "pop") {
			if (!pos) cout << -1 << endl;
			else {
				cout << top() << endl;
				pop();
			}
		}
		else if (input == "size") {
			cout << pos << endl;
		}
		else if (input == "empty") {
			cout << !pos << endl;
		}
		else {
			if (!pos) cout << -1 << endl;
			else cout <<  top() << endl;
		}
	}

	return 0;
}