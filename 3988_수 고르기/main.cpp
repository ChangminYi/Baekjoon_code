#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, k;
int arg[1000000], seg[4000005];

void update_seg(int idx, int lo, int hi, int offset, int val) {
    if(lo == hi)
        seg[idx] = val;
    else {
        int mid = (lo + hi) / 2;
        if(offset <= mid) update_seg(2 * idx, lo, mid, offset, val);
        else update_seg(2 * idx + 1, mid + 1, hi, offset, val);
        seg[idx] = min(seg[2 * idx], seg[2 * idx + 1]);
    }
}

int get_query(int idx, int lo, int hi, int left, int right) {
    if(lo == left && hi == right)
        return seg[idx];
    else {
        int mid = (lo + hi) / 2;
        if(right <= mid) return get_query(2 * idx, lo, mid, left, right);
        else if(mid < left) return get_query(2 * idx + 1, mid + 1, hi, left, right);
        else return min(get_query(2 * idx, lo, mid, left, mid), get_query(2 * idx + 1, mid + 1, hi, mid + 1, right));
    }
}

int main() {
    /**
     * 수열을 정렬하면, 구간 내에서의 원소의 차의 최댓값을 구할 수 있다.
     * 구간 내에서의 원소의 차의 최솟값은 세그먼트 트리를 사용하여 관리한다.
     * 그 후, 가능한 모든 구간에서 차의 최댓값과 차의 최솟값의 합의 최솟값을 구한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> arg[i];
    }

    sort(arg, arg + n);
    for(int i = 0; i < n - 1; i++) {
        update_seg(1, 0, n - 2, i, arg[i + 1] - arg[i]);
    }

    int ans = get_query(1, 0, n - 2, 0, n - k - 2) + (arg[n - k - 1] - arg[0]);
    for(int i = 1; i <= k; i++) {
        ans = min(ans, get_query(1, 0, n - 2, i, i + n - k - 2) + (arg[i + n - k - 1] - arg[i]));
    }
    
    cout << ans;

    return 0;
}
