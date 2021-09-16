#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

constexpr int CLEANER = -1;
const vector<pint> poss_dir = {
    pint(0, 1),
    pint(1, 0),
    pint(0, -1),
    pint(-1, 0)
};

int r, c, t;
vector<vector<int>> board, incr, decr;
pint cleaner_row(-1, -1);

pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first < r) && (0 <= p.second && p.second < c);
}

bool is_cleaner(const pint& p) {
    if ((p.first == cleaner_row.first || p.first == cleaner_row.second) && p.second == 0) {
        return true;
    }
    return false;
}

void update_dust() {
    for (int i = 0; i < r; i++) {
        fill(incr[i].begin(), incr[i].end(), 0);
        fill(decr[i].begin(), decr[i].end(), 0);
    }

    // 증가량, 감소량을 따로 저장 후 마지막에 board에 업데이트
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (board[i][j] > 0) {
                pint cur = pint(i, j);

                for (const pint& dir : poss_dir) {
                    pint nxt = cur + dir;

                    if(in_range(nxt) && !is_cleaner(nxt)){
                        incr[nxt.first][nxt.second] += board[cur.first][cur.second] / 5;
                        decr[cur.first][cur.second] += board[cur.first][cur.second] / 5;
                    }
                }
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            board[i][j] += (incr[i][j] - decr[i][j]);
        }
    }
}

void update_clean() {
    //위 순환
    for (int i = cleaner_row.first - 1; i > 0; i--) {
        board[i][0] = board[i - 1][0];
    }
    for (int i = 0; i < c - 1; i++) {
        board[0][i] = board[0][i + 1];
    }
    for (int i = 0; i < cleaner_row.first; i++) {
        board[i][c - 1] = board[i + 1][c - 1];
    }
    for (int i = c - 1; i > 1; i--) {
        board[cleaner_row.first][i] = board[cleaner_row.first][i - 1];
    }
    board[cleaner_row.first][1] = 0;

    //아래 순환
    for (int i = cleaner_row.second + 1; i < r - 1; i++) {
        board[i][0] = board[i + 1][0];
    }
    for (int i = 0; i < c - 1; i++) {
        board[r - 1][i] = board[r - 1][i + 1];
    }
    for (int i = r - 1; i > cleaner_row.second; i--) {
        board[i][c - 1] = board[i - 1][c - 1];
    }
    for (int i = c - 1; i > 1; i--) {
        board[cleaner_row.second][i] = board[cleaner_row.second][i - 1];
    }
    board[cleaner_row.second][1] = 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> r >> c >> t;
    board.resize(r, vector<int>(c));
    incr.resize(r, vector<int>(c));
    decr.resize(r, vector<int>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> board[i][j];
            
            if (board[i][j] == CLEANER) {
                if (cleaner_row.first == -1) {
                    cleaner_row.first = i;
                }
                else {
                    cleaner_row.second = i;
                }
            }
        }
    }

    for (int i = 0; i < t; i++) {
        update_dust();
        update_clean();
    }

    int cnt = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (board[i][j] > 0) {
                cnt += board[i][j];
            }
        }
    }

    cout << cnt;

    return 0;
}