#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

#define endl '\n'

vector<int> grp[26];
vector<int> idg(26);
vector<int> days(26);
vector<long long> cache(26);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string j;
    
    while (true) {
        getline(cin, j);

        if (j.empty()) break;

        stringstream ss(j);
        string tmp;
        vector<string> strs;

        while (getline(ss, tmp, ' ')) {
            strs.emplace_back(tmp);
        }
        int num = strs[0][0] - 'A';
        days[num] = stoi(strs[1]);

        if (strs.size() == 2) continue;

        for (char& c : strs[2]) {
            c -= 'A';
            grp[c].emplace_back(num);
            idg[num]++;
        }
    }
    queue<int> q;
    long long res = 0;

    for (int i = 0; i < 26; i++) {
        if (!idg[i] && days[i]) {
            cache[i] = static_cast<long long>(days[i]);
            res = max(res, cache[i]);
            q.emplace(i);
        }
    }

    while (!q.empty()) {
        int x = q.front(); q.pop();

        for (int& i : grp[x]) {
            cache[i] = max(cache[i], cache[x] + static_cast<long long>(days[i]));
            res = max(res, cache[i]);
            if (--idg[i] == 0) q.emplace(i);
        }
    }
    cout << res << endl;
    return 0;
}