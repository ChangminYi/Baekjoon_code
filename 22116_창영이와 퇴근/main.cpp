#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct dir {
    int row, col;
    dir(int _r = 0,  int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

struct pqn {
    dir cur;
    int cost;
    pqn(const dir& _d, const int _c) : cur(_d), cost(_c) {}
    bool operator>(const pqn& other) const {
        return cost > other.cost;
    }
};

const int INF = INT32_MAX / 2; 
const vector<dir> poss_dir = {
    dir(1, 0), dir(0, 1), dir(-1, 0), dir(0, -1)
};

int n, board[1001][1001], dist[1001][1001];
priority_queue<pqn, vector<pqn>, greater<>> pq;

bool in_range(const dir& d) {
    return 1 <= d.row && d.row <= n && 1 <= d.col && d.col <= n;
}

int main() {
    /**
     * 다익스트라 알고리즘을 사용하여 해결. 특정 노드까지의 최단거리를
     * 시작점부터 해당 노드까지의 경사 중 최댓값으로 설정하였다.
     * 알고리즘을 실행한 후의 n행 n열의 최단거리를 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> board[i][j];
            dist[i][j] = INF;
        }
    }

    dist[1][1] = 0;
    for(const dir& pd: poss_dir) {
        dir nxt = dir(1, 1) + pd;
        if(in_range(nxt)) {
            dist[nxt.row][nxt.col] = abs(board[nxt.row][nxt.col] - board[1][1]);
            pq.push(pqn(nxt, dist[nxt.row][nxt.col]));
        }
    }
    while(!pq.empty()) {
        dir cur = pq.top().cur;
        int cur_cost = pq.top().cost;
        pq.pop();

        if(cur_cost > dist[cur.row][cur.col]) continue;
        for(const dir& pd: poss_dir) {
            dir nxt = cur + pd;
            int new_dist = max(cur_cost, abs(board[nxt.row][nxt.col] - board[cur.row][cur.col]));
            if(in_range(nxt) && new_dist < dist[nxt.row][nxt.col]) {
                dist[nxt.row][nxt.col] = new_dist;
                pq.push(pqn(nxt, new_dist));
            }
        }
    }

    cout << dist[n][n];

    return 0;
}