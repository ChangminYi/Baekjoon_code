#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long lli;

int n, res_lo, res_hi;
lli res = -1;
vector<int> argi, seg_min;
vector<lli> seg_sum;

void init_sum(int idx, int lo, int hi) {
    if (lo == hi) {
        seg_sum[idx] = argi[lo];
    }
    else {
        int mid = (lo + hi) / 2;
        init_sum(2 * idx, lo, mid);
        init_sum(2 * idx + 1, mid + 1, hi);
        seg_sum[idx] = seg_sum[2 * idx] + seg_sum[2 * idx + 1];
    }
}

void init_min(int idx, int lo, int hi) {
    if (lo == hi) {
        seg_min[idx] = lo;
    }
    else {
        int mid = (lo + hi) / 2;
        init_min(2 * idx, lo, mid);
        init_min(2 * idx + 1, mid + 1, hi);

        if (argi[seg_min[2 * idx]] < argi[seg_min[2 * idx + 1]]) {
            seg_min[idx] = seg_min[2 * idx];
        }
        else {
            seg_min[idx] = seg_min[2 * idx + 1];
        }
    }
}

int get_min(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return seg_min[idx];
    }
    else {
        int mid = (lo + hi) / 2;

        if (right <= mid) {
            return get_min(2 * idx, lo, mid, left, right);
        }
        else if (mid < left) {
            return get_min(2 * idx + 1, mid + 1, hi, left, right);
        }
        else {
            int res_left = get_min(2 * idx, lo, mid, left, mid);
            int res_right = get_min(2 * idx + 1, mid + 1, hi, mid + 1, right);

            return (argi[res_left] < argi[res_right] ? res_left : res_right);
        }
    }
}

lli get_sum(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return seg_sum[idx];
    }
    else {
        int mid = (lo + hi) / 2;

        if (right <= mid) {
            return get_sum(2 * idx, lo, mid, left, right);
        }
        else if (mid < left) {
            return get_sum(2 * idx + 1, mid + 1, hi, left, right);
        }
        else {
            lli sum_left = get_sum(2 * idx, lo, mid, left, mid);
            lli sum_right = get_sum(2 * idx + 1, mid + 1, hi, mid + 1, right);

            return sum_left + sum_right;
        }
    }
}

void get_max(int lo, int hi) {
    int min_idx = get_min(1, 1, n, lo, hi);
    lli sum_val = get_sum(1, 1, n, lo, hi);

    if (res < argi[min_idx] * sum_val) {
        res = argi[min_idx] * sum_val;
        res_lo = lo, res_hi = hi;
    }

    if (lo < min_idx) {
        get_max(lo, min_idx - 1);
    }
    if (min_idx < hi) {
        get_max(min_idx + 1, hi);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n + 1);
    seg_sum.resize(4 * n + 1);
    seg_min.resize(4 * n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> argi[i];
    }
    init_sum(1, 1, n);
    init_min(1, 1, n);

    /*
    * 세그먼트 트리 + 분할정복
    * 최솟값의 인덱스를 저장하는 세그트리와 합을 저장하는 세그트리 필요
    * 초기화 한 후, 현재 범위에서 최솟값의 인덱스를 찾음.
    * 값을 계산한 후, 최솟값 인덱스 좌우로 분할하여 재귀적으로 값 갱신.
    */
    get_max(1, n);
    cout << res << '\n' << res_lo << ' ' << res_hi;

    return 0;
}