#include <iostream>
#include <cmath>

using namespace std;

int n;
long long dp[101];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * Ű���带 ������ �� ���ڸ� �߰��ϴ� ����, ����-����-�ٿ��ֱ⸦ �ϴ� ��찡 �ִ�.
    * ����, �� ���� ��� �� ���� ū ���� ���� ��츦 ����ϸ� �ȴ�.
    */

    cin >> n;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + 1;
        for (int j = 3; j <= i; j++) {
            dp[i] = max(dp[i], dp[i - j] * (j - 1));
        }
    }

    cout << dp[n];

    return 0;
}