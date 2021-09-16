#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> argi, dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n);
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        argi[i].resize(i + 1);
        dp[i].resize(i + 1);
        for (int j = 0; j <= i; j++) {
            cin >> argi[i][j];
        }
    }

    /*
    * (i, j)에서 영향을 줄 수 있는 값은,
    * (i + 1, j)와 (i + 1, j + 1) 두 개이다.
    * 점화식으로 값을 계속 업데이트하여,
    * 마지막 행에서 최댓값을 출력하면 된다.
    */
    dp[0][0] = argi[0][0];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + argi[i + 1][j]);
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + argi[i + 1][j + 1]);
        }
    }
    
    int res = 0;
    for (const int& val : dp.back()) {
        res = max(res, val);
    }

    cout << res;

    return 0;
}