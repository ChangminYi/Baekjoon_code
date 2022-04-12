#include <iostream>

using namespace std;

const int ARG_SIZE = 100'001;
const int SEG_SIZE = (ARG_SIZE << 2) + 1;

int testcase, n;
long long ans;
int arg[ARG_SIZE];
int segtree[SEG_SIZE];

void update_seg(int idx, int lo, int hi, int new_val, int diff) {
    if (lo == hi) {
        segtree[idx] += diff;
    }
    else {
        int mid = (lo + hi) / 2;
        if (new_val <= mid) update_seg(2 * idx, lo, mid, new_val, diff);
        else update_seg(2 * idx + 1, mid + 1, hi, new_val, diff);
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
    /*
    * �Է��� �Է� ���ڰ� ���� ���ʷ� ��ȯ�Ͽ� �����Ѵ�.
    * ���� �Է��� ������, �Է��� ���ʷ� ��ȯ�� ������ ũ�ų� ���� ����
    * ���ݱ��� �� �� ���Դ����� �� ��, �� ���� ��� ���ϸ� �ȴ�.
    * ������ ���� ���� ���ϱ� ���� ���׸�Ʈ Ʈ�� ���.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    for (; testcase; testcase--) {
        fill(arg, arg + ARG_SIZE, 0);
        fill(segtree, segtree + SEG_SIZE, 0);
        ans = 0;

        cin >> n;
        for (int i = 1, tmp; i <= n; i++) {
            cin >> tmp;
            arg[tmp] = i;
        }
        
        for (int i = 1, val; i <= n; i++) {
            cin >> val;
            val = arg[val];
            ans += get_query(1, 1, n, val, n);
            update_seg(1, 1, n, val, 1);
        }

        cout << ans << '\n';
    }

    return 0;
}