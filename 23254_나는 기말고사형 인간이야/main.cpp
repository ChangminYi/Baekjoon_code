#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

struct pqn {
    int add_val, remain;
    pqn(const int _a, const int _p) : add_val(_a), remain(_p) {}
    bool operator<(const pqn& other) const {
        return add_val < other.add_val;
    }
};

int n, m, arg[200000], ans = 0;
priority_queue<pqn> pq;

int main() {
    /**
     * 1시간 동안 학습하여 성적이 가장 많이 오르는 과목 순으로 공부하면 된다.
     * 가능한 증가량이 1시간 공부의 증가량보다 작은 경우는 1시간 증가량을 줄인다.
     * 우선순위 큐를 사용하여 1시간 단위로 관리하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> arg[i];
        ans += arg[i];
    }
    for(int i = 0, tmp; i < m; i++) {
        cin >> tmp;
        pq.push(pqn(min(tmp, 100 - arg[i]), 100 - arg[i]));
    }

    for(int i = 0; i < 24 * n && !pq.empty(); i++) {
        int cur_add_val = pq.top().add_val;
        int cur_remain = pq.top().remain;
        pq.pop();

        ans += min(cur_add_val, cur_remain);
        if(cur_add_val < cur_remain)
            pq.push(pqn(min(cur_add_val, cur_remain - cur_add_val), cur_remain - cur_add_val));
    }

    cout << ans;

    return 0;
}