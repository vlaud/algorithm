#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <algorithm>

using namespace std;
using str2d = vector<vector<string>>;

/// <summary>
/// 서로소 집합
/// </summary>
class dsu
{
private:
	vector<int> par, size;
public:
	/// <summary>
	/// n의 크기만큼 각 원소들의 집합 생성
	/// 각 부모의 원소는 자기 자신, 크기는 1로 초기화
	/// </summary>
	/// <param name="n"></param>
	dsu(int n)
	{
		par.resize(n);
		iota(begin(par), end(par), 0);
		size.resize(n, 1);
	}

	/// <summary>
	/// 원소의 부모 찾기
	/// </summary>
	/// <param name="x"></param>
	/// <returns></returns>
	int find(int x)
	{
		while (x != par[x])
		{
			par[x] = par[par[x]];
			x = par[x];
		}
		return x;
	}

	/// <summary>
	/// a와 b를 합친 집합
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	void merge(int a, int b)
	{
		a = find(a);
		b = find(b);

		if (a == b) return;

		if (size[a] < size[b])
		{
			swap(a, b);
		}

		par[b] = a;
		size[a] += size[b];
	}
};


int main()
{
	str2d emails =
	{
		{"tom", "tom@aa", "tom@bb"},
		{"jin", "jin@cc", "jin@dd"},
		{"tom", "tom@cc", "tom@dd"},
		{"jin", "jin@ss", "jin@tt"},
		{"tom", "tom@bb", "tom@cc"},
	};

	int n = emails.size();

	unordered_map<string, int> mp;
	dsu ds(n);

	
	for (int i = 0; i < n; i++)
	{
		// 이름 (0번 원소는) 스킵
		for (int j = 1; j < emails[i].size(); j++)
		{
			// 해시맵에 이메일이 있으면 병합
			// 없으면 i 인덱스 (이메일 주인 인덱스)를 삽입
			auto& e = emails[i][j];
			if (mp.find(e) != mp.end()) ds.merge(mp[e], i);
			else mp[e] = i;
		}
	}

	// 임시 2차원 벡터 생성
	str2d temp(n);
	for (auto [e, i] : mp)
	{
		// 해시맵에 저장된 인덱스의 부모 찾기
		int par = ds.find(i);

		// 부모 인덱스 위치에 이메일 삽입
		temp[par].emplace_back(e);
	}

	str2d res;
	for (int i = 0; i < n; i++)
	{
		if (temp[i].empty()) continue;

		// 이메일을 정렬
		sort(begin(temp[i]), end(temp[i]));

		// 이메일 주인의 이름을 먼저 삽입 후 소유한 이메일들을 뒤에 붙인다
		res.emplace_back(vector<string>({ emails[i][0] }));
		res.back().insert(res.back().end(), temp[i].begin(), temp[i].end());
	}

	for (auto& e : res)
	{
		for (string& s : e)
		{
			printf("%s ", s.c_str());
		}
		cout << endl;
	}

	return 0;
}