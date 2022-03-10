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
    * 중간에 잘못된 코드가 섞여 있더라도, 계산 중에 자동으로 0이 계산된다.
    * 한 자리인 경우와 두 자리인 경우로 나누어 현재의 값을 구하면 된다.
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