#include <iostream>
#include <vector>

using namespace std;

struct pos {
    int row, col;
    pos(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    pos operator+(const pos& other) const {
        return pos(this->row + other.row, this->col + other.col);
    }
};

struct robot {
    pos cur_pos;
    int dir;
};

const pos avail_dir[4] = {
    pos(1, 0), pos(0, 1), pos(-1, 0), pos(0, -1)
};

const int WALL = -1;
const int EMPTY = 0;

int a, b, n, m;
int board[102][102];
vector<robot> robot_list;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 문제에서 요구하는 사항을 그대로 구현하면 된다.
    * 다만, 행과 열이 순서가 바뀌어 들어오므로 입력에 주의.
    */
    cin >> a >> b >> n >> m;
    for (int i = 0; i <= b + 1; i++) {
        for (int j = 0; j <= a + 1; j++) {
            if (i == 0 || i == b + 1 || j == 0 || j == a + 1) board[i][j] = WALL;
            else board[i][j] = EMPTY;
        }
    }
    robot_list.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        char cur_dir;
        cin >> robot_list[i].cur_pos.col >> robot_list[i].cur_pos.row >> cur_dir;
        board[robot_list[i].cur_pos.row][robot_list[i].cur_pos.col] = i;
        
        if (cur_dir == 'N') robot_list[i].dir = 0;
        else if (cur_dir == 'E') robot_list[i].dir = 1;
        else if (cur_dir == 'S') robot_list[i].dir = 2;
        else robot_list[i].dir = 3;
    }

    bool no_error = true, is_wall = false;
    int r_num, crashed, iter;
    char inst;
    do {
        cin >> r_num >> inst >> iter;

        if (inst == 'F') {
            for (int i = 0; i < iter; i++) {
                pos cur = robot_list[r_num].cur_pos;
                pos tmp_nxt = cur + avail_dir[robot_list[r_num].dir];
                
                if (board[tmp_nxt.row][tmp_nxt.col] == EMPTY) {
                    board[cur.row][cur.col] = EMPTY, board[tmp_nxt.row][tmp_nxt.col] = r_num;
                    robot_list[r_num].cur_pos = tmp_nxt;
                }
                else {
                    if (board[tmp_nxt.row][tmp_nxt.col] == WALL) no_error = false, is_wall = true;
                    else no_error = false, is_wall = false, crashed = board[tmp_nxt.row][tmp_nxt.col];
                    break;
                }
            }
        }
        else {
            for (int i = 0; i < iter; i++) {
                robot_list[r_num].dir += (inst == 'L' ? 3 : 1);
                robot_list[r_num].dir %= 4;
            }
        }
    } while (--m && no_error);

    if (no_error) cout << "OK";
    else if (is_wall) cout << "Robot " << r_num << " crashes into the wall";
    else cout << "Robot " << r_num << " crashes into robot " << crashed;

    return 0;
}