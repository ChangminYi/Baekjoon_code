#include <iostream>
#include <cmath>

using namespace std;

int n, t;
int presum[50'001];
int dp[4][50'001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 각각의 열차가 직전까지 끌 수 있는 최대치와
    * 직전 열차가 끌지 않는 부분부터의 최대치 중
    * 더 큰 값이 현재 열차까지 끌 수 있는 최대값.
    */

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> presum[i];
        presum[i] += presum[i - 1];
    }
    cin >> t;

    for (int i = 1; i <= 3; i++) {
        for (int j = i * t; j <= n; j++) {
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - t] + (presum[j] - presum[j - t]));
        }
    }

    cout << dp[3][n];

    return 0;
}