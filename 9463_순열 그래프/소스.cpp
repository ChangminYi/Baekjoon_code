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
    * 입력을 입력 숫자가 나온 차례로 변환하여 저장한다.
    * 다음 입력이 들어오면, 입력이 차례로 변환한 값보다 크거나 같은 값이
    * 지금까지 몇 번 나왔는지를 센 후, 그 수를 모두 더하면 된다.
    * 범위에 대한 합을 구하기 위해 세그먼트 트리 사용.
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