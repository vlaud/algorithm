#include <iostream>
#include <vector>

using namespace std;

/* lower_bound: 타겟과 같거나 큰 첫번째 원소 */
/* upper_bound: 타겟보다 큰 첫번째 원소 */

int bound(vector<int>& arr, int target, bool lower = true)
{
	int l = 0, r = arr.size() - 1;

	while (l < r)
	{
		int m = l + (r - l) / 2;

		bool v = lower ? arr[m] < target : arr[m] <= target;

		if (v) l = m + 1;
		else r = m;
	}

	return r;
}

int main()
{
	vector<int> arr = { 1,2,3,3,3,3,4,5 };
	// lower_bound
	int idx = bound(arr, 3);
	printf("lower_bound: arr[%d] = %d\n", idx, arr[idx]);

	// upper_bound
	idx = bound(arr, 3, false);
	printf("upper_bound: arr[%d] = %d\n", idx, arr[idx]);
	return 0;
}