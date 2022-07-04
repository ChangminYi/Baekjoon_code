#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int t, n, k, arg[1000000];

int main() {
    /**
     * 두 정수의 쌍만 구하면 되므로, 원래 수열을 정렬해도 상관없다.
     * 가장 작은 값과 가장 큰 값부터 시작하여, 두 수를 더하고
     * 현재 가장 큰 차이보다 더 작은지 혹은 같은지를 판별한다.
     * 이를 lo가 hi보다 작을 동안 실행하고, 정답을 출력한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    while(t--) {
        cin >> n >> k;
        for(int i = 0; i < n; i++) {
            cin >> arg[i];
        }

        sort(arg, arg + n);

        int max_diff = INT32_MAX, lo = 0, hi = n - 1;
        long long ans = 0;
        while(lo < hi) {
            int sum = arg[lo] + arg[hi];
            int tmp_diff = abs(k - sum);
            if(tmp_diff == max_diff)
                ans++;
            else if(tmp_diff < max_diff)
                ans = 1, max_diff = tmp_diff;

            if(sum >= k)
                hi--;
            if(sum <= k)
                lo++;
        }
        
        cout << ans << '\n';
    }

    return 0;
}
