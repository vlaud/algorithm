#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

#define PRIME 7919

int res = 7;

int ymin = 1, xmin = 1;
int ymax = INT_MAX, xmax = INT_MAX;

struct HASH
{
	string key;

	HASH(string key) : key(key) {}
};

list<HASH*> hmap[PRIME];

uint64_t gethash(string& s)
{
	uint64_t hash = 5381;

	for (char c : s)
	{
		hash = (hash << 5) + hash + c;
	}

	return hash;
}

bool exist(string& s, int& h)
{
	if (hmap[h].empty()) return false;

	for (auto it = hmap[h].begin(); it != hmap[h].end(); it++)
	{
		if ((*it)->key == s) return true;
	}
	return false;
}

void insert(string& s, int& h)
{
	hmap[h].emplace_back(new HASH(s));
}

string vecToString(vector<string>& mat)
{
	string s;
	for (string c : mat)
	{
		s += c;
	}
	return s;
}

vector<int> maketable(string& pat)
{
	int n = pat.size();
	vector<int> table(n, 0);

	int len = 0;

	for (int i = 1; i < n; i++)
	{
		while (len != 0 && pat[len] != pat[i]) len = table[len - 1];

		if (pat[len] == pat[i])
		{
			table[i] = ++len;
		}
	}
	return table;
}

bool search(string& s, string& pat, vector<int>& table)
{
	int n = s.size();
	int m = pat.size();
	int len = 0;

	for (int i = 0; i < n; i++)
	{
		while (len != 0 && pat[len] != s[i]) len = table[len - 1];

		if (pat[len] == s[i])
		{
			if (len == m - 1) return true;
			else len++;
		}
	}

	return false;
}

void spin(vector<string>& mat, int r, int c, bool right = true)
{
	int n = mat.size(), m = mat[0].size();

	if (right)
	{
		for (int i = -1; i < 1; i++)
		{
			for (int j = i + 1; j < 2; j++)
			{
				swap(mat[r + i][c + j], mat[r + j][c + i]);
			}
		}
	}
	else
	{
		for (int i = -1; i < 1; i++)
		{
			for (int j = -1; j < -i; j++)
			{
				swap(mat[r + i][c + j], mat[r - j][c - i]);
			}
		}
	}

	for (int i = r - 1; i <= r + 1; i++)
	{
		swap(mat[i][c - 1], mat[i][c + 1]);
	}
}

void findcomb(vector<string>& mat, string& pat, vector<int>& table, int level, int cnt)
{
	for (int i = 0; i < mat.size(); i++)
	{
		if (search(mat[i], pat, table))
		{
			res = min(cnt, res);
			return;
		}
	}

	string s = vecToString(mat);

	int h = gethash(s) % PRIME;
	if (level == 6 || exist(s, h)) return;

	insert(s,h);
	
	for (int i = ymin; i <= ymax; i++)
	{
		for (int j = xmin; j <= xmax; j++)
		{
			spin(mat, i, j);
			findcomb(mat, pat, table, level + 1, cnt + 1);
			spin(mat, i, j, false);
		}
	}
}

int main()
{
	vector<string> mat;

	string s;
	while (true)
	{
		getline(cin, s);
		if (s.empty()) break;
		mat.emplace_back(s);
	}
	string pat = "AAA";
	vector<int> table = maketable(pat);

	ymax = mat.size() - 2;
	xmax = mat[0].size() - 2;

	findcomb(mat, pat, table, 0, 0);

	cout << (res == 7 ? "불가능" : "가능") << endl;
	return 0;
}
