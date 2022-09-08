#include <iostream>
#include <memory.h>

using namespace std;

int t, n, k, q, a, b;
int arg[100000];
int seg[2][400005];  // 0: min, 1: max

void update_seg(int segnum, int idx, int lo, int hi, int offset, int val) {
    if(lo == hi)
        seg[segnum][idx] = val;
    else {
        int mid = (lo + hi) / 2;
        if(offset <= mid)
            update_seg(segnum, 2 * idx, lo, mid, offset, val);
        else
            update_seg(segnum, 2 * idx + 1, mid + 1, hi, offset, val);

        if(segnum) seg[segnum][idx] = max(seg[segnum][2 * idx], seg[segnum][2 * idx + 1]);
        else seg[segnum][idx] = min(seg[segnum][2 * idx], seg[segnum][2 * idx + 1]);
    }
}

int get_query(int segnum, int idx, int lo, int hi, int left, int right) {
    if(lo == left && hi == right)
        return seg[segnum][idx];
    else {
        int mid = (lo + hi) / 2;
        if(right <= mid)
            return get_query(segnum, 2 * idx, lo, mid, left, right);
        else if(mid < left)
            return get_query(segnum , 2 * idx + 1, mid + 1, hi, left, right);
        else {
            if(segnum)
                return max(get_query(segnum, 2 * idx, lo, mid, left, mid), get_query(segnum , 2 * idx + 1, mid + 1, hi, mid + 1, right));
            else
                return min(get_query(segnum, 2 * idx, lo, mid, left, mid), get_query(segnum , 2 * idx + 1, mid + 1, hi, mid + 1, right));
        }
    }
}

int main() {
    /**
     * l번부터 r번까지의 선반에 같은 번호의 DVD들이 있는지는
     * 해당 구간의 최솟값이 l이고 최댓값이 r인지로 구분할 수 있다.
     * DVD의 번호가 유일하기 때문에, 만약 다른 값이 섞여 있다면 최대/최솟값이 바뀐다.
     * 세그먼트 트리 2개를 사용하여 최댓값과 최솟값을 관리하면 된다.
     * 0번 쿼리가 들어오면 원본 배열을 스왑하고 이를 세그먼트 트리에 업데이트.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);    
    
    cin >> t;
    do {
        cin >> n >> k;
        for(int i = 0; i < n; i++) {
            arg[i] = i;
            for(int j = 0; j < 2; j++)
                update_seg(j, 1, 0, n - 1, i, i);
        }

        do {
            cin >> q >> a >> b;
            if(q) {
                if(get_query(0, 1, 0, n - 1, a, b) == a && get_query(1, 1, 0, n - 1, a, b) == b)
                    cout << "YES\n";
                else
                    cout << "NO\n";
            }
            else {
                swap(arg[a], arg[b]);
                for(int i = 0; i < 2; i++) {
                    update_seg(i, 1, 0, n - 1, a, arg[a]);
                    update_seg(i, 1, 0, n - 1, b, arg[b]);
                }
            }
        } while(--k);
    } while(--t);

    return 0;
}