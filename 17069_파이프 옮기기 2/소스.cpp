#include <iostream>

using namespace std;

int n;
int board[34][34];
long long dp[3][34][34];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 파이프의 위치와 방향까지도 같이 생각해야 한다.
    * 따라서 dp를 3차원으로 선언하여 방향, 행, 열로 표현하였다.
    */

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }

    dp[0][1][2] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (board[i][j + 1] == 0) dp[0][i][j + 1] += dp[0][i][j] + dp[2][i][j];
            if (board[i + 1][j] == 0) dp[1][i + 1][j] += dp[1][i][j] + dp[2][i][j];
            if (board[i + 1][j + 1] == 0 && board[i + 1][j] == 0 && board[i][j + 1] == 0) {
                dp[2][i + 1][j + 1] += dp[0][i][j] + dp[1][i][j] + dp[2][i][j];
            }
        }
    }

    cout << dp[0][n][n] + dp[1][n][n] + dp[2][n][n];

    return 0;
}