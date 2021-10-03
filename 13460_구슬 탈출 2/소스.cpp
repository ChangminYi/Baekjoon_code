#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

const vector<pint> poss_dir = {
    pint(0, 1),
    pint(1, 0),
    pint(0, -1),
    pint(-1, 0)
};

const char EMPTY = '.';
const char WALL = '#';
const char EXIT = 'O';

int n, m;
int total_move = INT32_MAX;
vector<vector<char>> board;
pint init_red, init_blue;

void operator+=(pint& lhs, const pint& rhs) {
    lhs.first += rhs.first, lhs.second += rhs.second;
}

void operator-=(pint& lhs, const pint& rhs) {
    lhs.first -= rhs.first, lhs.second -= rhs.second;
}

int get_dist(const pint& lhs, const pint& rhs) {
    return abs(lhs.first - rhs.first) + abs(lhs.second - rhs.second);
}

/*
* 현재 방향의 반대방향을 반환한다.
*/
int get_rev_dir_idx(const int cur_dir_idx) {
    return ((cur_dir_idx + 2) % 4);
}

/*
* 공을 원하는 방향으로 보낸다.
* 가는 길에 출구를 만나면 표시한다.
*/
void go_to_dir(pint& cur, int dir_idx, bool& flag) {
    cur += poss_dir[dir_idx];

    while (true) {
        if (board[cur.first][cur.second] == WALL) {
            break;
        }
        else if (board[cur.first][cur.second] == EXIT) {
            flag = true;
            break;
        }
        else {
            cur += poss_dir[dir_idx];
        }
    }

    cur -= poss_dir[dir_idx];
}

void do_move(int mov_cnt, int dir_idx, pint red, pint blue) {
    if (total_move <= mov_cnt || mov_cnt > 10) {
        return;
    }
    else{
        bool flag_red = false, flag_blue = false;
        pint nxt_red = red, nxt_blue = blue;
        
        go_to_dir(nxt_red, dir_idx, flag_red);
        go_to_dir(nxt_blue, dir_idx, flag_blue);

        if (!flag_blue) {
            if (flag_red) {
                total_move = min(total_move, mov_cnt);
            }
            else {
                if (nxt_red == nxt_blue) {
                    /*
                    * 멀리서 온 공이 뒤에 있어야 한다.
                    */
                    int dist_red = get_dist(red, nxt_red);
                    int dist_blue = get_dist(blue, nxt_blue);

                    (dist_red > dist_blue ? nxt_red : nxt_blue) -= poss_dir[dir_idx];
                }

                for (int i = 0; i < 4; i++) {
                    if ((i != dir_idx) && (i != get_rev_dir_idx(dir_idx))) {
                        do_move(mov_cnt + 1, i, nxt_red, nxt_blue);
                    }
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> m;
    board.resize(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];

            if (board[i][j] == 'R') {
                init_red = pint(i, j);
                board[i][j] = EMPTY;
            }
            else if (board[i][j] == 'B') {
                init_blue = pint(i, j);
                board[i][j] = EMPTY;
            }
        }
    }

    /*
    * 네 방향으로 모두 보내본다.
    */
    for (int i = 0; i < 4; i++) {
        do_move(1, i, init_red, init_blue);
    }

    cout << (total_move == INT32_MAX ? -1 : total_move);

    return 0;
}