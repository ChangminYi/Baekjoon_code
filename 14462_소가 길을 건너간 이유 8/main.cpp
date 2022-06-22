#include <iostream>
#include <cmath>

using namespace std;

int n;
int arg[1001][2], dp[1001][1001];

int main() {
    /**
     * 현재의 직전에 이은 횡단보도의 최댓값을 가져온 후,
     * 현재 목초지의 숫자 차가 4 이하이면 새로 횡단보도를 잇는다.
     * 이를 dp로 풀어내면 dp[n][n]이 정답이다.
     */
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < 2; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> arg[j][i];
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if(abs(arg[i][0] - arg[j][1]) <= 4) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }

    cout << dp[n][n];

    return 0;
}