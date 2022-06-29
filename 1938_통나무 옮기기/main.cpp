#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int r = 0, const int c = 0) : row(r), col(c) {}
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
    dir operator-(const dir& other) const {
        return dir(row - other.row, col - other.col);
    }
};

struct qn {
    dir cur;
    int idx;
    qn(const dir d, const int i) : cur(d), idx(i) {}
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};
const vector<dir> clear_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1), dir(1, 1), dir(1, -1), dir(-1, 1), dir(-1, -1)
};
const dir poss_idx[2][2] = {
    {dir(0, -1), dir(0, 1)},
    {dir(1, 0), dir(-1, 0)}
};
const int NOT_VISIT = -1;

int n, b_cnt = 0, e_cnt = 0, start_idx, end_idx;
char board[50][50];
int dist[2][50][50];
dir start_p[3], end_p[3];
queue<qn> que;

bool in_range(const vector<dir> &arg) {
    for(const dir& d : arg) {
        if(d.row < 0 || d.row >= n || d.col < 0 || d.col >= n)
            return false;
    }
    return true;
}

bool board_empty(const vector<dir> &arg) {
    for(const dir& d: arg) {
        if(board[d.row][d.col] == '1')
            return false;
    }
    return true;
}

bool can_turn(const dir &c) {
    for(const dir& cd: clear_dir) {
        dir nxt = c + cd;
        if(board[nxt.row][nxt.col] == '1')
            return false;
    }
    return true;
}

int main() {
    /**
     * 통나무의 방향을 인덱스로 변환한다. 코드에서는 가로가 0, 세로가 1의 상태를 가짐.
     * dist를 3차원으로 구성하고, 각 방향 인덱스까지 거리에 포함시켜 bfs를 한다.
     * 시작점과 도착점의 방향 상태를 구해서 일치하는 거리를 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> board[i][j];
            if(board[i][j] == 'B') {
                board[i][j] = '0';
                start_p[b_cnt++] = dir(i, j);
            }
            else if(board[i][j] == 'E') {
                board[i][j] = '0';
                end_p[e_cnt++] = dir(i, j);
            }
            dist[0][i][j] = dist[1][i][j] = NOT_VISIT;
        }
    }

    dir s_diff = start_p[0] - start_p[1];
    start_idx = (s_diff.row == 0 ? 0 : 1);
    dist[start_idx][start_p[1].row][start_p[1].col] = 0;
    que.push(qn(start_p[1], start_idx));
    while(!que.empty()) {
        dir cur = que.front().cur;
        int cur_idx = que.front().idx;
        que.pop();

        for(const dir& pd: poss_dir) {
            dir nxt = cur + pd;
            vector<dir> nxt_set = {nxt + poss_idx[cur_idx][0], nxt, nxt + poss_idx[cur_idx][1]};
            if(in_range(nxt_set) && board_empty(nxt_set) && dist[cur_idx][nxt.row][nxt.col] == NOT_VISIT) {
                dist[cur_idx][nxt.row][nxt.col] = dist[cur_idx][cur.row][cur.col] + 1;
                que.push(qn(nxt, cur_idx));
            }
        }
        int nxt_idx = (cur_idx + 1) % 2;
        vector<dir> nxt_set = {cur + poss_idx[nxt_idx][0], cur, cur + poss_idx[nxt_idx][1]};
        if(in_range(nxt_set) && can_turn(cur) && dist[nxt_idx][cur.row][cur.col] == NOT_VISIT) {
            dist[nxt_idx][cur.row][cur.col] = dist[cur_idx][cur.row][cur.col] + 1;
            que.push(qn(cur, nxt_idx));
        }
    }

    dir e_diff = e_diff = end_p[0] - end_p[1];
    end_idx = (e_diff.row == 0 ? 0 : 1);
    cout << (dist[end_idx][end_p[1].row][end_p[1].col] == NOT_VISIT ? 0 : dist[end_idx][end_p[1].row][end_p[1].col]);

    return 0;
}