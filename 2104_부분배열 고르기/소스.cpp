#include <iostream>
#include <cmath>

using namespace std;

const int IDX = 0;
const int SUM = 1;

int n;
int arg[100000];
int seg_idx[400001];
long long seg_sum[400001];

void init_seg(int idx, int lo, int hi) {
    if (lo == hi) {
        seg_idx[idx] = lo;
        seg_sum[idx] = arg[lo];
    }
    else {
        int mid = (lo + hi) / 2;
        init_seg(2 * idx, lo, mid);
        init_seg(2 * idx + 1, mid + 1, hi);
        seg_idx[idx] = (arg[seg_idx[2 * idx]] < arg[seg_idx[2 * idx + 1]] ? seg_idx[2 * idx] : seg_idx[2 * idx + 1]);
        seg_sum[idx] = seg_sum[2 * idx] + seg_sum[2 * idx + 1];
    }
}

int get_idx(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return seg_idx[idx];
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
            int idx1 = get_idx(2 * idx, lo, mid, left, mid);
            int idx2 = get_idx(2 * idx + 1, mid + 1, hi, mid + 1, right);
            return (arg[idx1] < arg[idx2] ? idx1 : idx2);
        }
    }
}

long long get_sum(int idx, int lo, int hi, int left, int right) {
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
            long long sum1 = get_sum(2 * idx, lo, mid, left, mid);
            long long sum2 = get_sum(2 * idx + 1, mid + 1, hi, mid + 1, right);
            return sum1 + sum2;
        }
    }
}

long long get_max(int lo, int hi) {
    int min_idx = get_idx(1, 0, n - 1, lo, hi);
    long long res = get_sum(1, 0, n - 1, lo, hi) * arg[min_idx];
    if (lo < min_idx) {
        res = max(res, get_max(lo, min_idx - 1));
    }
    if (min_idx < hi) {
        res = max(res, get_max(min_idx + 1, hi));
    }
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 세그먼트 트리를 사용하여 부분 수열의 구간합과 구간의 최솟값 인덱스를 미리 구한다.
    * 그리고 전체 범위에서부터 분할 정복을 하여 최솟값 인덱스의 좌우측으로 나눠서 값을 구하고
    * 결과를 출력하면 된다.
    */
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }

    init_seg(1, 0, n - 1);

    cout << get_max(0, n - 1);

    return 0;
}