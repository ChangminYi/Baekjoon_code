#include <iostream>
#include <cmath>

using namespace std;

const int EVEN = 0;
const int ODD = 1;

int n, q, inst, arg_1, arg_2;
long long segtree[2][1200005];

void update_seg(int offset, int idx, int lo, int hi, int val_idx, int new_val) {
    if (lo == hi) {
        segtree[offset][idx] += new_val;
    }
    else {
        int mid = (lo + hi) / 2;
        if (val_idx <= mid) {
            update_seg(offset, 2 * idx, lo, mid, val_idx, new_val);
        }
        else {
            update_seg(offset, 2 * idx + 1, mid + 1, hi, val_idx, new_val);
        }
        segtree[offset][idx] = segtree[offset][2 * idx] + segtree[offset][2 * idx + 1];
    }
}

long long get_query(int offset, int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return segtree[offset][idx];
    }
    else {
        int mid = (lo + hi) / 2;
        if (right <= mid) {
            return get_query(offset, 2 * idx, lo, mid, left, right);
        }
        else if (mid < left) {
            return get_query(offset, 2 * idx + 1, mid + 1, hi, left, right);
        }
        else {
            long long res1 = get_query(offset, 2 * idx, lo, mid, left, mid);
            long long res2 = get_query(offset, 2 * idx + 1, mid + 1, hi, mid + 1, right);
            return res1 + res2;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���׸�Ʈ Ʈ���� �� �� ����. �ϳ��� ¦�� ������ ����, �ٸ� �ϳ��� Ȧ�� ������ ����.
    * �������� ����� ���� �� ���� ī������ �� �����̹Ƿ�, �¿�� �������� �ʾƵ� �ȴ�.
    * �־��� ���������� ���� �հ� ���� ���� ���� ���Ͽ�, �� ���̸� ����ϸ� �ȴ�.
    */
    cin >> n >> q;
    for (int i = 1, val; i <= n; i++) {
        cin >> val;
        update_seg((i & 1 ? ODD : EVEN), 1, 1, n, i, val);
    }

    do {
        cin >> inst >> arg_1 >> arg_2;

        if (inst == 1) {
            long long res_1 = get_query((arg_1 & 1 ? ODD : EVEN), 1, 1, n, arg_1, arg_2);
            long long res_2 = get_query((arg_1 & 1 ? EVEN : ODD), 1, 1, n, arg_1, arg_2);
            cout << abs(res_1 - res_2) << '\n';
        }
        else {
            update_seg((arg_1 & 1 ? ODD : EVEN), 1, 1, n, arg_1, arg_2);
        }
    } while (--q);

    return 0;
}