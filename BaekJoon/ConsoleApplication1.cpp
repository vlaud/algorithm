#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using int2d = vector<vector<int>>;
using ll = long long;

int2d twoSum(vector<int> arr, int s, int n, ll target)
{
	int2d res;
	int l = s, r = n - 1;

	while (l < r)
	{
		ll sum = arr[l] + arr[r];
		if (sum == target)
		{
			res.emplace_back(vector<int>({ arr[l++], arr[r--] }));
			while (l < r && arr[l] == arr[l - 1]) l++;
			while (l < r && arr[r] == arr[r + 1]) r--;
		}
		else if (sum < target) l++;
		else r--;
	}
	return res;
}
int2d kSum(vector<int> arr, int s, int n, int k, ll target)
{
	int2d res;

	if (s == n) return res;

	ll average = target / k;

	if (average < arr[s] || arr.back() < average) return res;

	if (k == 2) return twoSum(arr, s, n, target);

	for (int i = s; i < n; i++)
	{
		if (s != i && arr[i] == arr[i - 1]) continue;

		for (auto& sub : kSum(arr, i + 1, n, k - 1, static_cast<ll>(target - arr[i])))
		{
			res.emplace_back(vector<int>({ arr[i] }));
			res.back().insert(res.back().end(), sub.begin(), sub.end());
		}
	}

	return res;
}

int2d GetKSum(vector<int> arr, int k, ll target)
{
	sort(arr.begin(), arr.end());
	return kSum(arr, 0, arr.size(), k, target);
}
int main()
{
	vector<int> arr = { 1,0,-1,0,-2,2 };

	for (auto& sub : GetKSum(arr, 4, 0))
	{
		for (auto& i : sub)
		{
			printf("%d ", i);
		}
		cout << endl;
	}
	return 0;
}