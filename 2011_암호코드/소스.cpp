#include <iostream>
#include <string>

using namespace std;

const int MOD = 1000000;

string tmp;
int str[5'001];
int dp[5'001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �߰��� �߸��� �ڵ尡 ���� �ִ���, ��� �߿� �ڵ����� 0�� ���ȴ�.
    * �� �ڸ��� ���� �� �ڸ��� ���� ������ ������ ���� ���ϸ� �ȴ�.
    */

    cin >> tmp;
    for (int i = 0; i < (int)tmp.length(); i++) {
        str[i + 1] = tmp[i] - '0';
    }

    dp[0] = 1;
    for (int i = 1, val; i <= (int)tmp.length(); i++) {
        if (1 <= str[i] && str[i] <= 9) {
            dp[i] += dp[i - 1];
            dp[i] %= MOD;
        }
        val = str[i - 1] * 10 + str[i];
        if (10 <= val && val <= 26) {
            dp[i] += dp[i - 2];
            dp[i] %= MOD;
        }
    }

    cout << dp[tmp.length()];

    return 0;
}