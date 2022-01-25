#include <iostream>
#include <stack>
#include <array>
#include <cmath>

using namespace std;

struct pos {
    int row, col;
    pos(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    pos operator+(const pos& other) const { return pos(this->row + other.row, this->col + other.col); }
    void operator+=(const pos& other) { this->row += other.row, this->col += other.col; }
    bool operator==(const pos& other) const { return this->row == other.row && this->col == other.col; }
};

struct fish {
    pos p;
    bool is_alive = true;
    int number, dir_idx;
    fish(const pos& _p = pos(), const int _n = -1, const int _idx = -1) : p(_p), number(_n), dir_idx(_idx) {}
    bool operator<(const fish& other) { return this->number < other.number; }
};

const int NO_FISH = -2;
const int SHARK = -1;
const pos poss_dir[8] = {
    pos(-1, 0), pos(-1, -1), pos(0, -1), pos(1, -1),
    pos(1, 0), pos(1, 1), pos(0, 1), pos(-1, 1)
};

bool in_range(const pos& p) {
    return 0 <= p.row && p.row < 4 && 0 <= p.col && p.col < 4;
}

int simulate(pos shark_pos, array<fish, 17>& prev_list) {
    int board[4][4];
    array<fish, 17> fish_list;
    int eat_number = 0, shark_dir;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = NO_FISH;
        }
    }

    for (int i = 1; i <= 16; i++) {
        if (prev_list[i].is_alive) {
            if (prev_list[i].p == shark_pos) {
                eat_number = prev_list[i].number;
                shark_dir = prev_list[i].dir_idx;
                fish_list[i].is_alive = false;
                board[prev_list[i].p.row][prev_list[i].p.col] = SHARK;
            }
            else {
                fish_list[i] = prev_list[i];
                board[prev_list[i].p.row][prev_list[i].p.col] = prev_list[i].number;
            }
        }
        else {
            fish_list[i].is_alive = false;
        }
    }

    for (int i = 1; i <= 16; i++) {
        if (fish_list[i].is_alive) {
            pos cur = fish_list[i].p;
            int cur_dir = fish_list[i].dir_idx;

            while (true) {
                pos nxt = cur + poss_dir[cur_dir];
                if (in_range(nxt)) {
                    if (board[nxt.row][nxt.col] == NO_FISH) {
                        board[nxt.row][nxt.col] = fish_list[i].number;
                        board[cur.row][cur.col] = NO_FISH;
                        fish_list[i].p = nxt, fish_list[i].dir_idx = cur_dir;
                        break;
                    }
                    else if (board[nxt.row][nxt.col] == SHARK) {
                        cur_dir = (cur_dir + 1) % 8;
                    }
                    else {
                        int swapped = board[nxt.row][nxt.col];
                        swap(board[cur.row][cur.col], board[nxt.row][nxt.col]);
                        swap(fish_list[i].p, fish_list[swapped].p);
                        fish_list[i].dir_idx = cur_dir;
                        break;
                    }
                }
                else {
                    cur_dir = (cur_dir + 1) % 8;
                }
            }
        }
    }

    int max_ret = 0;
    for (pos p = shark_pos + poss_dir[shark_dir]; in_range(p); p += poss_dir[shark_dir]) {
        if (board[p.row][p.col] != NO_FISH) {
            max_ret = max(max_ret, simulate(p, fish_list));
        }
    }

    return max_ret + eat_number;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 각각의 이동 상황을 모두 기록하기 위해서, 판을 공유하지 않고
    * simulate 함수가 실행될 때마다 상어 위치와 물고기 상황을 인자로 넘겨
    * 새로 판을 만들었다. 물고기의 이동을 구현하고, 상어가 갈 수 있는 위치마다
    * simulate를 호출하여 최댓값을 찾고, 현재 함수에서 먹은 물고기 번호와
    * 더하여 반환한다. 물고기 번호를 인덱스와 일치시키기 위하여 fish 배열은 16+1개.
    */
    array<fish, 17> init_list;

    for (int i = 0, num, idx; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> num >> idx;
            init_list[num].p = pos(i, j);
            init_list[num].number = num;
            init_list[num].dir_idx = --idx;
        }
    }

    cout << simulate(pos(0, 0), init_list);

    return 0;
}