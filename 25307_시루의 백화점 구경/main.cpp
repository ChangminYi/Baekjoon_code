#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

struct qn {
    dir pos;
    int dist;
    qn(const dir _p, const int _d) : pos(_p), dist(_d) {}
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};

int n, m, k;
dir sp;
queue<qn> que;
vector<dir> mannequin;
int board[2000][2000];
bool visit[2000][2000];

bool in_range(const dir &d) {
    return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
}

bool far_manne(const dir &d) {
    int min_dist = INT32_MAX;
    for(const dir& m: mannequin) {
        int diff = abs(d.row - m.row) + abs(d.col - m.col);
        if(diff < min_dist)
            min_dist = diff;
    }
    return min_dist > k;
}

int main() {
    /**
     * bfs를 통해 해결할 수 있다. 마네킹과의 최소 거리를 지키는 지를
     * 판단하면서 탐색하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
            if(board[i][j] == 4)
                sp = dir(i, j);
            else if(board[i][j] == 3) {
                board[i][j] = 1;
                mannequin.push_back(dir(i, j));
            }
        }
    }

    int ans = -1;
    visit[sp.row][sp.col] = true;
    que.push(qn(sp, 0));
    while(!que.empty() && ans == -1) {
        dir cur = que.front().pos;
        int cur_dist = que.front().dist;
        que.pop();

        if(board[cur.row][cur.col] == 2)
            ans = cur_dist;
        else {
            for(const dir& pd: poss_dir) {
                dir nxt = cur + pd;
                if(in_range(nxt) && board[nxt.row][nxt.col] != 1 && far_manne(nxt) && !visit[nxt.row][nxt.col]) {
                    visit[nxt.row][nxt.col] = true;
                    que.push(qn(nxt, cur_dist + 1));
                }
            }
        }
    }

    cout << ans;

    return 0;
}
