#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
int dp[10'001];
pair<int, int> arg[10'001];

int main() {
    /**
     * i번째 좌표까지의 최솟값은, j ~ i번째 좌표가 포함되는 통신범위의 비용과
     * j - 1번째 좌표까지의 최솟값의 합의 최솟값이다.
     * 통신범위의 비용은 가로와 세로 길이 중 더 큰 값이 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> arg[i].first >> arg[i].second;
    }

    fill(dp + 1, dp + n + 1, INT32_MAX);
    sort(arg + 1, arg + n + 1);

    for(int i = 1, max_hgt, wdt; i <= n; i++) {
        max_hgt = 0;
        for(int j = i; j; j--) {
            max_hgt = max(max_hgt, 2 * abs(arg[j].second));
            wdt = arg[i].first - arg[j].first;
            dp[i] = min(dp[i], dp[j - 1] + max(max_hgt, wdt));
        }
    }

    cout << dp[n];

    return 0;
}