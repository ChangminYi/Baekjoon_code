#include <iostream>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c){}
    dir operator+(const dir& other) const { return dir(row + other.row, col + other.col); }
};

struct qn {
    dir pos;
    int dist;
    qn(const dir _p, const int _d) : pos(_p), dist(_d) {}
};

const char EMPTY = '.';
const char WALL = '#';
const char START = '@';
const char FIRE = '*';
const vector<dir> poss_dir = {
    dir(0, 1), dir(0, -1), dir(1, 0), dir(-1, 0)
};

int testcase, row, col, res;
char board[1000][1000];
int fire_dist[1000][1000];
bool visit[1000][1000];
dir start;
queue<dir> fire_que;

void init() {
    for (int i = 0; i < row; i++) {
        fill(fire_dist[i], fire_dist[i] + col, INT32_MAX);
        fill(visit[i], visit[i] + col, false);
    }
}

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < row && 0 <= d.col && d.col < col;
}

bool can_exit(const dir& d) {
    return d.row == 0 || d.row == row - 1 || d.col == 0 || d.col == col - 1;
}

void init_fire() {
    while (!fire_que.empty()) {
        dir cur = fire_que.front();
        fire_que.pop();

        for (const dir& pd : poss_dir) {
            dir nxt = cur + pd;
            if (in_range(nxt) && board[nxt.row][nxt.col] == EMPTY && fire_dist[cur.row][cur.col] + 1 < fire_dist[nxt.row][nxt.col]) {
                fire_dist[nxt.row][nxt.col] = fire_dist[cur.row][cur.col] + 1;
                fire_que.push(nxt);
            }
        }
    }
}

int bfs() {
    int ret = -1;
    queue<qn> que;

    visit[start.row][start.col] = true;
    que.push(qn(start, 0));
    while (!que.empty()) {
        dir cur = que.front().pos;
        int cur_dist = que.front().dist;
        que.pop();

        if (can_exit(cur)) {
            ret = cur_dist + 1;
            break;
        }
        else {
            for (const dir& pd: poss_dir) {
                dir nxt = cur + pd;
                if (in_range(nxt) && board[nxt.row][nxt.col] == EMPTY && !visit[nxt.row][nxt.col] && cur_dist + 1 < fire_dist[nxt.row][nxt.col]) {
                    visit[nxt.row][nxt.col] = true;
                    que.push(qn(nxt, cur_dist + 1));
                }
            }
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> testcase;
    for (; testcase; testcase--) {
        cin >> col >> row;
        init();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cin >> board[i][j];
                if (board[i][j] == START) {
                    start = dir(i, j);
                    board[i][j] = EMPTY;
                }
                else if (board[i][j] == FIRE) {
                    fire_que.push(dir(i, j));
                    fire_dist[i][j] = 0;
                }
            }
        }

        init_fire();
        if ((res = bfs()) == -1) cout << "IMPOSSIBLE\n";
        else cout << res << '\n';
    }

    return 0;
}