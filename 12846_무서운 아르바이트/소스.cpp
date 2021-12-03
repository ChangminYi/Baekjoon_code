#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long lli;
struct node {
    int value = 0, index = 0;
    node() {}
    node(int _v, int _i) : value(_v), index(_i) {}
};
const int MAX = 100001;

int n;
int argi[MAX];
node seg[4 * MAX];

void init_seg(int idx, int lo, int hi) {
    if (lo == hi) {
        seg[idx].value = argi[lo];
        seg[idx].index = lo;
    }
    else {
        int mid = (lo + hi) / 2;

        init_seg(2 * idx, lo, mid);
        init_seg(2 * idx + 1, mid + 1, hi);
        if (seg[2 * idx].value < seg[2 * idx + 1].value) {
            seg[idx] = seg[2 * idx];
        }
        else {
            seg[idx] = seg[2 * idx + 1];
        }
    }
}

node search_seg(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return seg[idx];
    }
    else {
        int mid = (lo + hi) / 2;

        if (right <= mid) {
            return search_seg(2 * idx, lo, mid, left, right);
        }
        else if (mid < left) {
            return search_seg(2 * idx + 1, mid + 1, hi, left, right);
        }
        else {
            node c_left = search_seg(2 * idx, lo, mid, left, mid);
            node c_right = search_seg(2 * idx + 1, mid + 1, hi, mid + 1, right);

            return (c_left.value < c_right.value ? c_left : c_right);
        }
    }
}

lli find_max(const int left, const int right) {
    node range_min = search_seg(1, 0, n - 1, left, right);
    lli res_left = 0, res_right = 0;
    if (left < range_min.index) {
        res_left = find_max(left, range_min.index - 1);
    }
    if (range_min.index < right) {
        res_right = find_max(range_min.index + 1, right);
    }
    lli res = range_min.value * ((lli)right - left + 1);

    return max(res, max(res_left, res_right));
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> argi[i];
    }

    init_seg(1, 0, n - 1);

    /*
    * ���׸�Ʈ Ʈ�� + ���� ����.
    * Ư�� ���������� �ּڰ��� �� ���� �ε����� ���׸�Ʈ Ʈ���� ����.
    * ��ü ������������ �ּڰ��� �ε����� �������� �����Ͽ� �� ���.
    * ���� ������ ��, ���� ������ ��, ���� ������ �� �� �ִ��� ���ϸ� �ȴ�.
    * ����� int ������ �Ѿ �� ����.
    */
    cout << find_max(0, n - 1);

    return 0;
}