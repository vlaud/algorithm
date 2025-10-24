#include <iostream>
#include <list>
#include <string>
#include <algorithm>

#define endl '\n'
using namespace std;

const int mx = 1000005;
char dat[mx];
int prv[mx], nxt[mx];
int unused = 1; //tail = 0;

void insert(int adrs, char val) {
	dat[unused] = val;
	prv[unused] = adrs;
	nxt[unused] = nxt[adrs];

	if (nxt[adrs] != -1) prv[nxt[adrs]] = unused;
	//else tail = unused;

	nxt[adrs] = unused;

	unused++;
}

void erase(int adrs) {
	nxt[prv[adrs]] = nxt[adrs];

	if (nxt[adrs] != -1) prv[nxt[adrs]] = prv[adrs];
	//else tail = prv[adrs];


	//unused--;
}

void priting() {
	int cur = nxt[0];
	while (cur != -1) {
		cout << dat[cur];
		cur = nxt[cur];
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	fill(prv, prv + mx, -1);
	fill(nxt, nxt + mx, -1);
	string s;
	cin >> s;
	int p = 0;

	for (char c : s) {
		insert(p, c);
		p++;
	}

	int n = 0;
	char input;
	
	cin >> n;
	while (n--) {
		cin >> input;

		if (input == 'P') {
			cin >> input;
			insert(p, input);
			p = nxt[p];
		}
		else if (input == 'L') {
			if (prv[p] != -1) p = prv[p];
		}
		else if (input == 'D') {
			if (nxt[p] != -1) p = nxt[p];
		}
		else {
			if (prv[p] != -1) {
				erase(p);
				p = prv[p];
			}
		}
	}
	priting();
	return 0;
}