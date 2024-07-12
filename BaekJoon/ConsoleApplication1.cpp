#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> primeNumbers(int num) {

	vector<int> getNum(num + 1);
	vector<int> primeNum;

	getNum[0] = -1;
	getNum[1] = -1;

	for (int i = 2; i <= num; i++) {
		getNum[i] = i;
	}

	for (int i = 2; i * i <= num; i++) {
		// primeNum[i] 가 -1이면 이미 소수가 아니므로 continue
		if (getNum[i] == -1) {
			cout << "i = " << i << "번째 패스" << "\n";
			continue;
		}
			
		// i*k (k<i) 까지의 수는 이미 검사했으므로 j는 i*i 부터 검사해준다.
		for (int j = i * i; j <= num; j += i) {
			if (getNum[j] == -1) {
				cout << "j = " << j << "번째 패스" << "\n";
				continue;
			}
			cout << "i = " << i << ", j = " << j << "번째 계산중" << "\n";
			getNum[j] = -1;
		}
	}
	
	for (int num : getNum) {
		if (num != -1) primeNum.push_back(num);
	}
	
	return primeNum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int number = 0;

	cin >> number;

	auto primeNum = primeNumbers(number);

	for (int i = 0; i < primeNum.size(); i++) {
		cout << primeNum[i] << " ";
	}

	return 0;
}