#include <iostream>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) const {
        return dir(this->row + other.row, this->col + other.col);
    }
};

struct pqn {
    dir node;
    int dist;
    pqn(const dir _n, const int _d = 0) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const {
        return this->dist > other.dist;
    }
};

const char WALL = '1';
const int INF = INT32_MAX / 2;
const vector<dir> poss_dir = {
    dir(0, 1), dir(0, -1), dir(1, 0), dir(-1, 0)
};

int n, m;
char board[100][100];
int dist[100][100];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

bool in_range(const dir& p) {
    return 0 <= p.row && p.row < n && 0 <= p.col && p.col < m;
}

void dijk() {
    dist[0][0] = 0;
    pq.push(pqn(dir(0, 0), 0));
    while (!pq.empty()) {
        dir cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur.row][cur.col]) {
            for (const dir& d : poss_dir) {
                dir nxt = cur + d;
                if (in_range(nxt)) {
                    int new_dist = cur_dist + (board[nxt.row][nxt.col] == WALL ? 1 : 0);
                    if (new_dist < dist[nxt.row][nxt.col]) {
                        dist[nxt.row][nxt.col] = new_dist;
                        pq.push(pqn(nxt, new_dist));
                    }
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 최단거리를 구하되, 거리의 정의를 부순 벽의 수로 설정.
    * 나머지는 다익스트라 알고리즘으로 구하면 된다.
    */
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            dist[i][j] = INF;
        }
    }

    dijk();

    cout << dist[n - 1][m - 1];
    
    return 0;
}