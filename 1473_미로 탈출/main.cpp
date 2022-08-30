#include <iostream>
#include <vector>
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
    bool operator==(const dir& other) const {
        return row == other.row && col == other.col;
    }
};

struct qn {
    dir node;
    int visit_bit;
    qn(const dir& _n, const int _vb) {
        node = _n, visit_bit = _vb;
    }
};

const int NOT_VISIT = -1;
const vector<dir> poss_dir[4] = {
    {dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)},
    {},
    {dir(1, 0), dir(-1, 0)},
    {dir(0, 1), dir(0, -1)}
};

int n, m;
int init_b[7][7];
int dist[7][7][1 << 14];
char tmp;
queue<qn> q;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
}

int get_idx(const dir& d, const int _vb) {
    if(init_b[d.row][d.col] < 2) return init_b[d.row][d.col];
    else {
        bool flag = false;
        if(_vb & (1 << d.row)) flag = !flag;
        if(_vb & (1 << (n + d.col))) flag = !flag;

        if(flag) return (init_b[d.row][d.col] == 2 ? 3 : 2);
        else return init_b[d.row][d.col];
    }
}

bool is_bidirection(const dir& cur, const dir& nxt, const int _vb) {
    for(const dir& pd: poss_dir[get_idx(nxt, _vb)]) {
        dir pre = nxt + pd;
        if(cur == pre) return true;
    }
    return false;
}

int main() {
    /**
     * 행과 열의 수를 모두 더해도 최대 14이다. 따라서 어떤 행 혹은 열이
     * 뒤집힌 상태인지를 비트마스킹으로 관리할 수 있다. 현재 갈 수 있는 방향을
     * 비트를 사용하여 구하고, 가고자 하는 칸에서 다시 현재 칸을 올 수 있는지
     * 체크한 후 진행해야 한다. bfs를 통해 현재 위치와 비트를 같이 관리하며
     * 최초로 도착점에 도달한 순간의 시간을 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    dir sp = dir(0, 0), ep = dir(n - 1, m - 1);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> tmp;
            init_b[i][j] = tmp - 'A';
            fill(dist[i][j], dist[i][j] + (1 << (n + m)), NOT_VISIT);
        }
    }
    
    int ans = NOT_VISIT;
    dist[sp.row][sp.col][0] = 0;
    q.push(qn(sp, 0));
    while(!q.empty()) {
        dir cur = q.front().node;
        int cur_vb = q.front().visit_bit;
        q.pop();

        if(cur == ep) {
            ans = dist[ep.row][ep.col][cur_vb];
            break;
        }

        for(const dir& pd: poss_dir[get_idx(cur, cur_vb)]) {
            dir nxt = cur + pd;
            if(in_range(nxt) && is_bidirection(cur, nxt, cur_vb) && dist[nxt.row][nxt.col][cur_vb] == NOT_VISIT) {
                dist[nxt.row][nxt.col][cur_vb] = dist[cur.row][cur.col][cur_vb] + 1;
                q.push(qn(nxt, cur_vb));
            }
        }
        int nxt_vb = cur_vb ^ ((1 << cur.row) | (1 << (n + cur.col)));
        if(dist[cur.row][cur.col][nxt_vb] == NOT_VISIT) {
            dist[cur.row][cur.col][nxt_vb] = dist[cur.row][cur.col][cur_vb] + 1;
            q.push(qn(cur, nxt_vb));
        }
    }

    cout << ans;

    return 0;
}