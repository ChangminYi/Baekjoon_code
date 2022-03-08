#include <iostream>
#include <cmath>

using namespace std;

int n, m;
int arg[1'000'001];
int segtree[4'000'005];

void init_segtree(int idx, int lo, int hi) {
    if (lo == hi) segtree[idx] = arg[lo];
    else {
        int mid = (lo + hi) / 2;
        if (lo <= mid) init_segtree(2 * idx, lo, mid);
        if (mid < hi) init_segtree(2 * idx + 1, mid + 1, hi);
        segtree[idx] = max(segtree[2 * idx], segtree[2 * idx + 1]);
    }
}

int get_query(int idx, int lo, int hi, int s_lo, int s_hi) {
    if (lo == s_lo && hi == s_hi) return segtree[idx];
    else {
        int mid = (lo + hi) / 2;
        if (s_hi <= mid) return get_query(2 * idx, lo, mid, s_lo, s_hi);
        else if (mid < s_lo) return get_query(2 * idx + 1, mid + 1, hi, s_lo, s_hi);
        else {
            int ret1 = get_query(2 * idx, lo, mid, s_lo, mid);
            int ret2 = get_query(2 * idx + 1, mid + 1, hi, mid + 1, s_hi);
            return max(ret1, ret2);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���׸�Ʈ Ʈ���� �̿��Ͽ� ������ �ִ��� ���ϸ� �ȴ�.
    * �� ��, m���� n-m+1���� ������ �ִ��� ����ϸ� �ȴ�.
    */

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arg[i];
    }

    init_segtree(1, 1, n);

    for (int i = m; i <= n - m + 1; i++) {
        cout << get_query(1, 1, n, i - m + 1, i + m - 1) << ' ';
    }

    return 0;
}