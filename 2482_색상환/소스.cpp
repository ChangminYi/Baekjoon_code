#include <iostream>

using namespace std;

const int MAX = 1000;
const int MOD = 1000000003;

int n, k;
int dp[MAX + 1][MAX + 1] = { 0 };

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;

    // i개 중 0개를 선택하는 경우는 1개, i개 중 1개를 선택하는 경우는 i개.
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
        dp[i][1] = i;
    }

    /*
    * dp[i-2][j-1]: 2번째 전, 즉 인접하지 않은 색상환까지의 경우의 수
    * dp[i-1][j]: 인접한 색상환까지의 경우의 수
    */
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            dp[i][j] = (dp[i - 2][j - 1] + dp[i - 1][j]) % MOD;
        }
    }

    /*
    * n번째 칸을 칠하는 경우, 1과 n - 1번 칸을 칠하면 안된다.
    * 또한, n번째 칸을 칠하지 않으면, n-1까지 k개를 칠하는 경우와 같다.
    */
    cout << (dp[n - 1][k] + dp[n - 3][k - 1]) % MOD;

    return 0;
}