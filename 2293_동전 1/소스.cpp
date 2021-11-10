#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, k;
vector<int> arg, dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> k;
    arg.resize(n);
    dp.resize(k + 1);
    for (int& i : arg) {
        cin >> i;
    }

    /*
    * 0을 만들 수 있는 경우는, 모든 수를 고르지 않는 1가지의 경우.
    * 나머지는 자신 이하의 수의 경우끼리 더하면 구해진다.
    */
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = arg[i]; j <= k; j++) {
            dp[j] += dp[j - arg[i]];
        }
    }

    cout << dp[k];

    return 0;
}