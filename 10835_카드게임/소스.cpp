#include <iostream>
#include <cmath>

using namespace std;

const int NOT_VISIT = -1;

int n;
int left_arg[2'000], right_arg[2'000];
int dp[2'000][2'000];

int get_dp(int i, int j) {
    if (i == n || j == n) {
        return 0;
    }
    else {
        if (dp[i][j] == NOT_VISIT) {
            dp[i][j] = max(get_dp(i + 1, j), get_dp(i + 1, j + 1));
            if (left_arg[i] > right_arg[j]) {
                dp[i][j] = max(dp[i][j], get_dp(i, j + 1) + right_arg[j]);
            }
        }

        return dp[i][j];
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 카드게임의 룰을 그대로 점화식으로 옮기면 된다.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> left_arg[i];
        fill(dp[i], dp[i] + n, NOT_VISIT);
    }
    for (int i = 0; i < n; i++) {
        cin >> right_arg[i];
    }

    cout << get_dp(0, 0);

    return 0;
}