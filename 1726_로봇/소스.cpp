#include <iostream>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(int _r = 0, int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) const { return dir(row + other.row, col + other.col); }
    bool operator==(const dir& other) const { return row == other.row && col == other.col; }
};

struct qn {
    dir cur;
    int dir_idx, dist;
    qn(dir _c, int _d = 0, int _i = 0) : cur(_c), dist(_d), dir_idx(_i) {}
};

const dir poss_dir[4] = {
    dir(0, 1), dir(0, -1), dir(1, 0), dir(-1, 0)
};

int m, n;
dir start, dest;
int start_idx, dest_idx;
bool board[101][101], visit[101][101][4];
queue<qn> que;

bool in_range(const dir& d) {
    return 1 <= d.row && d.row <= m && 1 <= d.col && d.col <= n;
}

int bfs() {
    int ret = 0;

    visit[start.row][start.col][start_idx] = true;
    que.push(qn(start, 0, start_idx));
    while (!que.empty()) {
        dir cur = que.front().cur;
        int cur_idx = que.front().dir_idx;
        int cur_dist = que.front().dist;
        que.pop();

        if (cur == dest && cur_idx == dest_idx) {
            ret = cur_dist;
            break;
        }
        else {
            int nxt_idx[2];
            if (cur_idx < 2) nxt_idx[0] = 2, nxt_idx[1] = 3;
            else nxt_idx[0] = 0, nxt_idx[1] = 1;
            for (int i = 0; i < 2; i++) {
                if (!visit[cur.row][cur.col][nxt_idx[i]]) {
                    visit[cur.row][cur.col][nxt_idx[i]] = true;
                    que.push(qn(cur, cur_dist + 1, nxt_idx[i]));
                }
            }

            dir nxt = cur;
            for (int i = 1; i <= 3; i++) {
                nxt = nxt + poss_dir[cur_idx];
                if (in_range(nxt) && board[nxt.row][nxt.col]) {
                    if (!visit[nxt.row][nxt.col][cur_idx]) {
                        visit[nxt.row][nxt.col][cur_idx] = true;
                        que.push(qn(nxt, cur_dist + 1, cur_idx));
                    }
                }
                else {
                    break;
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
    * bfs로 탐색하면 된다. 갈 수 있는 공간과 더불어 현재 위치에서의 방향까지
    * 탐색에서 고려해야 한다. 따라서 visit이 3차원이 된다.
    */

    cin >> m >> n;
    for (int i = 1, tmp; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> tmp;
            board[i][j] = (tmp == 0);
        }
    }
    cin >> start.row >> start.col >> start_idx;
    cin >> dest.row >> dest.col >> dest_idx;
    start_idx--, dest_idx--;

    cout << bfs();

    return 0;
}