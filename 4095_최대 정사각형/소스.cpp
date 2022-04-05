#include <iostream>
#include <cmath>

using namespace std;

int n, m;
int board[1001][1001], dp[1001][1001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        else {
            int ans = 0;

            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    cin >> board[i][j];
                }
            }

            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    if (board[i][j]) {
                        dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
                    }
                    else dp[i][j] = 0;
                    ans = max(ans, dp[i][j]);
                }
            }

            cout << ans << '\n';
        }
    }

    return 0;
}