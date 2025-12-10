#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#define endl '\n'
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, x = 0;

    cin >> n >> m;
    vector<int> prev(m), cur(m);
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '0') {
                cur[j] = 0;
                continue;
            }
            
            if (i == 0 || j == 0) cur[j] = 1;
            else cur[j] = min({cur[j-1], prev[j-1], prev[j]}) + 1;

            x = max(cur[j], x);
        }
        prev = cur;
    }
    cout << x * x;
    return 0;
}