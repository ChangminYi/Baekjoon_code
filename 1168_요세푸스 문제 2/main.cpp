#include <iostream>

using namespace std;

int n, k;
int seg[400'001];

int get_query(int idx, int lo, int hi, int cnt) {
    if(lo == hi)
        return lo;
    else {
        int mid = (lo + hi) / 2;
        if(seg[2 * idx] >= cnt) return get_query(2 * idx, lo, mid, cnt);
        else return get_query(2 * idx + 1, mid + 1, hi, cnt - seg[2 * idx]);
    }
}

void update_seg(int idx, int lo, int hi, int offset, int val) {
    if(lo == hi)
        seg[idx] += val;
    else {
        int mid = (lo + hi) / 2;
        if(offset <= mid) update_seg(2 * idx, lo, mid, offset, val);
        else update_seg(2 * idx + 1, mid + 1, hi, offset, val);
        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }
}

int main() {
    /**
     * 세그먼트 트리를 활용하면 특정 구간에 아직 선택되지 않은 수의
     * 수를 구할 수 있다. 따라서, 다음 숫자의 순서를 계산한 후 해당 순서와
     * 일치하는 숫자를 계속 출력하면서 세그먼트 트리를 업데이트하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;

    for(int i = 1; i <= n; i++)
        update_seg(1, 1, n, i, 1);
    
    cout << '<';
    for(int i = 0, seq = 1, res; i < n; i++) {
        seq += k - 1;
        if(seq % (n - i) == 0) seq = n - i;
        else seq %= n - i;

        res = get_query(1, 1, n, seq);
        update_seg(1, 1, n, res, -1);

        cout << res << (i == n - 1 ? ">" : ", ");
    }

    return 0;
}