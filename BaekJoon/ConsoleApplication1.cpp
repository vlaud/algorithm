#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;

#define endl "\n"

int partition(vector<int>& arr, int left, int right) {
    int& pivot = arr[right];
    right--;
    while (1) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;

        if (left >= right) break;
        else {
            swap(arr[left], arr[right]);
            left++;
        }
    }
    swap(arr[left], pivot);

    return left;
}
void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int pi = partition(arr, left, right);

    quickSort(arr, left, pi - 1);
    quickSort(arr, pi + 1, right);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    vector<int> arr = {4,5,2,4,3,2,1,4,4};
    quickSort(arr, 0, arr.size() - 1);

    for (int it : arr) cout << it << " ";
    cout << endl;

    return 0;
}