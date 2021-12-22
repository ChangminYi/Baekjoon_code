#include <iostream>
#include <vector>

using namespace std;

int testcase, n, m;
vector<int> coin;
int dp[10001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    do {
        cin >> n;
        coin = vector<int>(n);
        for (int& c : coin) {
            cin >> c;
        }
        cin >> m;

        /*
        * �賶 ����. 0���� 1���� ����� ��� ����.
        * �׸��� �� ���ڸ� ����� ����� ��� ���ϸ� �ȴ�.
        */
        fill(dp + 1, dp + m + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = coin[i]; j <= m; j++) {
                dp[j] += dp[j - coin[i]];
            }
        }

        cout << dp[m] << '\n';
    } while (--testcase);

    return 0;
}