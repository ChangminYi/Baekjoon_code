#include <iostream>
#include <numeric>

using namespace std;

const int ARG_SIZE = 200'001;
const int SEGTREE_SIZE = 800'005;

int n, m, testcase;
int location[ARG_SIZE], segtree[SEGTREE_SIZE];

void update_segtree(int idx, int lo, int hi, int new_val, int variation) {
    if (lo == hi) {
        segtree[idx] += variation;
    }
    else {
        int mid = (lo + hi) / 2;
        if (new_val <= mid) update_segtree(2 * idx, lo, mid, new_val, variation);
        else update_segtree(2 * idx + 1, mid + 1, hi, new_val, variation);
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
    * 최초 n개의 영화가 있고, m번 움직이므로 전체 공간을 n + m개의 배열로 생각해도 된다.
    * 이를 기준으로 세그먼트 트리를 만들어 현재 고른 영화의 번호보다
    * 위에 있는 모든 영화의 수를 출력하고, 가장 위에 영화를 추가하면 된다.
    * 이를 위해서는 현재 영화의 위치와 가장 위의 인덱스를 기억해야 한다.
    */

    cin >> testcase;
    for (; testcase; testcase--) {
        fill(segtree, segtree + SEGTREE_SIZE, 0);

        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            update_segtree(1, 1, n + m, i, 1);
            location[i] = n - i + 1;
        }

        for (int i = 0, cur, top = n; i < m; i++) {
            cin >> cur;
            update_segtree(1, 1, n + m, location[cur], -1);
            cout << get_query(1, 1, n + m, location[cur], top) << ' ';
            update_segtree(1, 1, n + m, ++top, 1);
            location[cur] = top;
        }
        cout << '\n';
    }

    return 0;
}