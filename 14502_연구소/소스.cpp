#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

const vector<pint> poss_dir = {
    make_pair(0, 1),
    make_pair(1, 0),
    make_pair(0, -1),
    make_pair(-1, 0)
};
const int EMPTY = 0;
const int WALL = 1;
const int VIRUS = 2;
const int MAX_WALL = 3;

int n, m, res = 0;
vector<vector<int>> board, tmp_board, simul_board;
vector<pint> dir_virus;
queue<pint> que;

pint operator+(const pint& lhs, const pint& rhs){
    return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first < n) && (0 <= p.second && p.second < m);
}

void copy_board(const vector<vector<int>>& from, vector<vector<int>>& to) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            to[i][j] = from[i][j];
        }
    }
}

void bfs() {
    copy_board(tmp_board, simul_board);
    for (const pint& v : dir_virus) {
        que.push(v);
    }

    while (!que.empty()) {
        pint cur = que.front();
        que.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt) && simul_board[nxt.first][nxt.second] == EMPTY) {
                simul_board[nxt.first][nxt.second] = VIRUS;
                que.push(nxt);
            }
        }
    }

    int tmp_res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (simul_board[i][j] == EMPTY) {
                tmp_res++;
            }
        }
    }

    res = max(res, tmp_res);
}

void make_wall(int cnt) {
    if (cnt == MAX_WALL) {
        bfs();
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (tmp_board[i][j] == EMPTY) {
                    tmp_board[i][j] = WALL;
                    make_wall(cnt + 1);
                    tmp_board[i][j] = EMPTY;
                }
            }
        }
    }
}

int main(void) {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> m;
    board.resize(n, vector<int>(m));
    tmp_board.resize(n, vector<int>(m));
    simul_board.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];

            if (board[i][j] == VIRUS) {
                dir_virus.push_back(make_pair(i, j));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == EMPTY) {
                copy_board(board, tmp_board);

                tmp_board[i][j] = WALL;
                make_wall(1);
                tmp_board[i][j] = EMPTY;
            }
        }
    }

    cout << res;

    return 0;
}