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
    * (i, j)���� ������ �� �� �ִ� ����,
    * (i + 1, j)�� (i + 1, j + 1) �� ���̴�.
    * ��ȭ������ ���� ��� ������Ʈ�Ͽ�,
    * ������ �࿡�� �ִ��� ����ϸ� �ȴ�.
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