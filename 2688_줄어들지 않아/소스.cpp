#include <iostream>

using namespace std;

int t, n;
unsigned long long sum = 0;
unsigned long long dp[65][10];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 1의 자리부터 수를 센다. dp[i][j]는, i자리 수에서 가장 큰 자릿수가 j인 경우의 수.
    * dp[i][j]는 dp[i-1][0]에서 dp[i-1][j]까지의 합이다.
    */
    for (int i = 0; i < 10; i++) {
        dp[1][i] = 1;
    }
    for (int i = 2; i <= 64; i++) {
        for (int j = 0; j < 10; j++) {
            dp[i][j] = 0;
            for (int k = 0; k <= j; k++) {
                dp[i][j] += dp[i - 1][k];
            }
        }
    }

    cin >> t;
    do {
        cin >> n;
        
        sum = 0;
        for (int i = 0; i < 10; i++) {
            sum += dp[n][i];
        }
        cout << sum << '\n';
    } while (--t);

    return 0;
}