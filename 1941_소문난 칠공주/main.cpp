#include <iostream>
#include <memory.h>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

int ans;
char board[5][5];
bool visit[25];
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

bool over_four() {
    int cnt = 0;
    for(int i = 0; i < 25; i++) {
        if(visit[i] && board[i / 5][i % 5] == 'S') cnt++;
    }

    return cnt >= 4;
}

bool in_range(const int r, const int c) {
    return 0 <= r && r < 5 && 0 <= c && c < 5;
}

bool all_adj() {
    queue<pint> q;
    bool bfs_visit[5][5];

    memset(bfs_visit, false, sizeof(bfs_visit));

    bool q_init = false;
    for(int i = 0; i < 25 && !q_init; i++) {
        if(visit[i] && !q_init) {
            q_init = true;
            q.push(pint(i / 5, i % 5));
            bfs_visit[i / 5][i % 5] = true;
        }
    }

    int cnt = 1;
    while(!q.empty() && cnt < 7) {
        int r = q.front().first, c = q.front().second;
        q.pop();

        for(int i = 0, nr, nc; i < 4; i++) {
            nr = r + dr[i], nc = c + dc[i];
            if(in_range(nr, nc) && visit[5 * nr + nc] && !bfs_visit[nr][nc]) {
                bfs_visit[nr][nc] = true;
                q.push(make_pair(nr, nc));
                cnt++;
            }
        }
    }

    return cnt == 7;
}

void dfs(int idx, int cnt) {
    if(cnt == 7) {
        if(over_four() && all_adj())
            ans++;
    }   
    else {
        for(int i = idx; i < 25; i++) {
            if(visit[i]) continue;
            visit[i] = true;
            dfs(i, cnt + 1);
            visit[i] = false;
        }
    }
}

int main() {
    /**
     * dfs와 백트래킹을 통해 일단 25명 중 7명을 선택한다.
     * 선택된 7명 중 S가 4개 이상인지를 확인한 후,
     * bfs를 통해 선택된 7명 모두를 방문할 수 있는지를 확인한다.
     * 모두 가능하면 올바른 조합을 고른 것이다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);    
    
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cin >> board[i][j];
        }
    }
    
    dfs(0, 0);
    
    cout << ans;
    
    return 0;
}