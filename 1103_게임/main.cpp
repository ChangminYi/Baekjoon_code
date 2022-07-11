#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r, const int _c) : row(_r), col(_c) {}
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};
const int NOT_VISIT = -1;

int n, m;
dir sp = dir(1, 1);
char board[51][51];
vector<dir> graph[51][51];
bool visit[51][51];
int degree[51][51], dp[51][51];

bool in_range(const dir& d) {
    return 0 < d.row && d.row <= n && 0 < d.col && d.col <= m;
}

void init_graph(const dir& cur) {
    int v_len = board[cur.row][cur.col] - '0';
    for(const dir& pd: poss_dir) {
        dir nxt = dir(cur.row + v_len * pd.row, cur.col + v_len * pd.col);
        if(in_range(nxt)) {
            graph[cur.row][cur.col].push_back(nxt);
            degree[nxt.row][nxt.col]++;
            if(board[nxt.row][nxt.col] != 'H' && !visit[nxt.row][nxt.col]) {
                visit[nxt.row][nxt.col] = true;
                init_graph(nxt);
            }
        }
        else {
            graph[cur.row][cur.col].push_back(dir(0, 0));
            degree[0][0]++;
        }
    }
}

bool has_cycle(const dir& start) {
    queue<dir> que;

    que.push(start);
    while(!que.empty()) {
        dir cur = que.front();
        que.pop();

        for(const dir& nxt: graph[cur.row][cur.col]) {
            if(--degree[nxt.row][nxt.col] == 0)
                que.push(nxt);
        }
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            if(degree[i][j])
                return true;
        }
    }
    return false;
}

int get_max(const dir& cur) {
    if((cur.row == 0 && cur.col == 0) || board[cur.row][cur.col] == 'H')
        return dp[cur.row][cur.col] = 0;
    else if(dp[cur.row][cur.col] != NOT_VISIT)
        return dp[cur.row][cur.col];
    else {
        int ret = 0;
        for(const dir& nxt: graph[cur.row][cur.col]) {
            ret = max(ret, get_max(nxt) + 1);
        }

        return dp[cur.row][cur.col] = ret;
    }
}

int main() {
    /**
     * 만약 보드의 움직임 중에서 사이클이 존재한다면 무한히 움직일 수 있다.
     * 따라서 사이클이 존재하면 -1을 출력한다. 이 때, 도달할 수 없는 사이클을
     * 배제하기 위해 dfs를 실행하여 도달 가능한 노드들만 그래프에 포함한다.
     * 위상 정렬을 통해 사이클 유무를 판별하고, 그래프에 대해 dfs를 실행하며
     * 각 노드의 최댓값을 저장하였다가 시작점의 dp값을 출력한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> board[i][j];
        }
        fill(dp[i] + 1, dp[i] + m + 1, NOT_VISIT);
    }
    dp[0][0] = NOT_VISIT;

    visit[sp.row][sp.col] = true;
    init_graph(sp);

    cout << (has_cycle(sp) ? -1 : get_max(sp));

    return 0;
}