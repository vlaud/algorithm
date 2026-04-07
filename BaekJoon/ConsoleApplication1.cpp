#include <iostream>

using namespace std;

int arr[6] = { 1,5,4,2,-5,-7 };

int partition(int l, int r)
{
	int p = arr[r];

	for (int i = l; i < r; i++)
	{
		if (p >= arr[i])
		{
			swap(arr[l++], arr[i]);
		}
	}
	swap(arr[l], arr[r]);

	return l;
}

int kSelect(int l, int r, int k)
{
	while (l <= r)
	{
		int m = partition(l, r);
		if (k == m) return m;
		else if (m < k) l = m + 1;
		else r = m - 1;
	}
	return -1;
}
int main()
{
	int n;
	cin >> n;
	n = 6 - n;
	int idx = kSelect(0, 5, n);
	cout << arr[idx];
	return 0;
}