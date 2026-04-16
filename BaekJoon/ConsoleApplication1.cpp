#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int p[4] = { 15,20,9,14 };
	int w[4] = { 3,5,3,4 };
	int m = 10;
	vector<vector<double>> dp(5, vector<double>(m + 1)); // 물품 수, 무게

	//dp[0][0~m] = 물건을 하나도 선택 안함 -> 전부 0
	//dp[i] i번째 물건을 고려함
	for (int i = 1; i <= 4; i++)
	{
		int curw = w[i - 1];
		int curval = p[i - 1];

		for (int j = 1; j <= m; j++)
		{
			// 현재 짐을 넣거나 dp[i-1][j-curw] + curval
			// 넣치 않거나 dp[i-1][j]

			// 현재 무게 j가 물체의 무게 curw 이상일 때만 계산
			if (curw <= j)
			{
				// 이전 물체의 최대 무게 계산 vs 
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - curw] + curval);
			}
			else dp[i][j] = dp[i - 1][j];
		}
	}

	cout << dp[4][10];
	return 0;
}