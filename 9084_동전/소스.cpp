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
        * 배낭 문제. 0원은 1개의 만드는 방법 존재.
        * 그리고 각 숫자를 만드는 방법을 모두 더하면 된다.
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