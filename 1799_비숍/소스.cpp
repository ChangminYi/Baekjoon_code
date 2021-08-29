#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 10;
int n;
int ans[2];
int board[MAX][MAX];
int board_color[MAX][MAX];
bool selected[MAX][MAX];

int dir[2][4] = {
    { -1, -1, 1, 1 },
    { -1, 1, -1, 1 }
};

bool in_range(int x, int y) {
    if (0 <= x && x < n) {
        if (0 <= y && y < n) {
            return true;
        }
    }
    return false;
}

bool can_pos(int x, int y) {
    for (int i = 0; i < 2; i++) {
        int nx = x, ny = y;

        while (in_range(nx, ny)) {
            if (selected[nx][ny] == true) {
                return false;
            }
            nx += dir[0][i];
            ny += dir[1][i];
        }
    }
    return true;
}

void dfs(int idx, int cnt, int color) {
    ans[color] = max(ans[color], cnt);

    for (int i = idx + 1; i < n * n; i++) {
        int x = i / n, y = i % n;

        if (board_color[x][y] == color && board[x][y] && can_pos(x, y)) {
            selected[x][y] = true;
            dfs(i, cnt + 1, color);
            selected[x][y] = false;
        }
    }
}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];

            if ((i + j) % 2 == 0) {
                board_color[i][j] = 1;
            }
        }
    }

    dfs(-1, 0, 0);
    dfs(-1, 0, 1);
    cout << ans[0] + ans[1];

    return 0;
}