#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const int MAX = 1000000;

int n;
vector<lli> segtree;
vector<int> arg;
int idx[MAX + 1];

void update_seg(int cur, int lo, int hi, int new_idx, int new_val) {
    if (lo == hi) {
        segtree[cur] += new_val;
    }
    else {
        int mid = (lo + hi) / 2;

        if (new_idx <= mid) {
            update_seg(2 * cur, lo, mid, new_idx, new_val);
        }
        else {
            update_seg(2 * cur + 1, mid + 1, hi, new_idx, new_val);
        }

        segtree[cur] = segtree[2 * cur] + segtree[2 * cur + 1];
    }
}

lli get_sum(int cur, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return segtree[cur];
    }
    else {
        int mid = (lo + hi) / 2;

        if (right <= mid) {
            return get_sum(2 * cur, lo, mid, left, right);
        }
        else if (mid < left) {
            return get_sum(2 * cur + 1, mid + 1, hi, left, right);
        }
        else {
            lli res_l = get_sum(2 * cur, lo, mid, left, mid);
            lli res_r = get_sum(2 * cur + 1, mid + 1, hi, mid + 1, right);
            return res_l + res_r;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n, 0);
    segtree.resize((n << 2) + 1, 0);

    /*
    * 첫 번째 배열에서는 입력된 값이 몇 번째인지를 저장한다.
    * 두 번째 배열에서는 첫 번째 배열에서 입력된 값이 어디 있는지를 찾는다.
    */
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        idx[tmp] = i;
    }
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        arg[i] = idx[tmp];
    }

    /*
    * 첫 번째 배열의 값을 두 번째 배열에서 찾고, 그 자리부터 자신의 오른쪽을 본다.
    * 오른쪽 중에서 이미 방문한 값들은 자신과 엇갈리는 값들이다.
    * 따라서, 그 수를 더해준 후, 자신이 왔음을 체크한다.
    * 이를 모든 원소에 대해서 반복하면 겹치는 선분의 수를 알 수 있다.
    */
    lli res = 0;
    for (int i = 0; i < n; i++) {
        res += get_sum(1, 0, n - 1, arg[i], n - 1);
        update_seg(1, 0, n - 1, arg[i], 1);
    }

    cout << res;

    return 0;
}