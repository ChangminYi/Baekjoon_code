#include <iostream>

using namespace std;

const int MAX = 100001;

int n, ans = -1;
int argi[MAX], seg[4 * MAX + 1];

void init_seg(int idx, int lo, int hi) {
    if (lo == hi) {
        seg[idx] = lo;
    }
    else {
        int mid = (lo + hi) / 2;
        init_seg(2 * idx, lo, mid);
        init_seg(2 * idx + 1, mid + 1, hi);

        seg[idx] = (argi[seg[2 * idx]] < argi[seg[2 * idx + 1]] ? seg[2 * idx] : seg[2 * idx + 1]);
    }
}

int get_idx(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return seg[idx];
    }
    else {
        int mid = (lo + hi) / 2;

        if (right <= mid) {
            return get_idx(2 * idx, lo, mid, left, right);
        }
        else if (mid < left) {
            return get_idx(2 * idx + 1, mid + 1, hi, left, right);
        }
        else {
            int res_l = get_idx(2 * idx, lo, mid, left, mid);
            int res_r = get_idx(2 * idx + 1, mid + 1, hi, mid + 1, right);

            return (argi[res_l] < argi[res_r] ? res_l : res_r);
        }
    }
}

void get_ans(int lo, int hi) {
    int wid = hi - lo + 1;
    int h_idx = get_idx(1, 1, n, lo, hi);

    ans = max(ans, wid * argi[h_idx]);
    if (lo < h_idx) {
        get_ans(lo, h_idx - 1);
    }
    if (h_idx < hi) {
        get_ans(h_idx + 1, hi);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> argi[i];
    }
    init_seg(1, 1, n);

    /*
    * 세그먼트 트리 + 분할정복
    * 구간에서의 최소 높이의 인덱스만 저장하고,
    * 이를 기준으로 넓이 계산하여 최댓값 계산.
    */
    get_ans(1, n);
    cout << ans;

    return 0;
}