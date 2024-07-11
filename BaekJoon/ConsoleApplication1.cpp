#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int* primeNumbers(int num) {

	int* getNum = new int[num + 1];
	int amount = num - 1;

	getNum[0] = -1;
	getNum[1] = -1;

	for (int i = 2; i <= num; i++) {
		getNum[i] = i;
	}

	for (int i = 2; i * i <= num; i++) {
		// primeNum[i] 가 -1이면 이미 소수가 아니므로 continue
		if (getNum[i] == -1) {
			continue;
		}
			
		// i*k (k<i) 까지의 수는 이미 검사했으므로 j는 i*i 부터 검사해준다.
		for (int j = i * i; j <= num; j += i) {
			if (getNum[j] == -1) {
				continue;
			}
			getNum[j] = -1;
			amount--;
		}
	}

	int idx = 2;
	int* primeNum = new int[amount + 1];

	primeNum[0] = amount;

	for (int i = 1; i <= amount; i++) {
		for (int j = idx; j < num + 1; j++) {
			if (getNum[j] != -1) {
				primeNum[i] = getNum[j];
				idx = j + 1;
				break;
			}
		}
	}
	
	return primeNum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int number = 0;

	cin >> number;

	for (int i = 1; i <= primeNumbers(number)[0]; i++) {
		cout << primeNumbers(number)[i] << " ";
	}

	return 0;
}