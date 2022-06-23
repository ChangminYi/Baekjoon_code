#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(int _r = 0, int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) {
        return dir(row + other.row, col + other.col);
    }
    void operator+=(const dir& rhs) {
        row += rhs.row, col += rhs.col;
    }
};

struct qn {
    dir pos;
    int l_cnt, r_cnt;
    qn(dir _p, int _l, int _r) : pos(_p), l_cnt(_l), r_cnt(_r) {}
};

const vector<dir> pd = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};

int n, m, left_cnt, right_cnt, visit_cnt = 1;
string board[1000];
dir start_point;
bool visit[1000][1000];
queue<qn> que;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
}

int main() {
    /**
     * bfs를 사용하여 탐색을 하면 되지만, 좌우로 이동 가능한 횟수가 남아 있는지를
     * 확인해야 한다. 또한, 방문하지 않은 칸에 방문한 경우, 해당 칸에서 이동할 수
     * 있는 모든 상하의 칸들을 모두 같은 거리로 방문했다고 가정하고 큐에
     * 삽입하면서 탐색을 이어나가야 한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> left_cnt >> right_cnt;
    for(int i = 0; i < n; i++) {
        cin >> board[i];
        for(int j = 0; j < m; j++) {
            if(board[i][j] == '2') {
                start_point = dir(i, j);
                visit[i][j] = true;
            }
        }
    }

    que.push(qn(start_point, left_cnt, right_cnt));
    for(int i = 0; i < 2; i++) {
        for(dir cur = start_point + pd[i]; in_range(cur) && board[cur.row][cur.col] != '1'; cur += pd[i]) {
            visit[cur.row][cur.col] = true;
            visit_cnt++;
            que.push(qn(cur, left_cnt, right_cnt));
        }
    }
    while(!que.empty()) {
        dir cur = que.front().pos;
        int cur_l = que.front().l_cnt;
        int cur_r = que.front().r_cnt;
        que.pop();
        
        if(cur_l > 0) {
            dir nxt = cur + pd[3];
            if(in_range(nxt) && board[nxt.row][nxt.col] != '1' && !visit[nxt.row][nxt.col]) {
                visit[nxt.row][nxt.col] = true;
                visit_cnt++;
                que.push(qn(nxt, cur_l - 1, cur_r));
                for(int i = 0; i < 2; i++) {
                    for(dir vert = nxt + pd[i]; in_range(vert) && board[vert.row][vert.col] != '1'; vert += pd[i]) {
                        visit[vert.row][vert.col] = true;
                        visit_cnt++;
                        que.push(qn(vert, cur_l - 1, cur_r));
                    }
                }
            }
        }
        if(cur_r > 0) {
            dir nxt = cur + pd[2];
            if(in_range(nxt) && board[nxt.row][nxt.col] != '1' && !visit[nxt.row][nxt.col]) {
                visit[nxt.row][nxt.col] = true;
                visit_cnt++;
                que.push(qn(nxt, cur_l, cur_r - 1));
                for(int i = 0; i < 2; i++) {
                    for(dir vert = nxt + pd[i]; in_range(vert) && board[vert.row][vert.col] != '1'; vert += pd[i]) {
                        visit[vert.row][vert.col] = true;
                        visit_cnt++;
                        que.push(qn(vert, cur_l, cur_r - 1));
                    }
                }
            }
        }
    }

    cout << visit_cnt;

    return 0;
}