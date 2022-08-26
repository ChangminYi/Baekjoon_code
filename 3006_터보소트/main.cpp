#include <iostream>

using namespace std;

int n;
int idx[100001], seg[400005];

void update_seg(int idx, int lo, int hi, int offset, int new_val) {
    if(lo == hi)
        seg[idx] = new_val;
    else {
        int mid = (lo + hi) / 2;
        if(offset <= mid)
            update_seg(2 * idx, lo, mid, offset, new_val);
        else
            update_seg(2 * idx + 1, mid + 1, hi, offset, new_val);
        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }
}

int get_query(int idx, int lo, int hi, int left, int right) {
    if(lo == left && right == hi)
        return seg[idx];
    int mid = (lo + hi) / 2;
    if(right <= mid)
        return get_query(2 * idx, lo, mid, left, right);
    else if(mid < left)
        return get_query(2 * idx + 1, mid + 1, hi, left, right);
    else
        return get_query(2 * idx, lo, mid, left, mid) + get_query(2 * idx + 1, mid + 1, hi, mid + 1, right);
}

int main() {
    /**
     * 세그먼트 트리를 사용하면 정렬되지 않고 남아있는 숫자를 관리할 수 있다.
     * 홀수인 차례인 경우에는 정렬할 수보다 왼쪽에 남아있는 수의 갯수
     * 짝수인 경우에는 정렬할 수보다 오른쪽에 남아있는 수의 갯수를 출력하면 된다.
     * 정렬이 끝난 수는 세그먼트 트리에서 수를 0으로 바꿔 세지 않도록 한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 1, val; i <= n; i++) {
        cin >> val;
        idx[val] = i;
    }

    for(int i = 1; i <= n; i++)
        update_seg(1, 1, n, i, 1);

    for(int i = 1, lo = 1, hi = n, dir; i <= n; i++) {
        if(i & 1) {
            update_seg(1, 1, n, idx[lo], 0);
            cout << get_query(1, 1, n, 1, idx[lo]) << '\n';     
            lo++;
        }
        else {
            update_seg(1, 1, n, idx[hi], 0);
            cout <<  get_query(1, 1, n, idx[hi], n) << '\n';
            hi--;
        }
    }

    return 0;
}