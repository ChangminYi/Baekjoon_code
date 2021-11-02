#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

int n, m;
vector<lli> argi, segtree, lazy;

void init_segtree(int idx, int lo, int hi) {
    if (lo == hi) {
        segtree[idx] = argi[lo];
    }
    else {
        int mid = (lo + hi) / 2;

        init_segtree(2 * idx, lo, mid);
        init_segtree(2 * idx + 1, mid + 1, hi);
    }
}

void update_lazy(int idx, int lo, int hi) {
    if (lazy[idx] != 0) {
        segtree[idx] += ((lli)hi - lo + 1) * lazy[idx];

        if (lo < hi) {
            lazy[2 * idx] += lazy[idx];
            lazy[2 * idx + 1] += lazy[idx];
        }

        lazy[idx] = 0;
    }
}

void update_segtree(int idx, int lo, int hi, int left, int right, int val) {
    update_lazy(idx, lo, hi);

    if (hi < left || lo > right) {
        return;
    }
    else if (left <= lo && hi <= right) {
        segtree[idx] += ((lli)hi - lo + 1) * val;

        if (lo < hi) {
            lazy[2 * idx] += val;
            lazy[2 * idx + 1] += val;
        }
    }
    else {
        int mid = (lo + hi) / 2;
        update_segtree(2 * idx, lo, mid, left, right, val);
        update_segtree(2 * idx + 1, mid + 1, hi, left, right, val);
    }
}

lli get_query(int idx, int lo, int hi, int to_find) {
    update_lazy(idx, lo, hi);

    if (lo == hi) {
        return segtree[idx];
    }
    else {
        int mid = (lo + hi) / 2;

        if (to_find <= mid) {
            return get_query(2 * idx, lo, mid, to_find);
        }
        else {
            return get_query(2 * idx + 1, mid + 1, hi, to_find);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n + 1);
    segtree.resize(4 * (n + 1) + 1);
    lazy.resize(4 * (n + 1) + 1);

    for (int i = 1; i <= n; i++) {
        cin >> argi[i];
    }
    init_segtree(1, 1, n);

    cin >> m;
    /*
    * lazy propagation 방식을 사용한 top down 세그먼트 트리.
    * 다만, 특정 인덱스 값 하나만을 출력하므로, terminal 노드가 아닌
    * 다른 세그먼트 트리의 노드들은 업데이트하지 않음.
    */
    for (int inst; m > 0; m--) {
        cin >> inst;

        if (inst == 1) {
            int lo, hi, val;
            cin >> lo >> hi >> val;

            update_segtree(1, 1, n, lo, hi, val);
        }
        else {
            int idx;
            cin >> idx;

            cout << get_query(1, 1, n, idx) << '\n';
        }
    }

    return 0;
}