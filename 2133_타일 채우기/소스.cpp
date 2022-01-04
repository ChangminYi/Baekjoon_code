#include <iostream>

using namespace std;

int n;
int dp[31];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * n이 홀수이면 반드시 채울 수 없다.
    * 짝수라면, 경우를 잘 조합하여 점화식을 세우면 된다.
    */
    cin >> n;
    if (n & 1) {
        cout << 0;
    }
    else {
        dp[0] = 1, dp[1] = 0, dp[2] = 3;
        for (int i = 4; i <= n; i++) {
            dp[i] = dp[i - 2] * dp[2];
            for (int j = i - 4; j >= 0; j -= 2) {
                dp[i] += 2 * dp[j];
            }
        }

        cout << dp[n];
    }

    return 0;
}