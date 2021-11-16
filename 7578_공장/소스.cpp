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
    * ù ��° �迭������ �Էµ� ���� �� ��°������ �����Ѵ�.
    * �� ��° �迭������ ù ��° �迭���� �Էµ� ���� ��� �ִ����� ã�´�.
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
    * ù ��° �迭�� ���� �� ��° �迭���� ã��, �� �ڸ����� �ڽ��� �������� ����.
    * ������ �߿��� �̹� �湮�� ������ �ڽŰ� �������� �����̴�.
    * ����, �� ���� ������ ��, �ڽ��� ������ üũ�Ѵ�.
    * �̸� ��� ���ҿ� ���ؼ� �ݺ��ϸ� ��ġ�� ������ ���� �� �� �ִ�.
    */
    lli res = 0;
    for (int i = 0; i < n; i++) {
        res += get_sum(1, 0, n - 1, arg[i], n - 1);
        update_seg(1, 0, n - 1, arg[i], 1);
    }

    cout << res;

    return 0;
}