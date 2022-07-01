#include <iostream>
#include <cmath>

using namespace std;

void init_seg(int idx, int lo, int hi);
int get_query(int idx, int lo, int hi, int left, int right);
long long get_ans(int lo, int hi);

int n;
int arg[100'000], seg[400'005];

int main() {
    /**
     * 분할 정복과 세그먼트 트리를 사용하여 해결할 수 있다.
     * 특정 구간에서의 최솟값을 구해야 하는데, 이는 세그먼트 트리를 사용하여
     * 구간에서 최솟값의 인덱스를 저장하는 방식으로 얻을 수 있다.
     * 그리고 인덱스 좌우로 구간을 나눠 재귀적으로 넓이의 최댓값을 구하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arg[i];

    init_seg(1, 0, n - 1);

    cout << get_ans(0, n - 1);

    return 0;
}

long long get_ans(int lo, int hi) {
    if(lo == hi)
        return (long long)arg[lo];
    else {
        int min_idx = get_query(1, 0, n - 1, lo, hi);
        long long res = ((long long)hi - lo + 1) * arg[min_idx];
        long long left_res = INT64_MIN, right_res = INT64_MIN;
        if(lo < min_idx)
            left_res = get_ans(lo, min_idx - 1);
        if(min_idx < hi)
            right_res = get_ans(min_idx + 1, hi);
        return max(res, max(left_res, right_res));
    }
}

void init_seg(int idx, int lo, int hi) {
    if(lo == hi)
        seg[idx] = lo;
    else {
        int mid = (lo + hi) / 2;
        init_seg(2 * idx, lo, mid);
        init_seg(2 * idx + 1, mid + 1, hi);
        seg[idx] = (arg[seg[2 * idx]] < arg[seg[2 * idx + 1]] ? seg[2 * idx] : seg[2 * idx + 1]);
    }
}

int get_query(int idx, int lo, int hi, int left, int right) {
    if(lo == left && hi == right)
        return seg[idx];
    else {
        int mid = (lo + hi) / 2;
        if(right <= mid)
            return get_query(2 * idx, lo, mid, left, right);
        else if(mid < left)
            return get_query(2 * idx + 1, mid + 1 , hi, left, right);
        else {
            int res_1 = get_query(2 * idx, lo, mid, left, mid);
            int res_2 = get_query(2 * idx + 1, mid + 1 ,hi, mid + 1, right);
            return (arg[res_1] < arg[res_2] ? res_1 : res_2);
        }
    }
}