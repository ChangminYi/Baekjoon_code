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
    * ���׸�Ʈ Ʈ���� Ȱ���Ͽ� ���ݱ��� ���� �Ƿ��� ���� �����Ѵ�.
    * �ٸ�, �ԷµǴ� �Ƿ� ���� ������ 1 ~ 10^9�̴�. ���� ��ǥ�� �����Ѵ�.
    * �Ƿ� �������� ������ ��, n�� ������ ���� �����ϰ�, �ٽ� ���� ������� �����Ѵ�.
    * �� ��, ���׸�Ʈ Ʈ���� �Ƿ� ���� ������Ʈ�ϰ�, �ڽź��� ũ�ų� ����
    * ����� ���� ���� ����ϸ� �ȴ�.
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