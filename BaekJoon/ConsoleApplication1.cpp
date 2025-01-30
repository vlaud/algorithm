#include<iostream>
#include<algorithm>
#include <vector>
using namespace std;
using int2d = vector<vector<int>>;

void mow_the_lawn(int k, vector<pair<vector<int>, vector<int>>>& operations) {
    vector<vector<int>> grid(10, vector<int>(10, 1));

    for (int week = 0; week < k; ++week) {
        vector<int>& rows = operations[week].first;
        vector<int>& cols = operations[week].second;

        // 선택된 행과 열을 미리 1로 설정
        vector<bool> row_cut(10, false), col_cut(10, false);
        for (int r : rows) row_cut[r - 1] = true;
        for (int c : cols) col_cut[c - 1] = true;

        // 성장 (잔디 깎이지 않는 칸만 증가)
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (!row_cut[i] && !col_cut[j]) {
                    grid[i][j] += 1;
                }
            }
        }

        // 잔디 깎기
        for (int r : rows) fill(grid[r - 1].begin(), grid[r - 1].end(), 1);
        for (int c : cols) {
            for (int i = 0; i < 10; ++i) grid[i][c - 1] = 1;
        }
    }

    for (const auto& row : grid) {
        for (int height : row) cout << height << " ";
        cout << endl;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int k;
    cin >> k; // 주어진 주 수

    vector<pair<vector<int>, vector<int>>> operations(k);

    // k개의 주에 대해 입력 받기
    for (int i = 0; i < k; ++i) {
        vector<int> rows(3), cols(3);
        for (int j = 0; j < 3; ++j) cin >> rows[j]; // 3개의 행 정보 입력
        for (int j = 0; j < 3; ++j) cin >> cols[j]; // 3개의 열 정보 입력
        operations[i] = { rows, cols };
    }

    // 결과 계산 및 출력
    mow_the_lawn(k, operations);

    return 0;
}