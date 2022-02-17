#include <iostream>
#include <cmath>

using namespace std;

int n;
long long dp[101];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 키보드를 눌러서 한 글자를 추가하는 경우와, 선택-복사-붙여넣기를 하는 경우가 있다.
    * 따라서, 두 가지 경우 중 가장 큰 값을 갖는 경우를 사용하면 된다.
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