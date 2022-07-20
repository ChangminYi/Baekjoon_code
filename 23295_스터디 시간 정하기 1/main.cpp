#include <iostream>
#include <cmath>

using namespace std;

int n, t, dev[100003], latest_time = -1;
long long presum[100003];

int main() {
    /**
     * 누적 합을 빠르게 구하기 위해서, 구간의 시작과 끝의 변화량을 저장한다.
     * 이 변화량을 계속 업데이트하면서 누적 합을 구하게 된다.
     * 이를 활용하여 길이가 t인 구간에서 최대의 만족도를 가지는 시작점을 구한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> t;
    for(int i = 0, k, lo, hi; i < n; i++) {
        cin >> k;
        while(k--) {
            cin >> lo >> hi;
            lo++, hi++;
            dev[lo]++, dev[hi]--;
            latest_time = max(latest_time, hi);
        }
    }

    for(int i = 1, cur_dev = 0; i <= latest_time; i++) {
        cur_dev += dev[i];
        presum[i] = presum[i - 1] + cur_dev;
    }

    int base = 0;
    long long max_val = -1, tmp_val;
    for(int i = 1; i + t - 1 <= latest_time; i++) {
        tmp_val = presum[i + t - 1] - presum[i - 1];
        if(tmp_val > max_val)
            base = i - 1, max_val = tmp_val;
    }

    cout << base << ' ' << base + t;

    return 0;
}