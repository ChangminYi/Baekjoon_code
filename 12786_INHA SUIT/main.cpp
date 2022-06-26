#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

typedef tuple<int, int, int> tint;

const int MAX_H = 20;

int n, k;
vector<int> node[101];
bool visit[51][101][21];
queue<tint> que;

bool in_range(const int h) {
    return 1 <= h && h <= MAX_H;
}

int main() {
    /**
     * 현재 위치에서 이동할 수 있는 좌표를 미리 구하고,
     * 다음 나무에 해당 좌표가 존재하는 지를 체크한다. 있으면 이동한다.
     * T 기능을 사용하는 경우, 다음 칸이 이미 방문되었는지와 횟수 제한
     * 이하로 사용했는지만을 체크하고 이동한다. 가장 마지막 나무의
     * 좌표들 중에서 T를 가장 적게 사용한 이동이 정답이다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    for(int i = 1, cnt, tmp; i <= n; i++) {
        cin >> cnt;
        while(cnt--) {
            cin >> tmp;
            node[i].push_back(tmp);
        }
        sort(node[i].begin(), node[i].end());
    }

    que.push(tint(0, 1, 0));
    while(!que.empty()) {
        int cur_idx, cur_h, cur_t_use;
        tie(cur_idx, cur_h, cur_t_use) = que.front();
        que.pop();

        if(cur_idx < n) {
            int nxt_idx = cur_idx + 1;
            int tmp_h[4] = {cur_h, cur_h + 1, min(cur_h << 1, MAX_H), cur_h - 1};
            for(int i = 0; i < 4; i++) {
                if(in_range(tmp_h[i]) && binary_search(node[nxt_idx].begin(), node[nxt_idx].end(), tmp_h[i]) && !visit[cur_t_use][nxt_idx][tmp_h[i]]) {
                    visit[cur_t_use][nxt_idx][tmp_h[i]] = true;
                    que.push(tint(nxt_idx, tmp_h[i], cur_t_use));
                }
            }

            if(cur_t_use < k) {
                int nxt_t_use = cur_t_use + 1;
                for(const int& nxt_h: node[nxt_idx]) {
                    if(!visit[nxt_t_use][nxt_idx][nxt_h]) {
                        visit[nxt_t_use][nxt_idx][nxt_h] = true;
                        que.push(tint(nxt_idx, nxt_h, nxt_t_use));
                    }
                }
            }
        }
    }

    int ans = -1;
    for(int i = 0, break_flag = 0; i <= k && break_flag == 0; i++) {
        for(const int& h: node[n]) {
            if(visit[i][n][h]) {
                ans = i;
                break_flag = 1;
                break;
            }
        }
    }

    cout << ans;

    return 0;
}