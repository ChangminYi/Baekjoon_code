#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> argi;
vector<int> dp, rev_dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n + 1);
    dp.resize(n + 1);
    rev_dp.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> argi[i];
    }

    /*
    * ���� �� �����ϴ� �κм���
    * �ð����⵵ O(n^2)
    */
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;

        for (int j = 1; j <= i; j++) {
            if (argi[j] < argi[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    /*
    * ���� �� �����ϴ� �κм���
    * �ð����⵵ O(n^2)
    * ��� �ڿ������� ����Ͽ� �����δ� �����ϴ� �κм���
    */
    for (int i = n; i > 0; i--) {
        rev_dp[i] = 1;

        for (int j = n; j >= i; j--) {
            if (argi[j] < argi[i] && rev_dp[i] < rev_dp[j] + 1) {
                rev_dp[i] = rev_dp[j] + 1;
            }
        }
    }

    /*
    * i��° ���ұ����� ��������+���Ҽ���
    * �ڱ� �ڽ��� ��ġ�� ������ ���̿��� 1 ����
    */
    int max_len = 0;
    for (int i = 0; i <= n; i++) {
        max_len = max(max_len, dp[i] + rev_dp[i] - 1);
    }

    cout << max_len;

    return 0;
}