#include <iostream>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) {
        row = _r, col = _c;
    }
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

const dir poss_dir[] = {
    dir(0, 1), dir(0, -1), dir(-1, 0), dir(1, 0)
};

int n, m, k, inst;
dir dice_dir;
int dice[2][4]; // {top, north, bottom, south}, {top, east, bottom, west}
int board[20][20];

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
}

int move_dice(const int move_idx) {
    int tmp;
    
    switch(move_idx) {
    case 0: // east
        tmp = dice[1][3];
        for(int i = 3; i >= 1; i--)
            dice[1][i] = dice[1][i - 1];
        dice[1][0] = tmp, dice[0][0] = dice[1][0], dice[0][2] = dice[1][2];
        break;
    case 1: // west
        tmp = dice[1][0];
        for(int i = 0; i <= 2; i++)
            dice[1][i] = dice[1][i + 1];
        dice[1][3] = tmp, dice[0][0] = dice[1][0], dice[0][2] = dice[1][2];
        break;
    case 2: // north
        tmp = dice[0][3];
        for(int i = 3; i >= 1; i--)
            dice[0][i] = dice[0][i - 1];
        dice[0][0] = tmp, dice[1][0] = dice[0][0], dice[1][2] = dice[0][2];
        break;
    case 3: // south
        tmp = dice[0][0];
        for(int i = 0; i <= 2; i++)
            dice[0][i] = dice[0][i + 1];
        dice[0][3] = tmp, dice[1][0] = dice[0][0], dice[1][2] = dice[0][2];
        break;
    }

    dir nxt = dice_dir + poss_dir[move_idx];
    if(board[nxt.row][nxt.col] == 0) 
        board[nxt.row][nxt.col] = dice[0][2];
    else {
        dice[0][2] = dice[1][2] = board[nxt.row][nxt.col];
        board[nxt.row][nxt.col] = 0;
    }
    dice_dir = nxt;
    
    return dice[0][0];
}

int main() {
    /**
     * 주사위의 숫자 상태는 윗면과 아랫면이 중복되는 2 * 4 배열로 저장했다.
     * 중복값이 생기지만, 반복문을 통한 구현의 편의성을 우선하였다.
     * 이동 전, 먼저 이동 후 위치가 범위 내인지를 판단하고, 맞는 경우에만 이동을 진행한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> dice_dir.row >> dice_dir.col >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    do {
        cin >> inst;
        if(in_range(dice_dir + poss_dir[--inst]))
            cout << move_dice(inst) << '\n';
    } while(--k);

    return 0;
}