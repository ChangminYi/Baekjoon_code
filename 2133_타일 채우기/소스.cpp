#include <iostream>

using namespace std;

int n;
int dp[31];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * n�� Ȧ���̸� �ݵ�� ä�� �� ����.
    * ¦�����, ��츦 �� �����Ͽ� ��ȭ���� ����� �ȴ�.
    */
    cin >> n;
    if (n & 1) {
        cout << 0;
    }
    else {
        dp[0] = 1, dp[1] = 0, dp[2] = 3;
        for (int i = 4; i <= n; i++) {
            dp[i] = dp[i - 2] * dp[2];
            for (int j = i - 4; j >= 0; j -= 2) {
                dp[i] += 2 * dp[j];
            }
        }

        cout << dp[n];
    }

    return 0;
}