#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

typedef pair<int, int> pint;
typedef tuple<int, int, pint> node;

const int MAX = 1000;
const int EMPTY = 0;
const int WALL = 1;
const vector<pint> poss_dir = {
    pint(0, 1), pint(0, -1),
    pint(1, 0), pint(-1, 0)
};

int n, m;
pint arriv, dest;
int board[MAX + 1][MAX + 1];
bool visit[MAX + 1][MAX + 1][2] = { false };
queue<node> que;

pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint &p) {
    return (1 <= p.first && p.first <= n) && (1 <= p.second && p.second <= m);
}

int bfs() {
    que.push(node(0, 0, arriv));

    while (!que.empty()) {
        pint cur = get<2>(que.front());
        int mov_cnt = get<0>(que.front());
        bool wall_break = get<1>(que.front());
        que.pop();

        if (cur == dest) {
            return mov_cnt;
        }
        else {
            for (const pint& dir : poss_dir) {
                pint nxt = cur + dir;

                if (in_range(nxt)) {
                    if (board[nxt.first][nxt.second] == WALL) {
                        if (wall_break == 0 && !visit[nxt.first][nxt.second][wall_break]) {
                            visit[nxt.first][nxt.second][wall_break] = true;
                            que.push(node(mov_cnt + 1, 1, nxt));
                        }
                    }
                    else {
                        if (!visit[nxt.first][nxt.second][wall_break]) {
                            visit[nxt.first][nxt.second][wall_break] = true;
                            que.push(node(mov_cnt + 1, wall_break, nxt));
                        }
                    }
                }
            }
        }
    }

    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    cin >> arriv.first >> arriv.second;
    cin >> dest.first >> dest.second;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> board[i][j];
        }
    }

    /*
    * bfs이지만, 방문 체크 시의 조건에 벽을 뚫었는지의 여부가 추가.
    * 따라서 visit 배열이 3차원. 다른 조건은 일반적인 bfs와 동일.
    */
    cout << bfs();

    return 0;
}