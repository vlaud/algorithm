#include <iostream>
#include <vector>

using namespace std;

vector<int> bad_char(string& pattern)
{
	int n = pattern.size();

	vector<int> bd(256, n);

	for (int i = 0; i < n; i++)
	{
		bd[pattern[i]] = i;
	}
	return bd;
}

vector<int> make_good(string& pattern)
{
	int n = pattern.size();

	int p = n;
	int sp = p + 1;

	// 접미사 동일 문자열 체크 테이블
	vector<int> suffix(n + 1, 0);
	suffix[n] = sp;
	// 스킵 테이블
	vector<int> skip(n + 1, 0);

	// 역 preKMP
	while (p > 0)
	{
		while (sp <= n && pattern[p - 1] != pattern[sp - 1])
		{
			if (skip[sp] == 0) 
				skip[sp] = sp - p;
			sp = suffix[sp];
		}
		suffix[--p] = --sp;
	}

	sp = suffix[0];

	while (p < n)
	{
		if (skip[p] == 0)
			skip[p] = sp;
		if (p++ == sp)
			sp = suffix[sp];
	}

	return skip;
}

void search(vector<int>& bad, vector<int>& good, string& s, string& pattern)
{
	int n = s.size(), m = pattern.size();

	int b = 0;

	if (n < m) return;

	while (b <= n - m)
	{
		int match = m;

		while (match != 0 && pattern[match - 1] == s[b + match - 1]) --match;

		if (!match)
		{
			cout << b << " ";
		}

		char c = s[b + match];
		int shift = bad[c];
		int goodshift = good[match];
		if (shift != m)
		{
			b += max(match - shift, good[match]);
		}
		else b += max(match, good[match]);
	}
}
int main()
{
	string h = "abztyaababbababttbcabbabatdwcaabbabczzba";
	string pattern = "abbab";
	const int p_size = pattern.size();

	vector<int> bad = bad_char(pattern);
	vector<int> good = make_good(pattern);
	search(bad, good, h, pattern);
	return 0;
}