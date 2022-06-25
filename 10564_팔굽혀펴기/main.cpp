#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

typedef tuple<int, int, int> tint;

const int MAX_N = 5001;
const int MAX_T = 600;

int t, n, m;
int s[10];
bool visit[MAX_T][MAX_N];
queue<tint> que;

int main() {
    /**
     * bfs와 dp를 같이 사용하여 해결. visit 배열을 dp 배열과 같이 사용.
     * 배열의 행은 총 득점, 열은 총 팔굽혀펴기 횟수로 설정하였음.
     * 그리고 현재 상태에서 팔굽혀펴기를 했을 때 전체 득점이 범위 내에 있다면
     * 득점했을 때의 상태를 큐에 삽입하여 탐색한다. 가장 많은 득점을 한
     * 경기를 선택해야 함으로, dp 배열을 인덱스 내림차순으로 검색하여
     * 방문을 했는지를 체크하고, 그에 따라 답을 출력하면 됨.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            cin >> s[i];
        }
        
        for(int i = 0; i < MAX_T; i++) {
            fill(visit[i], visit[i] + n + 1, false);
        }

        for(int i = 0; i < m; i++) {
            visit[s[i]][s[i]] = true;
            que.push(tint(s[i], s[i], s[i]));
        }
        while(!que.empty()) {
            int cur_t_score, cur_last_added, cur_t_pushup;
            tie(cur_t_score, cur_last_added, cur_t_pushup) = que.front();
            que.pop();

            for(int i = 0; i < m; i++) {
                int nxt_t_score = cur_t_score + s[i];
                int nxt_last_added = cur_last_added + s[i];
                int nxt_t_pushup = cur_t_pushup + nxt_last_added;
                if(nxt_t_pushup <= n && !visit[nxt_t_score][nxt_t_pushup]) {
                    visit[nxt_t_score][nxt_t_pushup] = true;
                    que.push(tint(nxt_t_score, nxt_last_added, nxt_t_pushup));
                }
            }
        }

        int ans = -1;
        for(int i = MAX_T - 1; i > 0; i--) {
            if(visit[i][n]) {
                ans = i;
                break;
            }
        }

        cout << ans << '\n';
    } while(--t);

    return 0;
}