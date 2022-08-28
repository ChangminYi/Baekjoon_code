#include <iostream>

using namespace std;

int n, ans, dp[1000001];

int main() {
    /**
     * 연속된 부분 수열이 아닌 수들을 앞이나 뒤로 옮기면
     * 수열을 정렬할 수 있다. 부분 수열 중 가장 긴 수열을 찾으면 된다.
     * 따라서 연속된 수로 이뤄진 LIS의 길이를 구하고,
     * 수열의 길이에서 LIS의 길이를 뺀 값이 답이다. 
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 1, val; i <= n; i++) {
        cin >> val;
        dp[val] = dp[val - 1] + 1;
        ans = max(ans, dp[val]);
    }

    cout << n - ans;
    
    return 0;
}