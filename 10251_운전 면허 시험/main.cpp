#include <iostream>
#include <cmath>
#include <memory.h>

using namespace std;

const int INF = 1'000'001;
const int MAX_TURN = 200;

int t, m, n, l, g;
int cost[100][100][2];
int dp[100][100][200][2];

int main() {
    /**
     * dp를 사용하여 해결할 수 있다. 특정 칸에 도달할 때까지의 방향 전환 횟수와 진입 방향을 기억한다.
     * 최소비용을 계산한 후, 최소 방향 전환 수를 찾는다. 이를 통해 사용한 연료량을 계산할 수 있다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> m >> n >> l >> g;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n - 1; j++) {
                cin >> cost[i][j][0];
            }
        }
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                cin >> cost[i][j][1];
            }
        }

        memset(dp, INF, sizeof(dp));
        dp[0][0][0][0] = 0, dp[0][0][0][1] = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < MAX_TURN; k++) {
                    if (i < m - 1) {
                        dp[i + 1][j][k][1] = min(dp[i + 1][j][k][1], dp[i][j][k][1] + cost[i][j][1]);
                        dp[i + 1][j][k + 1][1] = min(dp[i + 1][j][k + 1][1], dp[i][j][k][0] + cost[i][j][1]);
                    }
                    if (j < n - 1) {
                        dp[i][j + 1][k][0] = min(dp[i][j + 1][k][0], dp[i][j][k][0] + cost[i][j][0]);
                        dp[i][j + 1][k + 1][0] = min(dp[i][j + 1][k + 1][0], dp[i][j][k][1] + cost[i][j][0]);
                    }
                }
            }
        }

        int ans = -1;
        for (int i = 0; i < MAX_TURN; i++) {
            if (dp[m - 1][n - 1][i][0] <= g || dp[m - 1][n - 1][i][1] <= g) {
                ans = l * (m + n - 2) + i;
                break;
            }
        }

        cout << ans << '\n';
    } while(--t);

    return 0;
}
