#include <iostream>
#include <algorithm>

using namespace std;

struct dat {
    int val, origin_order;
};

int n;
dat arg[500'000];
int segtree[2'000'001];

void update_segtree(int idx, int lo, int hi, int new_val) {
    if (lo == hi) {
        segtree[idx]++;
    }
    else {
        int mid = (lo + hi) / 2;
        if (new_val <= mid) update_segtree(2 * idx, lo, mid, new_val);
        else update_segtree(2 * idx + 1, mid + 1, hi, new_val);
        segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];
    }
}

int get_query(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return segtree[idx];
    }
    else {
        int mid = (lo + hi) / 2;
        if (right <= mid) return get_query(2 * idx, lo, mid, left, right);
        else if (mid < left) return get_query(2 * idx + 1, mid + 1, hi, left, right);
        else return get_query(2 * idx, lo, mid, left, mid) + get_query(2 * idx + 1, mid + 1, hi, mid + 1, right);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 세그먼트 트리를 활용하여 지금까지 나온 실력의 값을 저장한다.
    * 다만, 입력되는 실력 값의 범위가 1 ~ 10^9이다. 따라서 좌표를 압축한다.
    * 실력 기준으로 정렬한 후, n의 범위와 같게 조정하고, 다시 원래 순서대로 정렬한다.
    * 그 후, 세그먼트 트리에 실력 값을 업데이트하고, 자신보다 크거나 같은
    * 등수의 수를 세어 출력하면 된다.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].val;
        arg[i].origin_order = i;
    }

    sort(arg, arg + n, [](const dat& lhs, const dat& rhs) {
        return lhs.val < rhs.val;
    });
    for (int i = 0; i < n; i++) {
        arg[i].val = i;
    }
    sort(arg, arg + n, [](const dat& lhs, const dat& rhs) {
        return lhs.origin_order < rhs.origin_order;
    });

    for (int i = 0; i < n; i++) {
        update_segtree(1, 0, n - 1, arg[i].val);
        cout << get_query(1, 0, n - 1, arg[i].val, n - 1) << '\n';
    }

    return 0;
}