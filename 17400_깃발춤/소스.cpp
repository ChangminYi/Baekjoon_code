#include <iostream>
#include <cmath>

using namespace std;

int n, q, inst, arg1, arg2;
long long seg[1200005];

void update_seg(int idx, int lo, int hi, int val_idx, int val) {
    if (lo == hi) {
        seg[idx] += val;
    }
    else {
        int mid = (lo + hi) / 2;
        if (val_idx <= mid) {
            update_seg(2 * idx, lo, mid, val_idx, val);
        }
        else {
            update_seg(2 * idx + 1, mid + 1, hi, val_idx, val);
        }
        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }
}

long long get_query(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return seg[idx];
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
            long long res1 = get_query(2 * idx, lo, mid, left, mid);
            long long res2 = get_query(2 * idx + 1, mid + 1, hi, mid + 1, right);
            return res1 + res2;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� ���� �հ� ���� ���� ���� ���հ��� ���ϸ� �ǹǷ�,
    * ¦�� �ε������� ���, ���� �ε������� ������ ���� �����Ͽ�
    * ���� ������ �����Ѵ�. �� �ֽ�ȭ �� ���� �ε����� �����Ͽ� ������Ʈ�Ѵ�.
    * ����� ���� ���� ������ ����ϸ� �ȴ�.
    */
    cin >> n >> q;
    for (int i = 1, val; i <= n; i++) {
        cin >> val;
        update_seg(1, 1, n, i, (i & 1 ? val : (-1) * val));
    }

    do {
        cin >> inst >> arg1 >> arg2;

        if (inst == 1) {
            cout << abs(get_query(1, 1, n, arg1, arg2)) << '\n';
        }
        else {
            update_seg(1, 1, n, arg1, (arg1 & 1 ? arg2 : (-1) * arg2));
        }
    } while (--q);

    return 0;
}