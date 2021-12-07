#include <iostream>
#include <vector>
#include <map>

using namespace std;

int n, k;
vector<long long> sum;
map<long long, long long> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    sum.resize(n);

    /*
    * 미리 첫 번째 원소부터의 누적합을 구한다.
    * 그리고, 첫 번째부터의 누적합을 보면서
    * k를 만들 수 있는 조합이 있으면 그 수를 모두 더한다.
    */
    cin >> sum[0];
    for (int i = 1, tmp; i < n; i++) {
        cin >> tmp;
        sum[i] = sum[i - 1] + tmp;
    }

    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        if (sum[i] == k) {
            cnt++;
        }

        cnt += dp[sum[i] - k];
        dp[sum[i]]++;
    }

    cout << cnt;

    return 0;
}