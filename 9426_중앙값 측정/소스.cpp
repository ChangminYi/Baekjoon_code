#include <iostream>
#include <deque>

using namespace std;

const int MAX_RANGE = UINT16_MAX + 1;
const int MAX_SEG = (4 * MAX_RANGE) + 1;

int n, k;
long long sum = 0;
deque<int> arg;
int segtree[MAX_SEG];

void update_seg(int idx, int lo, int hi, int new_val, bool is_plus) {
    if (lo == hi) {
        segtree[idx] += (is_plus ? 1 : -1);
    }
    else {
        int mid = (lo + hi) / 2;
        if (new_val <= mid) update_seg(2 * idx, lo, mid, new_val, is_plus);
        else update_seg(2 * idx + 1, mid + 1, hi, new_val, is_plus);
        segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];
    }
}

int get_query(int idx, int lo, int hi, int val) {
    if (lo == hi) {
        return lo;
    }
    else {
        int mid = (lo + hi) / 2;
        if (val <= segtree[2 * idx]) return get_query(2 * idx, lo, mid, val);
        else return get_query(2 * idx + 1, mid + 1, hi, val - segtree[2 * idx]);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���׸�Ʈ Ʈ�� ����. 1572�� ������ ���� ��� ���ѻ����� �Ȱ���.
    * �ٸ�, �� ������ Ǯ ���� �Է°��� ���� �������� �ʰ�, ���� ����Ͽ�
    * k���� �������� �޸𸮸� �����ϴ� �������� ������ Ǯ����.
    */

    cin >> n >> k;
    for (int i = 0, tmp; i < k - 1; i++) {
        cin >> tmp;
        arg.push_front(tmp);
        update_seg(1, 0, MAX_RANGE - 1, tmp, true);
    }
    for (int i = k - 1, tmp; i < n; i++) {
        cin >> tmp;
        arg.push_front(tmp);
        update_seg(1, 0, MAX_RANGE - 1, tmp, true);
        sum += get_query(1, 0, MAX_RANGE - 1, (k + 1) / 2);
        update_seg(1, 0, MAX_RANGE - 1, arg.back(), false);
        arg.pop_back();
    }

    cout << sum;

    return 0;
}