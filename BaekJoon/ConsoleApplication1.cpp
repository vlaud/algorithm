#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;
using int2d = vector<vector<int>>;
#define endl "\n"

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];

    while (low < high) {

        // Find leftmost element greater than or
        // equal to pivot
        while (arr[low] < pivot) low++;

        // Find rightmost element smaller than 
        // or equal to pivot
        while (arr[high] > pivot) high--;

        // If two pointers met.
        if (low < high) {
            swap(arr[low], arr[high]);
            low++;
        }
    }
    return low;
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {

        /* pi is partitioning index, arr[pi] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before 
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi, high);
    }
}
void quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low >= high) return;

    int pi = partition(arr, low, high);

    if (k <= pi) quickSelect(arr, low, pi - 1, k);
    else quickSelect(arr, pi, high, k);
}
/* Function to print an array */
void printArray(const vector<int>& arr) {
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

// Driver Code
int main() {
    vector<int> arr = { 10, 7 };
    int k = 2;
    printArray(arr);
    quickSelect(arr, 0, arr.size() - 1, k);
    printArray(vector<int>(arr.begin(), arr.begin()+k));
    printArray(arr);
    return 0;
}