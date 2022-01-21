#include <iostream>
#include <string>

using namespace std;

bool is_win(const char player, const string& board) {
    if ((board[0] == board[1] && board[1] == board[2] && board[0] == player)
        || (board[3] == board[4] && board[4] == board[5] && board[3] == player)
        || (board[6] == board[7] && board[7] == board[8] && board[6] == player)
        || (board[0] == board[3] && board[3] == board[6] && board[0] == player)
        || (board[1] == board[4] && board[4] == board[7] && board[1] == player)
        || (board[2] == board[5] && board[5] == board[8] && board[2] == player)
        || (board[0] == board[4] && board[4] == board[8] && board[0] == player)
        || (board[2] == board[4] && board[4] == board[6] && board[2] == player)
        ) {
        return true;
    }
    else {
        return false;
    }
}

bool test_valid(const string& board) {
    int cnt_empty = 0, cnt_x = 0, cnt_o = 0;
    for (int i = 0; i < 9; i++) {
        board[i] == '.' ? cnt_empty++ : (board[i] == 'O' ? cnt_o++ : cnt_x++);
    }

    if (cnt_x == cnt_o) {   // O�� �̱�: X�� ���� �̱�� �ȵ�
        return !is_win('X', board) && is_win('O', board);
    }
    else if (cnt_x == cnt_o + 1) {  // X�� �̱� Ȥ�� ���
        if (cnt_empty == 0) {   // ���� ���: O�� ���� �̱�� �ȵ�
            return !is_win('O', board);
        }
        else {  // X�� �̱�� ���: O�� ���� �̱�� �ȵ�
            return is_win('X', board) && !is_win('O', board);
        }
    }
    else {  // �Ұ����� ���
        return false;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * X�� ���� �����ϹǷ�, ���忡 �ִ� X�� O�� ���� ���ų� X�� �ϳ� �� ���ƾ� �Ѵ�.
    * ���� �� �� �� ���� �̰��� ���, �ٸ� �� ���� �̱��� ���ؾ� �Ѵ�.
    * ���� ���� �� �� ���(X�� �� or ���), O�� ���� �̱� ��Ȳ�̸� �ȵȴ�.
    */
    string board;

    while (true) {
        cin >> board;
        if (board.length() == 3) {
            break;
        }
        else {
            cout << (test_valid(board) ? "valid\n" : "invalid\n");
        }
    }

    return 0;
}