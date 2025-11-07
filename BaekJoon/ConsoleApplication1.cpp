#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

#define endl '\n'

using namespace std;
const int MX = 1000005;
int dat[MX];
int head = 0, tail = 0;

void push(int x) {
	dat[tail++] = x;
}

void pop() {
	head++;
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

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;

	cin >> n;

	string s;
	//queue<int> q;

	for (int i = 0; i < n; i++) {
		cin >> s;
		if (s == "push") {
			cin >> s;
			//q.emplace(stoi(s));
			push(stoi(s));
		}
		else if (s == "pop") {
			cout << (empty() ? -1 : front()) << endl;
			if (!empty()) pop();
		}
		else if (s == "size") {
			cout << size() << endl;
		}
		else if (s == "empty") {
			cout << empty() << endl;
		}
		else if (s == "front") {
			cout << (empty() ? -1 : front()) << endl;
		}
		else {
			cout << (empty() ? -1 : back()) << endl;
		}
	}
	return 0;
}
/*
push X: 정수 X를 큐에 넣는 연산이다.
pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 큐에 들어있는 정수의 개수를 출력한다.
empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
*/