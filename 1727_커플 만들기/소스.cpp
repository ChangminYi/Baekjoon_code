#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, m;
int argi[2][1000];
int dp[1001][1001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> argi[0][i];
    }
    for (int i = 0; i < m; i++) {
        cin >> argi[1][i];
    }

    /*
    * 일단 남자, 여자의 수치를 모두 정렬한다.
    * 만약 i == j라면, 커플이 만들어진 경우이므로 수치의 차를 저장.
    * 만약 i > j라면, 남자가 더 많은 경우이므로, i번째 남자가 솔로이던가 커플의 수치차를 저장.
    * 만약 i < j라면, 여자가 더 많은 경우이므로, j번째 여자가 솔로이던가 커플의 수치차를 저장.
    */
    sort(argi[0], argi[0] + n);
    sort(argi[1], argi[1] + m);

    for (int i = 1, tmp; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            tmp = dp[i - 1][j - 1] + abs(argi[0][i - 1] - argi[1][j - 1]);

            if (i > j) {
                dp[i][j] = min(tmp, dp[i - 1][j]);
            }
            else if (i < j) {
                dp[i][j] = min(tmp, dp[i][j - 1]);
            }
            else {
                dp[i][j] = tmp;
            }
        }
    }

    cout << dp[n][m];

    return 0;
}