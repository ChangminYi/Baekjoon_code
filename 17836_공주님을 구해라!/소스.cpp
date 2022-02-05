#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(int r = 0, int c = 0) : row(r), col(c) {}
    dir operator+(const dir& other) const { return dir(row + other.row, col + other.col); }
};
struct qn {
    dir cur;
    int dist;
    qn(dir c, int d) : cur(c), dist(d) {}
};

const vector<dir> poss_dir = {
    dir(0, 1), dir(0, -1), dir(1, 0), dir(-1, 0)
};

const int INF = INT32_MAX / 2;
const int WALL = 1;
const int SWORD = 2;

int n, m, t, sword_to_princess;
dir sword_dir;
int board[101][101], dist[101][101];
queue<qn> que;

bool in_range(const dir& d) {
    return 1 <= d.row && d.row <= n && 1 <= d.col && d.col <= m;
}

void bfs() {
    dist[1][1] = 0;
    que.push(qn(dir(1, 1), 0));
    while (!que.empty()) {
        dir cur = que.front().cur;
        int cur_dist = que.front().dist;
        que.pop();

        for (const dir& d : poss_dir) {
            dir nxt = cur + d;
            if (in_range(nxt) && board[nxt.row][nxt.col] != WALL) {
                if (cur_dist + 1 < dist[nxt.row][nxt.col]) {
                    dist[nxt.row][nxt.col] = cur_dist + 1;
                    que.push(qn(nxt, cur_dist + 1));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 공주에게 도달하는 경로는 두 가지가 있다.
    * 검을 찾지 않고 바로 가는 경우와 검을 찾은 후 가는 경우.
    * 따라서 두 거리의 최솟값이 정답이 된다.
    * 도달할 수 없는 경우에 대해서 예외처리만 해주면 된다.
    */
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> board[i][j];
            dist[i][j] = INF;
            if (board[i][j] == SWORD) {
                sword_to_princess = (n - i) + (m - j);
                sword_dir = dir(i, j);
            }
        }
    }

    bfs();

    int dist_1 = dist[n][m];
    int dist_2 = (dist[sword_dir.row][sword_dir.col] == INF ? INF : dist[sword_dir.row][sword_dir.col] + sword_to_princess);
    if (min(dist_1, dist_2) <= t) cout << min(dist_1, dist_2);
    else cout << "Fail";

    return 0;
}