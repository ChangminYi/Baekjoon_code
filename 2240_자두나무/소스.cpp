#include <iostream>
#include <cmath>

using namespace std;

int t, w;
bool plum[1001];
int dp[1001][31];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * plum �迭�� 1�� �ڵΰ� t�ʿ� �������� �ǹ�. ���� �����̸� 2���� ��������.
    * ������ Ƚ���� Ȧ���̸� 2�� ��, ¦���̸� 1�� �ؿ� �� �ִ� ��Ȳ�̴�.
    * ����, ���� �ð��� ��ġ�� ���� ��ġ�� ���� ���� �ƴ� ���� �ִ񰪿�,
    * ���� ���� �ؿ� �ڵΰ� ������������ Ȯ���Ͽ� 1�� ���ϸ� �ȴ�.
    * ������ t���� �ð������� �ִ��� �ȴ�.
    */

    cin >> t >> w;
    for (int i = 1, num; i <= t; i++) {
        cin >> num;
        plum[i] = (num == 1);
    }
    
    plum[1] ? dp[1][0] = 1 : dp[1][1] = 1;
    for (int i = 2; i <= t; i++) {
        dp[i][0] = (plum[i] ? dp[i - 1][0] + 1 : dp[i - 1][0]);
        for (int j = 1; j <= w; j += 2) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + (plum[i] ? 0 : 1);
        }
        for (int j = 2; j <= w; j += 2) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + (plum[i] ? 1 : 0);
        }
    }

    int ans = 0;
    for (int i = 0; i <= w; i++) {
        ans = max(ans, dp[t][i]);
    }

    cout << ans;

    return 0;
}