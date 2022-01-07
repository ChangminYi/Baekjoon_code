#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, m;
int argi[2][1000];
int dp[1001][1001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> argi[0][i];
    }
    for (int i = 0; i < m; i++) {
        cin >> argi[1][i];
    }

    /*
    * �ϴ� ����, ������ ��ġ�� ��� �����Ѵ�.
    * ���� i == j���, Ŀ���� ������� ����̹Ƿ� ��ġ�� ���� ����.
    * ���� i > j���, ���ڰ� �� ���� ����̹Ƿ�, i��° ���ڰ� �ַ��̴��� Ŀ���� ��ġ���� ����.
    * ���� i < j���, ���ڰ� �� ���� ����̹Ƿ�, j��° ���ڰ� �ַ��̴��� Ŀ���� ��ġ���� ����.
    */
    sort(argi[0], argi[0] + n);
    sort(argi[1], argi[1] + m);

    for (int i = 1, tmp; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            tmp = dp[i - 1][j - 1] + abs(argi[0][i - 1] - argi[1][j - 1]);

            if (i > j) {
                dp[i][j] = min(tmp, dp[i - 1][j]);
            }
            else if (i < j) {
                dp[i][j] = min(tmp, dp[i][j - 1]);
            }
            else {
                dp[i][j] = tmp;
            }
        }
    }

    cout << dp[n][m];

    return 0;
}