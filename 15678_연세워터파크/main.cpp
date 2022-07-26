#include <iostream>
#include <cmath>

using namespace std;

int n, d;
long long seg[400005], dp[100000];

long long get_query(int idx, int lo, int hi, int left, int right) {
    if(lo == left && hi == right)
        return seg[idx];
    else {
        int mid = (lo + hi) / 2;
        if(right <= mid) return get_query(2 * idx, lo, mid, left, right);
        else if(mid < left) return get_query(2 * idx + 1, mid + 1, hi, left, right);
        else return max(get_query(2 * idx, lo, mid, left, mid), get_query(2 * idx + 1, mid + 1, hi, mid + 1, right));
    }
}

void update_seg(int idx, int lo, int hi, int offset, long long val) {
    if(lo == hi)
        seg[idx] += val;
    else {
        int mid = (lo + hi) / 2;
        if(offset <= mid) update_seg(2 * idx, lo, mid, offset, val);
        else update_seg(2 * idx + 1, mid + 1, hi, offset, val);
        seg[idx] = max(seg[2 * idx], seg[2 * idx + 1]);
    }
}

int main() {
    /**
     * 특정 위치에서의 최댓값은 i - d부터 i - 1번째 최댓값에 현재 점수를 더한 값
     * 혹은 현재 위치의 점수 중 최댓값이다. 이는 dp를 사용하여 구할 수 있다.
     * 다만 d의 값이 매우 크므로, 세그먼트 트리를 사용하여 구간 최댓값을 구한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> d;
    for(int i = 0; i < n; i++) {
        cin >> dp[i];
    }

    long long max_val = dp[0];
    update_seg(1, 0, n - 1, 0, dp[0]);
    for(int i = 1; i < n; i++) {
        dp[i] = max(dp[i], dp[i] + get_query(1, 0, n - 1, max(i - d, 0), i - 1));
        max_val = max(max_val, dp[i]);
        update_seg(1, 0, n - 1, i, dp[i]);
    }

    cout << max_val;

    return 0;
}