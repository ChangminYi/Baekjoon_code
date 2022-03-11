#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

struct qn {
    int node, move_cnt;
    qn(const int _n = 0, const int _c = 0) : node(_n), move_cnt(_c) {}
};

int n, k;
int dir[1'002][2], fuel_req[1'002][1'002];
bool visit[1'002];

int get_cost(const int idx_1, const int idx_2) {
    int x_diff = dir[idx_1][0] - dir[idx_2][0];
    int y_diff = dir[idx_1][1] - dir[idx_2][1];
    return (int)ceil(sqrt(x_diff * x_diff + y_diff * y_diff) / 10);
}

bool bfs(const int cur_fuel) {
    bool ret = false;
    queue<qn> que;
    fill(visit, visit + n, false);

    visit[0] = true;
    que.push(qn(0, 0));
    while (!que.empty() && !ret) {
        int cur = que.front().node;
        int cur_cnt = que.front().move_cnt;
        que.pop();

        if (cur == n - 1) {
            ret = true;
        }
        else {
            for (int i = 1; i < n; i++) {
                if (!visit[i] && fuel_req[cur][i] <= cur_fuel && cur_cnt <= k) {
                    visit[i] = true;
                    que.push(qn(i, cur_cnt + 1));
                }
            }
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 도착할 때까지 최대 k번 연료를 넣을 수 있으므로, 도착할 때까지
    * k+1번 착지하는 것이 허용된다. 미리 섬마다의 연료 필요량을 구하고,
    * 이분탐색을 통하여 도착점에 갈 수 있는지를 체크하면 된다.
    */

    cin >> n >> k;
    dir[0][0] = 0, dir[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> dir[i][0] >> dir[i][1];
    }
    dir[n + 1][0] = 10'000, dir[n + 1][1] = 10'000;
    
    n += 2;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            fuel_req[i][j] = fuel_req[j][i] = get_cost(i, j);
        }
    }

    int lo = 1, hi = get_cost(0, n - 1), ans = hi;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (bfs(mid)) {
            ans = mid;
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << ans;

    return 0;
}
