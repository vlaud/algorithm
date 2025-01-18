#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;

int partition(vector<int>& arr, int left, int right) {
	int& pivot = arr[right];

	int i = left;
	for (int j = left; j < right; j++) {
		if (arr[j] < pivot) {
			swap(arr[i++], arr[j]);
		}
	}
	swap(arr[i], pivot);
	return i;
}

int partition2(vector<int>& arr, int left, int right) {
	int i = left, j = right, pivot = right;

	while (i < j) {
		while (i < j && arr[i] <= arr[pivot]) i++;
		while (i < j && arr[j] >= arr[pivot]) j--;

		if (i < j) {
			swap(arr[i], arr[j]);
			continue;
		}

		swap(arr[j], arr[pivot]);
	}
	return i;
}

void quickSort2(vector<int>& arr, int left, int right) {
	if (left >= right) return;

	int pi = partition2(arr, left, right);

	quickSort2(arr, left, pi - 1);
	quickSort2(arr, pi + 1, right);
}
void quickSort(vector<int>& arr, int left, int right) {
	int i = left, j = right, pivot = right;

	while (i < j) {
		while (i < j && arr[i] <= arr[pivot]) i++;
		while (i < j && arr[j] >= arr[pivot]) j--;

		if (i < j) {
			swap(arr[i], arr[j]);
			continue;
		}

		swap(arr[j], arr[pivot]);
		quickSort(arr, left, i - 1);
		quickSort(arr, i + 1, right);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<int> arr = { 1, 2, 8, 7, 4, 6, 3, 2, 4 };
	quickSort(arr, 0, arr.size() - 1);

	for (int it : arr) cout << it << " ";
	cout << endl;

	vector<int> arr2 = { 1, 2, 8, 7, 4, 6, 3, 2, 4 };
	quickSort2(arr2, 0, arr2.size() - 1);

	for (int it : arr2) cout << it << " ";

	cout << endl;
	return 0;
}