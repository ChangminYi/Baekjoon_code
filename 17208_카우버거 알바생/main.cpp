#include <iostream>
#include <cmath>

using namespace std;

int n, m, k;
int cost[301][2], dp[101][301][301];

int main() {
    /**
     * 냅색 문제. 한 주문이 두 개의 물건으로 나눠지기 때문에,
     * 기존의 2차원 배열이 아니라 3차원 배열로 변형하여 풀 수 있음.
     * m과 3중 for문의 j는 치즈버거, k와 3중 for문의 v는 감자튀김을 담당.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        cin >> cost[i][0] >> cost[i][1];
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            for(int v = 1; v <= k; v++) {
                dp[i][j][v] = dp[i - 1][j][v];
                if(j >= cost[i][0] && v >= cost[i][1]) {
                    dp[i][j][v] = max(dp[i][j][v], dp[i - 1][j - cost[i][0]][v - cost[i][1]] + 1);
                }
            }
        }
    }

    cout << dp[n][m][k];

    return 0;
}