#include <iostream>
#include <algorithm>

using namespace std;

struct student {
    int val, algo;
    bool operator<(const student& other) {
        return val < other.val;
    }
};

int n, k, d;
student arg[100000];
int algo_cnt[31];

int main() {
    /**
     * 알고 있는 알고리즘은 비트를 사용하여 int 형으로 표현할 수 있다.
     * 그룹 내의 실력 차가 d 이하인 경우를 보려면, 실력 오름차순으로 정렬한다.
     * 투 포인터 방식을 사용하여 효율성의 최댓값을 구하면 된다.
     * 오른쪽이 마지막 원소에 도착하면 더 이상의 탐색은 무의미하므로 종료한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k >> d;
    for(int i = 0, m, tmp; i < n; i++) {
        cin >> m >> arg[i].val;
        while(m--) {
            cin >> tmp;
            arg[i].algo |= (1 << tmp);
        }
    }

    sort(arg, arg + n);

    int ans = 0;
    for(int i = 1; i <= k; i++) {
        if(arg[0].algo & (1 << i))
            algo_cnt[i]++;
    }
    for(int lo = 0, hi = 0; hi < n - 1; lo++) {
        while(hi < n - 1 && arg[hi + 1].val - arg[lo].val <= d) {
            hi++;
            for(int i = 1; i <= k; i++) {
                if(arg[hi].algo & (1 << i))
                    algo_cnt[i]++;
            }
        }

        int cnt = 0;
        for(int i = 1; i <= k; i++) {
            if(0 < algo_cnt[i] && algo_cnt[i] < (hi - lo + 1))
                cnt++;
        }
        ans = max(ans, cnt * (hi - lo + 1));

        for(int i = 1; i <= k; i++) {
            if(arg[lo].algo & (1 << i))
                algo_cnt[i]--;
        }
    }

    cout << ans;

    return 0;
}
