#include <iostream>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) {
        row = _r, col = _c;
    }
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

struct qn {
    dir node;
    int time_idx, visit_bit;
    qn(const dir& _d, const int _ti, const int _vb) {
        node = _d, time_idx = _ti, visit_bit = _vb;
    }
};

const dir poss_dir[4] = {
    dir(-1, 0), dir(0, 1), dir(1, 0), dir(0, -1)
};
const int INF = INT32_MAX / 2;

int m, n, k;
int init_door[101][101], t_num[101][101];
int dist[101][101][4][1 << 8];
char tmp;

int c_to_idx(const char c) {
    if(c == 'N') return 0;
    else if(c == 'E') return 1;
    else if(c == 'S') return 2;
    else return 3;
}

bool in_range(const dir &d) {
    return 1 <= d.row && d.row <= m && 1 <= d.col && d.col <= n;
}

void clear_var() {
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            for(int r = 0; r < 4; r++)
                fill(dist[i][j][r], dist[i][j][r] + (1 << k), INF);
            t_num[i][j] = INF;
        }
    }
}

int main() {
    /**
     * bfs로 미로를 탐색한다. 탐색 시 현재 문의 방향과 찾은 보물의 상태에서의
     * 최소 시간을 저장한다. 탐색 도중 최초로 도착점이면서 모든 보물을 찾은 때의 시간이 최소 시간이다.
     * 시간에 따라 문의 방향이 바뀌는 것을 조심해야 한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    while(true) {
        cin >> m >> n;
        if(m == 0 && n == 0) break;

        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                cin >> tmp;
                init_door[i][j] = c_to_idx(tmp);
            }
        }
        cin >> k;
        clear_var();
        for(int i = 0, r, c; i < k; i++) {
            cin >> r >> c;
            t_num[r][c] = i;
        }

        int ans = 0;
        queue<qn> q;
        dist[1][1][0][0] = 0;
        q.push(qn(dir(1, 1), 0, 0));
        while(!q.empty()) {
            dir cur = q.front().node;
            int cur_ti = q.front().time_idx;
            int cur_vb = q.front().visit_bit;
            q.pop();

            if(cur.row == m && cur.col == n && cur_vb == (1 << k) - 1) {
                ans = dist[m][n][cur_ti][cur_vb];
                break;
            }

            int nxt_ti = (cur_ti + 1) % 4;
            if(dist[cur.row][cur.col][nxt_ti][cur_vb] == INF) {
                dist[cur.row][cur.col][nxt_ti][cur_vb] = dist[cur.row][cur.col][cur_ti][cur_vb] + 1;
                q.push(qn(cur, nxt_ti, cur_vb));
            }
            
            dir nxt = cur + poss_dir[(cur_ti + init_door[cur.row][cur.col]) % 4];
            if(in_range(nxt)) {
                int nxt_vb = (t_num[nxt.row][nxt.col] == INF ? cur_vb : cur_vb | (1 << t_num[nxt.row][nxt.col]));
                if(dist[nxt.row][nxt.col][nxt_ti][nxt_vb] == INF) {
                    dist[nxt.row][nxt.col][nxt_ti][nxt_vb] = dist[cur.row][cur.col][cur_ti][cur_vb] + 1;
                    q.push(qn(nxt, nxt_ti, nxt_vb));
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}