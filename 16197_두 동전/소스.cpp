#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(int _r = 0, int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& rhs) { return dir(row + rhs.row, col + rhs.col); }
};

struct qn {
    dir coin_1, coin_2;
    int move_cnt;
    qn(dir _c1, dir _c2, int _c) : coin_1(_c1), coin_2(_c2), move_cnt(_c) {}
};

const vector<dir> poss_dir = {
    dir(0, 1), dir(0, -1), dir(1, 0), dir(-1, 0)
};
const char COIN = 'o';
const char WALL = '#';
const char EMPTY = '.';

int n, m, ans = INT32_MAX;
dir coin[2];
char board[22][22];
bool visit[22][22][22][22];
queue<qn> que;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row <= n + 1 && 0 <= d.col && d.col <= m + 1;
}

bool at_edge(const dir& d) {
    return d.row == 0 || d.row == n + 1 || d.col == 0 || d.col == m + 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 두 동전 중 하나만 판 바깥으로 나갈 때까지 bfs로 탐색한다.
    * 두 동전이 다 나간 경우에는 다음 수를 생각하지 않는다.
    * 동전이 다시 같은 자리로 오지 않도록 이미 간 곳을 관리한다.
    */

    cin >> n >> m;
    for (int i = 0; i <= m + 1; i++) {
        board[0][i] = board[n + 1][i] = EMPTY;
    }
    for (int i = 0; i <= n + 1; i++) {
        board[i][0] = board[i][m + 1] = EMPTY;
    }
    for (int i = 1, coin_idx = 0; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> board[i][j];
            if (board[i][j] == COIN) {
                coin[coin_idx++] = dir(i, j);
                board[i][j] = EMPTY;
            }
        }
    }

    visit[coin[0].row][coin[0].col][coin[1].row][coin[1].col] = true;
    que.push(qn(coin[0], coin[1], 0));
    while (!que.empty()) {
        dir cur1 = que.front().coin_1;
        dir cur2 = que.front().coin_2;
        int cur_dist = que.front().move_cnt;
        que.pop();

        if (at_edge(cur1) != at_edge(cur2)) {
            ans = cur_dist;
            break;
        }
        else {
            for (const dir& pd : poss_dir) {
                dir nxt1 = cur1 + pd;
                dir nxt2 = cur2 + pd;
                
                if (in_range(nxt1) && in_range(nxt2)) {
                    if (board[nxt1.row][nxt1.col] == WALL) nxt1 = cur1;
                    if (board[nxt2.row][nxt2.col] == WALL) nxt2 = cur2;

                    if (!(at_edge(nxt1) && at_edge(nxt2))) {
                        if (!visit[nxt1.row][nxt1.col][nxt2.row][nxt2.col] && cur_dist < 10) {
                            visit[nxt1.row][nxt1.col][nxt2.row][nxt2.col] = true;
                            que.push(qn(nxt1, nxt2, cur_dist + 1));
                        }
                    }
                }
            }
        }
    }

    cout << (ans == INT32_MAX ? -1 : ans);

    return 0;
}