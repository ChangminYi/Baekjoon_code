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

struct pqn {
    dir pos;
    int dist;
    pqn(const dir& _p, const int _d) : pos(_p), dist(_d) {}
    bool operator>(const pqn& other) const {
        return dist > other.dist;
    }
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};
const int INF = INT32_MAX / 2;

int n, m;
char board[300][300];
int dist[300][300];
dir sp, ep;
priority_queue<pqn, vector<pqn>, greater<>> pq;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
}

int main() {
    /**
     * 칸이 1인 경우, 직전 노드에서 거리가 1 추가된다.
     * 칸이 0인 경우, 파동이 사라지지 않고 진행하므로 거리가 추가되지 않는다.
     * 이는 다익스트라 알고리즘을 통해 최단거리를 구하면 되는 문제.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> sp.row >> sp.col >> ep.row >> ep.col;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
        fill(dist[i], dist[i] + m, INF);
    }
    sp.row--, sp.col--, ep.row--, ep.col--;
    board[sp.row][sp.col] = '1';
    board[ep.row][ep.col] = '1';

    dist[sp.row][sp.col] = 0;
    pq.push(pqn(sp, 0));
    while(!pq.empty()) {
        dir cur = pq.top().pos;
        int cur_dist = pq.top().dist;
        pq.pop();

        if(cur_dist > dist[cur.row][cur.col])
            continue;
        for(const dir& pd: poss_dir) {
            dir nxt = cur + pd;
            int new_dist = (board[nxt.row][nxt.col] == '0' ? cur_dist : cur_dist + 1);
            if(in_range(nxt) && new_dist < dist[nxt.row][nxt.col]) {
                dist[nxt.row][nxt.col] = new_dist;
                pq.push(pqn(nxt, new_dist));
            }
        }
    }

    cout << dist[ep.row][ep.col];

    return 0;
}