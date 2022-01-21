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

    if (cnt_x == cnt_o) {   // O가 이김: X가 먼저 이기면 안됨
        return !is_win('X', board) && is_win('O', board);
    }
    else if (cnt_x == cnt_o + 1) {  // X가 이김 혹은 비김
        if (cnt_empty == 0) {   // 비기는 경우: O가 먼저 이기면 안됨
            return !is_win('O', board);
        }
        else {  // X가 이기는 경우: O가 먼저 이기면 안됨
            return is_win('X', board) && !is_win('O', board);
        }
    }
    else {  // 불가능한 경우
        return false;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * X가 먼저 시작하므로, 보드에 있는 X와 O의 수는 같거나 X가 하나 더 많아야 한다.
    * 만약 둘 중 한 명이 이겼을 경우, 다른 한 쪽은 이기지 못해야 한다.
    * 만약 판이 다 찬 경우(X의 승 or 비김), O가 먼저 이긴 상황이면 안된다.
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