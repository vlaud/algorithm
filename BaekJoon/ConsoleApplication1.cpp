#include <iostream>
#include <string>
#include <list>

using namespace std;

int res = 7;

int ymin = 1, xmin = 1;
int ymax = INT_MAX, xmax = INT_MAX;

struct HASH
{
	string key;
	int depth;
	HASH(string key, int level) : key(key), depth(level) {}
};

class Unordered_Hash
{
#define PRIME 7919
public:
	Unordered_Hash() : curH()
	{
		hmap = new list<HASH*>[PRIME];
	}

	~Unordered_Hash()
	{
		for (int i = 0; i < PRIME; i++)
		{
			for (HASH* p : hmap[i])
			{
				delete p;
			}
			hmap[i].clear();
		}
	}

	uint64_t gethash(string& s)
	{
		uint64_t hash = 5381;

		for (char c : s)
		{
			hash = (hash << 5) + hash + c;
		}

		return hash;
	}

	HASH* find(string& s)
	{
		if (hmap[curH].empty()) return nullptr;

		for (auto it = hmap[curH].begin(); it != hmap[curH].end(); it++)
		{
			if ((*it)->key == s) return *it;
		}
		return nullptr;
	}

	void insert(string& s, int depth)
	{
		hmap[curH].emplace_back(new HASH(s, depth));
	}

	void setHash(string& s)
	{
		curH = gethash(s) % PRIME;
	}
private:
	list<HASH*> *hmap;
	int curH;
};

int main()
{
	string s = "dfewfwgwgweg";
	Unordered_Hash hs;
	hs.setHash(s);
	if (!hs.find(s)) cout << "없음" << endl;
	hs.insert(s, s.length());
	auto p = hs.find(s);

	cout << p->key << " " << p->depth << endl;
	return 0;
}
