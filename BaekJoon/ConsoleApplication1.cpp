#include <iostream>
#include <stack>
using namespace std;

#define endl '\n'
#define ll long long

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;

    while (true) {
        cin >> n;
        if (!n) break;

        stack<pair<int,int>> st;
        ll size = 0;
        for (int i = 0; i <= n; i++) {
            int num;
            if (i != n) cin >> num;
            while (!st.empty() && (i == n || st.top().first > num)) {
                ll h = st.top().first; st.pop();
                int w = st.empty() ? i : i - st.top().second - 1;
                size = max(size, h * w);
            }
            
            st.emplace(pair<int,int>({ num, i }));
        }
        cout << size << endl;
    }

    return 0;
}