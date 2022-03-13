#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r, const int _c) : row(_r), col(_c) {}
    dir operator+(const dir& other) { return dir(row + other.row, col + other.col); }
};

struct qn {
    dir cur;
    int idx;
    qn(const dir& _d, const int _i) : cur(_d), idx(_i) {}
};

const char EMPTY = '.';
const vector<dir> poss_dir = {
    dir(0, 0), dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1),
    dir(1, 1), dir(1, -1), dir(-1, 1), dir(-1, -1)
};

char board[8][8][9];
bool visit[8][8][9];
queue<qn> que;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < 8 && 0 <= d.col && d.col < 8;
}

int bfs() {
    int ret = 0;

    visit[7][0][0] = true;
    que.push(qn(dir(7, 0), 0));
    while (!que.empty() && ret == 0) {
        dir cur = que.front().cur;
        int cur_idx = que.front().idx;
        que.pop();

        if (cur_idx == 8) ret = 1;
        else if (board[cur.row][cur.col][cur_idx] == EMPTY) {
            for (const dir& pd : poss_dir) {
                dir nxt = cur + pd;
                if (in_range(nxt) && board[nxt.row][nxt.col][cur_idx] == EMPTY && !visit[nxt.row][nxt.col][cur_idx + 1]) {
                    visit[nxt.row][nxt.col][cur_idx + 1] = true;
                    que.push(qn(nxt, cur_idx + 1));
                }
            }
        }
        else continue;
    }
    
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 시작점으로부터 8번만 이동하면 미로의 모든 벽이 사라진다.
    * 따라서, 초기 상태 포함 9개의 미로를 만들고,
    * 9번째 미로에 도달하면 목표 지점에 도착 가능한 것으로 판단한다.
    */

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> board[i][j][0];
        }
    }
    for (int idx = 1; idx < 9; idx++) {
        for (int j = 0; j < 8; j++) {
            board[0][j][idx] = EMPTY;
        }
        for (int i = 1; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j][idx] = board[i - 1][j][idx - 1];
            }
        }
    }

    cout << bfs();

    return 0;
}