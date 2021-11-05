#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

int n, q;
vector<lli> segtree;

void update_seg(int idx, int lo, int hi, int upd_idx, int new_val) {
    if (lo == hi) {
        segtree[idx] += new_val;
    }
    else {
        int mid = (lo + hi) / 2;
        if (upd_idx <= mid) {
            update_seg(2 * idx, lo, mid, upd_idx, new_val);
        }
        else {
            update_seg(2 * idx + 1, mid + 1, hi, upd_idx, new_val);
        }

        segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];
    }
}

lli get_query(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return segtree[idx];
    }
    else {
        int mid = (lo + hi) / 2;

        if (right <= mid) {
            return get_query(2 * idx, lo, mid, left, right);
        }
        else if (mid < left) {
            return get_query(2 * idx + 1, mid + 1, hi, left, right);
        }
        else {
            lli ret = get_query(2 * idx, lo, mid, left, mid);
            ret += get_query(2 * idx + 1, mid + 1, hi, mid + 1, right);
            return ret;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> q;
    segtree.resize(((n + 1) << 2) + 1, 0);

    /*
    * 세그먼트 트리 문제.
    * 트리 업데이트에는 값을 교체하는 것이 아니라 더한다.
    * 자료형 범위가 int를 넘어갈 수 있음.
    */
    for (int i = 0, inst, arg1, arg2; i < q; i++) {
        cin >> inst >> arg1 >> arg2;

        if (inst == 1) {
            update_seg(1, 1, n, arg1, arg2);
        }
        else {
            cout << get_query(1, 1, n, arg1, arg2) << '\n';
        }
    }

    return 0;
}