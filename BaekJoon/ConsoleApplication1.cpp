#include <iostream>
#include <string>

#define endl '\n'

using namespace std;

const int mx = 1000005;
int dat[2 * mx + 1];
int head = mx, tail = mx;

void push_front(int x) {
	dat[--head] = x;
}

void push_back(int x) {
	dat[tail++] = x;
}

void pop_front() {
	head++;
}

void pop_back() {
	tail--;
}

int front() {
	return dat[head];
}

int back() {
	return dat[tail - 1];
}

bool empty() {
	return head == tail;
}

int size() {
	return tail - head;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n;

	cin >> n;

	string s;
	int a;
	while (n--) {
		cin >> s;

		if (s == "push_front") {
			cin >> a;
			push_front(a);
		}
		else if (s == "push_back") {
			cin >> a;
			push_back(a);
		}
		else if (s == "pop_front") {
			if (!empty()) {
				cout << front() << endl;
				pop_front();
			}
			else cout << -1 << endl;
		}
		else if (s == "pop_back") {
			if (!empty()) {
				cout << back() << endl;
				pop_back();
			}
			else cout << -1 << endl;
		}
		else if (s == "size") {
			cout << size() << endl;
		}
		else if (s == "empty") {
			cout << (empty()) << endl;
		}
		else if (s == "front") {
			if (!empty()) cout << front() << endl;
			else cout << -1 << endl;
		}
		else {
			if (!empty()) cout << back() << endl;
			else cout << -1 << endl;
		}
	}

	return 0;
}
