#include <iostream>

using namespace std;

int n;
long long dp[31][31];

void init_dp() {
    for (int i = 0; i <= 30; i++) {
        for (int j = i; j <= 30; j++) {
            if (i == 0) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * w�� h�� ǥ���� �� �ִ� ������ ���� ã���� �ȴ�.
    * 2���� �迭�� ���� w�� ��, ���� h�� ���� �Ͽ�,
    * dp[i][j] = dp[i-1][j] + dp[i][j-1], ��,
    * h�� �ϳ� ������ ���ڿ��� w�� �ϳ� ������ ���ڿ��� ���� ���Ѵ�.
    */
    init_dp();

    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        else {
            cout << dp[n][n] << '\n';
        }
    }

    return 0;
}