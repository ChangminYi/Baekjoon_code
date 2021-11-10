#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>

using namespace std;

typedef tuple<int, int, int> dir;
typedef pair<int, dir> node;

const int RIPE = 1;
const int NOT_RIPE = 0;
const int MAX = 100;
const vector<dir> poss_dir = {
    dir(0, 0, 1), dir(0, 0, -1),
    dir(0, 1, 0), dir(0, -1, 0),
    dir(1, 0, 0), dir(-1, 0, 0)
};

int m, n, h;
int not_riped = 0;
int board[MAX][MAX][MAX];
bool visit[MAX][MAX][MAX] = { false };
queue<node> que;

dir operator+(const dir& lhs, const dir& rhs) {
    return dir(get<0>(lhs) + get<0>(rhs), get<1>(lhs) + get<1>(rhs), get<2>(lhs) + get<2>(rhs));
}

bool in_range(const dir& p) {
    int x = get<0>(p), y = get<1>(p), z = get<2>(p);
    return (0 <= x && x < n) && (0 <= y && y < m) && (0 <= z && z < h);
}

int bfs() {
    int ret = 0;

    while (!que.empty()) {
        size_t iter = que.size();

        for (size_t i = 0; i < iter; i++) {
            dir cur = que.front().second;
            int cur_cnt = que.front().first;
            ret = max(ret, cur_cnt);
            que.pop();

            for (const dir& d : poss_dir) {
                dir nxt = cur + d;

                if (in_range(nxt)) {
                    if (board[get<0>(nxt)][get<1>(nxt)][get<2>(nxt)] == NOT_RIPE) {
                        if (!visit[get<0>(nxt)][get<1>(nxt)][get<2>(nxt)]) {
                            board[get<0>(nxt)][get<1>(nxt)][get<2>(nxt)] = RIPE;
                            not_riped--;
                            visit[get<0>(nxt)][get<1>(nxt)][get<2>(nxt)] = true;
                            que.push(node(cur_cnt + 1, nxt));
                        }
                    }
                }
            }
        }
    }

    return (not_riped == 0 ? ret : -1);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> m >> n >> h;
    for (int k = 0; k < h; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> board[i][j][k];

                if (board[i][j][k] == RIPE) {
                    visit[i][j][k] = true;
                    que.push(node(0, dir(i, j, k)));
                }
                else if (board[i][j][k] == NOT_RIPE) {
                    not_riped++;
                }
            }
        }
    }

    /*
    * 3차원 bfs.
    * 인접 노드 확인과 남은 토마토 수 세기만 잘 해주면 됨.
    */
    cout << bfs();

    return 0;
}