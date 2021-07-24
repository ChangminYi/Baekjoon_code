#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

vector<lli> argi;
vector<lli> segtree;
vector<lli> lazy;

lli init_segtree(int root, int left, int right) {
    if (left == right) {
        return segtree[root] = argi[left];
    }
    else {
        int mid = (left + right) / 2;
        return segtree[root] = init_segtree(root * 2, left, mid) + init_segtree(root * 2 + 1, mid + 1, right);
    }
}

void update_lazy(int root, int left, int right) {
    if (lazy[root] != 0) {
        segtree[root] += ((lli)right - left + 1) * lazy[root];

        if (left < right) {
            lazy[root * 2] += lazy[root];
            lazy[root * 2 + 1] += lazy[root];
        }

        lazy[root] = 0;
    }
}

void update_segtree(int root, int lo, int hi, int left, int right, lli val) {
    update_lazy(root, lo, hi);

    if (hi < left || right < lo) {
        return;
    }
    else if (left <= lo && hi <= right) {
        segtree[root] += ((lli)hi - lo + 1) * val;

        if (lo < hi) {
            lazy[root * 2] += val;
            lazy[root * 2 + 1] += val;
        }
        return;
    }
    else {
        int mid = (lo + hi) / 2;
        update_segtree(root * 2, lo, mid, left, right, val);
        update_segtree(root * 2 + 1, mid + 1, hi, left, right, val);
        segtree[root] = segtree[root * 2] + segtree[root * 2 + 1];
        return;
    }
}

lli get_sum(int root, int lo, int hi, int left, int right) {
    update_lazy(root, lo, hi);

    if (hi < left || right < lo) {
        return 0;
    }
    else if (left <= lo && hi <= right) {
        return segtree[root];
    }
    else {
        int mid = (lo + hi) / 2;
        return get_sum(root * 2, lo, mid, left, right) + get_sum(root * 2 + 1, mid + 1, hi, left, right);
    }
}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;

    argi = vector<lli>(n + 1);
    segtree = vector<lli>(4 * (n + 1));
    lazy = vector<lli>(4 * (n + 1));

    for (int i = 1; i <= n; i++) {
        cin >> argi[i];
    }
    init_segtree(1, 1, n);

    for (int i = 0, inst, arg1, arg2; i < m + k; i++) {
        cin >> inst >> arg1 >> arg2;

        if (inst == 1) {
            lli val;
            cin >> val;

            update_segtree(1, 1, n, arg1, arg2, val);
        }
        else if (inst == 2) {
            cout << get_sum(1, 1, n, arg1, arg2) << '\n';
        }
    }

    return 0;
}