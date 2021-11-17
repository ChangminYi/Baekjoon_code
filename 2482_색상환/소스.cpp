#include <iostream>

using namespace std;

const int MAX = 1000;
const int MOD = 1000000003;

int n, k;
int dp[MAX + 1][MAX + 1] = { 0 };

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;

    // i�� �� 0���� �����ϴ� ���� 1��, i�� �� 1���� �����ϴ� ���� i��.
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
        dp[i][1] = i;
    }

    /*
    * dp[i-2][j-1]: 2��° ��, �� �������� ���� ����ȯ������ ����� ��
    * dp[i-1][j]: ������ ����ȯ������ ����� ��
    */
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            dp[i][j] = (dp[i - 2][j - 1] + dp[i - 1][j]) % MOD;
        }
    }

    /*
    * n��° ĭ�� ĥ�ϴ� ���, 1�� n - 1�� ĭ�� ĥ�ϸ� �ȵȴ�.
    * ����, n��° ĭ�� ĥ���� ������, n-1���� k���� ĥ�ϴ� ���� ����.
    */
    cout << (dp[n - 1][k] + dp[n - 3][k - 1]) % MOD;

    return 0;
}