#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

const int LEFT_SIDE = 0;
const int RIGHT_SIDE = 1;
const int MIN_VAL = 1;
const int MAX_VAL = 200000;
const long long MOD = 1000000007;

int n;
pint arg[200000];
int seg[2][800010];

void update_seg(int snum, int idx, int lo, int hi, int offset, int add_val) {
    if(lo == hi)
        seg[snum][idx] += add_val;
    else {
        int mid = (lo + hi) >> 1;
        if(offset <= mid)
            update_seg(snum, idx << 1, lo, mid, offset, add_val);
        else
            update_seg(snum, (idx << 1) | 1, mid + 1, hi, offset, add_val);
        seg[snum][idx] = seg[snum][idx << 1] + seg[snum][(idx << 1) | 1];
    }
}

int get_query(int snum, int idx, int lo, int hi, int left, int right) {
    if(hi < left || right < lo)
        return 0;
    else if(lo == left && hi == right)
        return seg[snum][idx];
    else {
        int mid = (lo + hi) >> 1;
        if(right <= mid)
            return get_query(snum, idx << 1, lo, mid, left, right);
        else if(mid < left)
            return get_query(snum, (idx << 1) | 1, mid + 1, hi, left, right);
        else {
            int res1 = get_query(snum, idx << 1, lo, mid, left, mid);
            int res2 = get_query(snum, (idx << 1) | 1, mid + 1, hi, mid + 1, right);
            return res1 + res2;
        }
    }
}

int main() {
    /**
     * 세그먼트 트리 2개로 현재 x좌표 초과/미만의 y좌표를 관리할 수 있다.
     * 좌표의 범위가 음수도 포함하므로, y축 기준으로 정렬하여 좌표 압축을 한다.
     * 그 후 x좌표 오름차순으로 정렬하여 현재 점 좌우측의 좌표를 다룬다.
     * 같은 x좌표를 가지는 구간에서는 세그먼트 트리 최신화를 미루고,
     * 별자리 수를 모두 구한 후 업데이트하여 x좌표 중복을 처리한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);    
    
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arg[i].first >> arg[i].second;

    sort(arg, arg + n, [](pint& lhs, pint& rhs) {
        return lhs.second < rhs.second;
    });
    for(int i = 0, base = INT32_MIN, cnt = 0; i < n; i++) {
        if(arg[i].second != base) {
            base = arg[i].second;
            cnt++;
        }
        arg[i].second = cnt;
        update_seg(RIGHT_SIDE, 1, MIN_VAL, MAX_VAL, arg[i].second, 1);
    }

    sort(arg, arg + n);
    long long ans = 0;
    for(int lo = 0, hi = 0; lo < n; lo = hi) {
        while(hi < n && arg[lo].first == arg[hi].first) {
            update_seg(RIGHT_SIDE, 1, MIN_VAL, MAX_VAL, arg[hi].second, -1);
            hi++;
        }

        for(int i = lo, tmp; i < hi; i++) {
            tmp = get_query(LEFT_SIDE, 1, MIN_VAL, MAX_VAL, arg[i].second + 1, MAX_VAL);
            ans += (long long)tmp * get_query(RIGHT_SIDE, 1, MIN_VAL, MAX_VAL, arg[i].second + 1, MAX_VAL);
            ans %= MOD;
        }

        for(int i = lo; i < hi; i++)
            update_seg(LEFT_SIDE, 1, MIN_VAL, MAX_VAL, arg[i].second, 1);
    }

    cout << ans;

    return 0;
}