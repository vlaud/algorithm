#include <iostream>
#include <list>
#include <string>

#define endl '\n'
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s;
    cin >> s;
    list<char> mp;
    
    for (char& c : s) mp.emplace_back(c);
    auto t = mp.end();
    int n;
    char input;
    
    cin >> n;
    while (n--) {
        cin >> input;

        if (input == 'L') {
            if (t != mp.begin()) {
                t--;
            }
        }
        else if (input == 'D') {
            if (t != mp.end()) {
                t++;
            }
        }
        else if (input == 'B') {
            if (t != mp.begin()) {
                t--;
                t = mp.erase(t);
            }
        }
        else {
            cin >> input;
            mp.insert(t, input);
        }
    }

    for (auto i : mp) cout << i;
    return 0;
}