#include <iostream>

using namespace std;

struct pos {
    int row, col;
    pos(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    pos operator+(const pos& other) const { return pos(this->row + other.row, this->col + other.col); }
    void operator+=(const pos& other) { this->row += other.row, this->col += other.col; }
    void operator*=(const int i) { this->row *= i, this->col *= i; }
};

struct shark {
    pos dir;
    int speed, size;
    bool alive = false;
    shark(pos _d = pos(), int _spd = 0, int _sz = 0) : dir(_d), speed(_spd), size(_sz) {}
};

int r, c, m;
shark board[100][100], tmp_board[100][100];

bool in_range(const pos& p) {
    return 0 <= p.row && p.row < r && 0 <= p.col && p.col < c;
}

int get_shark(int col) {
    for (int i = 0; i < r; i++) {
        if (board[i][col].alive) {
            return board[i][col].size;
        }
    }
    return 0;
}

void move_shark(int erase_size) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            tmp_board[i][j].alive = false;
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (board[i][j].alive && board[i][j].size != erase_size) {
                pos nxt = pos(i, j);
                int to_move = board[i][j].speed % (board[i][j].dir.row == 0 ? 2 * c - 2 : 2 * r - 2);
                while(to_move--) {
                    if (!in_range(nxt + board[i][j].dir)) {
                        board[i][j].dir *= -1;
                    }
                    nxt += board[i][j].dir;
                }

                if (!tmp_board[nxt.row][nxt.col].alive || tmp_board[nxt.row][nxt.col].size < board[i][j].size) {
                    tmp_board[nxt.row][nxt.col] = board[i][j];
                }
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            board[i][j] = tmp_board[i][j];
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 상어의 움직임과 낚시꾼의 상어 잡는 행위를 구현하면 된다.
    * 다만, 상어의 속도가 판에 비해서 많이 클 수 있으므로, 칸에서
    * 실제로 얼마나 움직이는지를 미리 계산해야 한다. 속도 % (움직이는 축의 길이 * 2 - 2)가
    * 실제로 움직이게 되는 거리이다.
    */
    cin >> r >> c >> m;
    for (int i = 0, row, col, _s, _d, _z; i < m; i++) {
        cin >> row >> col >> _s >> _d >> _z;
        board[--row][--col].alive = true;
        if (_d == 1) board[row][col].dir = pos(-1, 0);
        else if (_d == 2) board[row][col].dir = pos(1, 0);
        else if (_d == 3) board[row][col].dir = pos(0, 1);
        else board[row][col].dir = pos(0, -1);
        board[row][col].size = _z, board[row][col].speed = _s;
    }

    int sum = 0;
    for (int i = 0, caught; i < c; i++) {
        caught = get_shark(i);
        sum += caught;
        move_shark(caught);
    }

    cout << sum;

    return 0;
}