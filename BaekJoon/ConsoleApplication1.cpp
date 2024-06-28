#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N;

    vector<int> prices(N);

    /*for (int i = 0; i < N; i++) {
        cin >> prices[i];
    }

    // N이 1이면 범위를 벗어나기에 쓰면 안됨

    int min1 = *min_element(prices.begin() + 1, prices.end());
    int index1 = min_element(prices.begin() + 1, prices.end()) - prices.begin();

    int min2 = *min_element(prices.begin(), prices.end());
    int index2 = min_element(prices.begin() , prices.end()) - prices.begin();*/

    //cout << "min1 = " << min1 << ", min2 = " << min2 << "\n";

    int min1 = 50, min2 = 50;
    int index1 = 0, index2 = 0;

    for (int i = 0; i < N; i++) {
        cin >> prices[i];
        if (i > 0 && prices[i] < min1) {
            min1 = prices[i];
            index1 = i;
        }
        if (prices[i] < min2) {
            min2 = prices[i];
            index2 = i;
        }
    }

    cin >> M;

    if (M < min1) {
        cout << "0\n";
        return 0;
    }

    vector<int> result;

    while (M >= min2) {
        if (result.empty()) {
            M -= min1;
            result.push_back(index1);
        }
        else {
            M -= min2;
            result.push_back(index2);
        }
    }

    int price = min1 + M;
    for (int i = 0; i < result.size(); i++) {
        for (int j = N - 1; j >= 0; j--) {
            if (price >= prices[j]) {
                result[i] = j;
                price = min2 + price - prices[j];
                break;
            }
        }
    }

    for (int num : result) {
        cout << num;
    }
    cout << "\n";

    return 0;
}
