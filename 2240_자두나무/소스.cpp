#include <iostream>
#include <cmath>

using namespace std;

int t, w;
bool plum[1001];
int dp[1001][31];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * plum 배열은 1번 자두가 t초에 떨어짐을 의미. 값이 거짓이면 2번에 떨어진다.
    * 움직인 횟수가 홀수이면 2번 밑, 짝수이면 1번 밑에 서 있는 상황이다.
    * 따라서, 직전 시간의 위치가 현재 위치와 같을 때와 아닐 때의 최댓값에,
    * 현재 나무 밑에 자두가 떨어지는지를 확인하여 1씩 더하면 된다.
    * 정답은 t초의 시간에서의 최댓값이 된다.
    */

    cin >> t >> w;
    for (int i = 1, num; i <= t; i++) {
        cin >> num;
        plum[i] = (num == 1);
    }
    
    plum[1] ? dp[1][0] = 1 : dp[1][1] = 1;
    for (int i = 2; i <= t; i++) {
        dp[i][0] = (plum[i] ? dp[i - 1][0] + 1 : dp[i - 1][0]);
        for (int j = 1; j <= w; j += 2) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + (plum[i] ? 0 : 1);
        }
        for (int j = 2; j <= w; j += 2) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + (plum[i] ? 1 : 0);
        }
    }

    int ans = 0;
    for (int i = 0; i <= w; i++) {
        ans = max(ans, dp[t][i]);
    }

    cout << ans;

    return 0;
}