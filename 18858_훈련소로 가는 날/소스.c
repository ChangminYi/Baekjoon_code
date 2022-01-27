#include <stdio.h>

long long MOD = 998244353, NOT_VISIT = -1, sum = 0;
int n, m;
long long dp[1001][101][3];

long long get_dp(int r, int c, int d) {
    if(dp[r][c][d] == NOT_VISIT) {
        if (r == n) {
            dp[r][c][d] = 1;
        }
        else {
            dp[r][c][d] = 0;
            if (d == 2) {
                dp[r][c][d] = (dp[r][c][d] + get_dp(r + 1, c, 0)) % MOD;
                for (int i = c + 1; i <= m; i++) {
                    dp[r][c][d] = (dp[r][c][d] + get_dp(r + 1, i, 2)) % MOD;
                }
            }
            else {
                dp[r][c][d] = (dp[r][c][d] + get_dp(r + 1, c, 0)) % MOD;
                for (int i = 1; i < c; i++) {
                    dp[r][c][d] = (dp[r][c][d] + get_dp(r + 1, i, 1)) % MOD;
                }
                for (int i = c + 1; i <= m; i++) {
                    dp[r][c][d] = (dp[r][c][d] + get_dp(r + 1, i, 2)) % MOD;
                }
            }
        }
    }
    return dp[r][c][d];
}

int main(void) {
    scanf("%d %d", &n, &m);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = NOT_VISIT;
        }
    }

    for (int i = 1; i <= m; i++) {
        sum += get_dp(1, i, 0);
        sum %= MOD;
    }

    printf("%lld", sum);

    return 0;
}