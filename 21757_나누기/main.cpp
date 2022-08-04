#include <iostream>

using namespace std;

int n, arg[100001], presum[100001];
long long dp[4][100001];

int main() {
    /**
     * 만약 모든 원소의 합이 4의 배수가 아니라면, 나눌 수 있는 방법은 없다.
     * 원소 총합을 4로 나눈 값을 기준점으로 사용할 수 있다.
     * 부분합이 기준점의 배수인 경우, 그 점을 구간을 나누는 선으로 사용할 수 있다.
     * 따라서, 3개의 기준선과 n - 1개의 원소까지 설치하였을 때의 경우의 수를 구하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> arg[i];
        presum[i] = presum[i - 1] + arg[i];
    }

    if(presum[n] % 4 != 0)
        cout << 0;
    else {
        int div_val = presum[n] / 4;
        
        fill(dp[0], dp[0] + n + 1, 1);
        for(int i = 1; i < 4; i++) {
            for(int j = 1; j <= n; j++) {
                dp[i][j] = dp[i][j - 1] + (div_val * i == presum[j] ? dp[i - 1][j - 1] : 0);
            }
        }

        cout << dp[3][n - 1];
    }

    return 0;
}
