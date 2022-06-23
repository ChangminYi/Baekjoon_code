#include <iostream>

using namespace std;

const int INF = INT32_MAX / 2;

int n, k;
int dp[10'001];

int main() {
    /**
     * dp를 사용하여 해결할 수 있음.
     * 현재 가격의 최솟값은 현재 가격엣 각 동전의 값만큼 뺀 가격들에
     * 도착할 수 있는 최소 횟수에 1을 더한 값이다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    fill(dp + 1, dp + k + 1, INF);
    for(int i = 0, coin; i < n; i++) {
        cin >> coin;
        for(int j = coin; j <= k; j++) {
            dp[j] = min(dp[j], dp[j - coin] + 1);
        }
    }

    cout << (dp[k] >= INF ? -1 : dp[k]);

    return 0;
}