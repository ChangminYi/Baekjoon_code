#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;

const int WALL = 0;
const int EMPTY = 1;
const int START = 2;
const vector<pint> poss_dir = {
    pint(0, 1), pint(0, -1),
    pint(1, 0), pint(-1, 0)
};

int n, m;
pint start;
int board[1000][1000];
int dist[1000][1000];
queue<pint> que;

pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first < n) && (0 <= p.second && p.second < m);
}

void bfs() {
    dist[start.first][start.second] = 0;
    que.push(start);

    while (!que.empty()) {
        pint cur = que.front();
        que.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt) && board[nxt.first][nxt.second] == EMPTY && dist[nxt.first][nxt.second] == -1) {
                dist[nxt.first][nxt.second] = dist[cur.first][cur.second] + 1;
                que.push(nxt);
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + m, -1);

        for (int j = 0; j < m; j++) {
            cin >> board[i][j];

            if (board[i][j] == START) {
                start = pint(i, j);
            }
            else if (board[i][j] == WALL) {
                dist[i][j] = 0;
            }
        }
    }

    /*
    * 시작점을 저장한 후, 너비 우선 탐색으로 최단거리를 구하면 된다.
    * 그 후, 출력 형식을 맞춰서 결과를 출력하면 된다.
    */
    bfs();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dist[i][j] << (j == m - 1 ? '\n' : ' ');
        }
    }

    return 0;
}