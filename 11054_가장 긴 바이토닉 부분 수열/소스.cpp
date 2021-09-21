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
    * 가장 긴 증가하는 부분수열
    * 시간복잡도 O(n^2)
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
    * 가장 긴 증가하는 부분수열
    * 시간복잡도 O(n^2)
    * 대신 뒤에서부터 계산하여 실제로는 감소하는 부분수열
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
    * i번째 원소까지의 증가수열+감소수열
    * 자기 자신이 겹치기 때문에 길이에서 1 빼기
    */
    int max_len = 0;
    for (int i = 0; i <= n; i++) {
        max_len = max(max_len, dp[i] + rev_dp[i] - 1);
    }

    cout << max_len;

    return 0;
}