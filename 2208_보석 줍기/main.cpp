#include <iostream>
#include <cmath>

using namespace std;

int n, m;
int arg[100001], presum[100001], dp[100001];

int main() {
    /**
     * m개로 이뤄진 새로운 구간, 혹은 직전 구간에서 보석 하나를 더 줍기
     * 두 개로 나눠 생각할 수 있다. 중간에 보석 줍기를 그만하고 나가는 경우에서
     * 최댓값이 발생할 수 있다. 0 미만으로 떨어지면 아예 줍지 않는 경우도 있다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> arg[i];
    }
    for(int i = 1; i <= n; i++) {
        presum[i] = presum[i - 1] + arg[i];
    }

    int max_val = 0;
    dp[m] = presum[m];
    max_val = dp[m];
    for(int i = m + 1; i <= n; i++) {
        dp[i] = max(dp[i - 1] + arg[i], presum[i] - presum[i - m]);
        max_val = max(max_val, dp[i]);
    }

    cout << max(max_val, 0);

    return 0;
}