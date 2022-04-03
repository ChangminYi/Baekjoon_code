#include <iostream>

using namespace std;

int n;
int segtree[8'000'001];

void update_seg(int idx, int lo, int hi, int val, int diff) {
    if (lo == hi) {
        segtree[idx] += diff;
    }
    else {
        int mid = (lo + hi) / 2;
        if (val <= mid) update_seg(2 * idx, lo, mid, val, diff);
        else update_seg(2 * idx + 1, mid + 1, hi, val, diff);
        segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];
    }
}

int get_query(int idx, int lo, int hi, int val) {
    if (lo == hi) {
        return lo;
    }
    else {
        int mid = (lo + hi) / 2;
        if (segtree[2 * idx] >= val) return get_query(2 * idx, lo, mid, val);
        else return get_query(2 * idx + 1, mid + 1, hi, val - segtree[2 * idx]);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���׸�Ʈ Ʈ���� ���� ������ x�� ������ 1 ~ 2'000'000�̴�.
    * ���׸�Ʈ Ʈ���� Ž���� ��, ���� ���� �������� ���� �ڽ� ��尡
    * �� ��°�� ���� ���� ���ϴ� val���� ũ�ٸ�, �� ������ ����.
    * �ƴ϶��, ������ �ڽ� ���� ���µ�, ���� �ڽ��� ����ŭ val���� ����
    * ��Ȯ�� Ž���� �� �� �ִ�.
    */

    cin >> n;
    for (int inst, x, val; n; n--) {
        cin >> inst >> x;
        if (inst == 1) {
            update_seg(1, 1, 2'000'000, x, 1);
        }
        else {
            val = get_query(1, 1, 2'000'000, x);
            cout << val << '\n';
            update_seg(1, 1, 2'000'000, val, -1);
        }
    }

    return 0;
}