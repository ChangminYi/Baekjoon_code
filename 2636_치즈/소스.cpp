#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

const int CHEESE = 1;
const int EMPTY = 0;
const int OUTER = 2;
const vector<pint> poss_dir = {
    pint(0, 1), pint(0, -1),
    pint(1, 0), pint(-1, 0)
};

int n, m, remain_cheese = 0;
int board[100][100];
queue<pint> que;

const pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first < n) && (0 <= p.second && p.second < m);
}

int update_board() {
    int remove_cnt = 0;

    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            if (board[i][j] == CHEESE) {
                bool adj_outer = false;
                pint cur = pint(i, j);

                for (const pint& dir : poss_dir) {
                    pint nxt = cur + dir;
                    if (board[nxt.first][nxt.second] == OUTER) {
                        adj_outer = true;
                        break;
                    }
                }

                if (adj_outer) {
                    remove_cnt++;
                    que.push(cur);
                }
            }
        }
    }

    while (!que.empty()) {
        pint cur = que.front();
        que.pop();
        board[cur.first][cur.second] = OUTER;
    }

    remain_cheese -= remove_cnt;
    return remove_cnt;
}

void update_outer() {
    bool visit[100][100] = { false };

    visit[0][0] = true;
    board[0][0] = OUTER;
    que.push(pint(0, 0));
    while (!que.empty()) {
        pint cur = que.front();
        que.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt)) {
                if (board[nxt.first][nxt.second] != CHEESE && !visit[nxt.first][nxt.second]) {
                    board[nxt.first][nxt.second] = OUTER;
                    visit[nxt.first][nxt.second] = true;
                    que.push(nxt);
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (board[i][j] == CHEESE) {
                remain_cheese++;
            }
        }
    }

    /*
    * 가장 바깥에서부터 치즈를 없애야 하므로, 가장 바깥의 공기는
    * 따로 분류한다. 가장 바깥 공기와 닿은 치즈는 녹여서 없애고,
    * 그 자리를 바깥 공기로 바꾼다. 그리고 빈 공간이 바깥 공기와
    * 닿으면 그 공간도 바깥이 되므로 계속 업데이트.
    */
    for (int i = 1, last_erase; ; i++) {
        update_outer();
        last_erase = update_board();
        
        if (remain_cheese == 0) {
            cout << i << '\n' << last_erase;
            break;
        }
    }

    return 0;
}