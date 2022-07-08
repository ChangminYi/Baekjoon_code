#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

const int NOT_VISIT = INT32_MAX;
const vector<dir> poss_dir = {
    dir(0, 1), dir(0, -1), dir(1, 0), dir(-1, 0)
};

int n, m, k;
int board[2000][2000], dist[2000][2000], mane_dist[2000][2000];
dir sp;
queue<dir> que;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
}

int main() {
    /**
     * 마네킹과의 거리를 미리 bfs로 구한다.
     * 그 뒤, 시작점에서 bfs를 하여 의자까지의 최단거리를 구한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + m, NOT_VISIT);
        fill(mane_dist[i], mane_dist[i] + m, NOT_VISIT);
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];

            if(board[i][j] == 4)
                sp = dir(i, j);
            else if(board[i][j] == 3) {
                mane_dist[i][j] = 0;
                que.push(dir(i, j));
            }
        }
    }

    while(!que.empty()) {
        dir cur = que.front();
        que.pop();

        for(const dir& pd: poss_dir) {
            dir nxt = cur + pd;
            if(in_range(nxt) && mane_dist[nxt.row][nxt.col] == NOT_VISIT) {
                mane_dist[nxt.row][nxt.col] = mane_dist[cur.row][cur.col] + 1;
                que.push(nxt);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] != 1 && mane_dist[i][j] <= k)
                board[i][j] = 1;
        }
    }

    int ans = -1;
    board[sp.row][sp.col] = 0;
    dist[sp.row][sp.col] = 0;
    que.push(sp);
    while(!que.empty() && ans == -1) {
        dir cur = que.front();
        que.pop();

        if(board[cur.row][cur.col] == 2)
            ans = dist[cur.row][cur.col];
        else {
            for(const dir& pd: poss_dir) {
                dir nxt = cur + pd;
                if(in_range(nxt) && board[nxt.row][nxt.col] != 1 && dist[nxt.row][nxt.col] == NOT_VISIT) {
                    dist[nxt.row][nxt.col] = dist[cur.row][cur.col] + 1;
                    que.push(nxt);
                }
            }
        }
    }

    cout << ans;

    return 0;
}