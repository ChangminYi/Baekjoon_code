#include <iostream>

using namespace std;

int t, n;
unsigned long long sum = 0;
unsigned long long dp[65][10];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 1�� �ڸ����� ���� ����. dp[i][j]��, i�ڸ� ������ ���� ū �ڸ����� j�� ����� ��.
    * dp[i][j]�� dp[i-1][0]���� dp[i-1][j]������ ���̴�.
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