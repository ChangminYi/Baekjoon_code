#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int t, n, cnt, seg[300005];
pint arg[75000];

void update_seg(int idx, int lo, int hi, int offset, int val) {
    if(lo == hi)
        seg[idx] += val;
    else {
        int mid = (lo + hi) >> 1;
        if(offset <= mid)
            update_seg(idx << 1, lo, mid, offset, val);
        else
            update_seg((idx << 1) | 1, mid + 1, hi, offset, val);
        
        seg[idx] = seg[idx << 1] + seg[(idx << 1) | 1];
    }
}

int get_query(int idx, int lo, int hi, int left, int right) {
    if(lo == left && hi == right)
        return seg[idx];
    else {
        int mid = (lo + hi) >> 1;
        if(right <= mid)
            return get_query(idx << 1, lo, mid, left, right);
        else if(mid < left)
            return get_query((idx << 1) | 1, mid + 1, hi, left, right);
        else {
            int res1 = get_query(idx << 1, lo, mid, left, mid);
            int res2 = get_query((idx << 1) + 1, mid + 1, hi, mid + 1, right);
            return res1 + res2;
        }
    }
}

int main() {
    /**
     * 북서풍으로 이동할 수 있는 것은 자신보다 남쪽 혹은 동쪽인 경우.
     * 값의 분포 범위가 매우 넓기 때문에, y좌표 기준으로 좌표 압축을 한다.
     * 그 후, 좌표를 x축 내림차순, y축 오름차순으로 정렬한다.
     * 모든 섬에 대하여 자신보다 x가 크거나 같은 섬 중 y좌표가 자신보다 작거나 같은
     * 섬의 수를 모두 더하면 된다. 세그먼트 트리를 사용하여 y좌표를 관리.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);    
    
    cin >> t;
    do {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> arg[i].first >> arg[i].second;

        sort(arg, arg + n, [](pint& lhs, pint& rhs) {
            return lhs.second < rhs.second;
        });
        memset(seg, 0, sizeof(seg));
        cnt = 0;
        for(int lo = 0, hi; lo < n; lo = hi, cnt++) {
            hi = lo + 1;
            while(hi < n && arg[lo].second == arg[hi].second)
                hi++;
            
            for(int j = lo; j < hi; j++)
                arg[j].second = cnt;
        }

        sort(arg, arg + n, [](pint& lhs, pint& rhs) {
            if(lhs.first == rhs.first) return lhs.second < rhs.second;
            else return lhs.first > rhs.first;
        });
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            ans += get_query(1, 0, n - 1, 0, arg[i].second);
            update_seg(1, 0, n - 1, arg[i].second, 1);
        }

        cout << ans << '\n';
    } while(--t);

    return 0;
}