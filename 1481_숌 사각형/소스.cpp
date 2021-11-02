#include <iostream>

using namespace std;

int n, d, base;
int board[10][10] = { 0 };

int get_row_bitset(int row, int col) {
    int ret = 0;
    for (int i = 0; i <= col; i++) {
        ret |= (1 << board[row][i]);
    }
    return ret;
}

int get_col_bitset(int row, int col) {
    int ret = 0;
    for (int i = 0; i <= row; i++) {
        ret |= (1 << board[i][col]);
    }
    return ret;
}

int get_cur_bitset(int row, int col) {
    return (get_row_bitset(row, col - 1) | get_col_bitset(row - 1, col));
}

bool has_bit(int bitset, int num) {
    return (bitset & (1 << num)) != 0;
}

bool simul(int row, int col) {
    if (row == n) {
        return true;
    }
    else {
        int cur_bitset = get_cur_bitset(row, col);
        int nxt_row = (col == n - 1 ? row + 1 : row);
        int nxt_col = (col == n - 1 ? base : col + 1);

        for (int i = 0; i < d; i++) {
            if (!has_bit(cur_bitset, i)) {
                board[row][col] = i;

                if (simul(nxt_row, nxt_col)) {
                    return true;
                }
            }
        }

        return false;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> d;

    /*
    * �ʱ�ȭ. 0���� �����Ͽ� ������������ �����Ǵ� ���� �ٱ��κ� ����.
    */
    base = n - d + 1;
    for (int i = 0; i < base; i++) {
        for (int j = base; j < n; j++) {
            board[j][i] = board[i][j] = j - base + 1;
        }
    }

    /*
    * ��Ʈ����ŷ���� ���� ���� üũ�ذ��� ��Ʈ��ŷ.
    * 0���� ���� ���Ƿ�, ó�� ������ �����ϴ� board�� ����.
    */
    int base_bitset = get_cur_bitset(base, base);
    int nxt_row = (base == n - 1 ? base + 1 : base);
    int nxt_col = (base == n - 1 ? base : base + 1);
    for (int i = 0; i < d; i++) {
        if (!has_bit(base_bitset, i)) {
            board[base][base] = i;

            if (simul(nxt_row, nxt_col)) {
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}