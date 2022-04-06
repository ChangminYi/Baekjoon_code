#include <iostream>

using namespace std;

string board[9];
bool row_used[9][10], col_used[9][10], partition_used[3][3][10];
bool finished = false;

bool is_right_partition(const int base_row, const int base_col) {
    bool used[10];
    fill(used, used + 10, false);
    for (int i = base_row; i < base_row + 3; i++) {
        for (int j = base_col; j < base_col + 3; j++) {
            if (used[board[i][j] - '0']) return false;
            else used[board[i][j] - '0'] = true;
        }
    }
    return true;
}

bool is_right_board() {
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (!is_right_partition(i, j)) return false;
            else continue;
        }
    }
    return true;
}

void do_sudoku(const int row, const int col) {
    if (row == 9) {
        if (is_right_board()) {
            finished = true;
            for (int i = 0; i < 9; i++) {
                cout << board[i] << '\n';
            }
        }
    }
    else {
        int nxt_col = (col + 1) % 9;
        int nxt_row = (nxt_col ? row : row + 1);

        if (board[row][col] == '0') {
            for (int i = 1; i <= 9 && !finished; i++) {
                if (!(row_used[row][i] || col_used[col][i] || partition_used[row / 3][col / 3][i])) {
                    bool backup_row = row_used[row][i];
                    bool backup_col = col_used[col][i];
                    bool backup_part = partition_used[row / 3][col / 3][i];
                    row_used[row][i] = col_used[col][i] = partition_used[row / 3][col / 3][i] = true;
                    board[row][col] = '0' + i;

                    do_sudoku(nxt_row, nxt_col);

                    board[row][col] = '0';
                    row_used[row][i] = backup_row;
                    col_used[col][i] = backup_col;
                    partition_used[row / 3][col / 3][i] = backup_part;
                }
                else continue;
            }
        }
        else {
            do_sudoku(nxt_row, nxt_col);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 현재 행, 열, 3 by 3 사각형에서 이미 사용한 숫자를 미리 저장한다.
    * 그리고 값이 '0'인 모든 칸에 대하여 사용하지 않은 값들을 대입하여
    * 스도쿠의 조건을 만족할 때까지 탐색과 백트래킹을 반복한다.
    * 사용한 값은 뒷 값의 탐색을 빠르게 하기 위하여 사용했다고 표시하고,
    * 백트래킹을 할 때 값을 다시 복원한다.
    */

    for (int i = 0; i < 9; i++) {
        cin >> board[i];
    }

    for (int i = 0, val; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            val = board[i][j] - '0';
            row_used[i][val] = col_used[j][val] = partition_used[i / 3][j / 3][val] = true;
        }
    }

    do_sudoku(0, 0);

    return 0;
}