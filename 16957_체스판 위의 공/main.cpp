#include <iostream>
#include <vector>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    bool operator==(const dir& other) {
        return row == other.row && col == other.col;
    }
};

const vector<dir> poss_dir{
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1),
    dir(1, 1), dir(1, -1), dir(-1, 1), dir(-1, -1)};

int r, c;
int board[500][500], cnt[500][500];
dir parent[500][500];

dir operator+(const dir &lhs, const dir &rhs) {
    return dir(lhs.row + rhs.row, lhs.col + rhs.col);
}

bool in_range(const dir &d) {
    return 0 <= d.row && d.row < r && 0 <= d.col && d.col < c;
}

dir find_parent(const dir& x) {
    if(parent[x.row][x.col] == x) return x;
    else return parent[x.row][x.col] = find_parent(parent[x.row][x.col]);
}

int main() {
    /**
     * union-find를 사용해 해당 칸의 공이 어디로 가야 할 지 빠르게 정할 수 있음. 
     * 그 후 board에 대해 cnt를 업데이트하고 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> board[i][j];
            parent[i][j].row = i, parent[i][j].col = j;
        }
    }

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            int min_val = board[i][j];
            dir cur(i, j), par(i, j);
            for(const dir& pd: poss_dir) {
                dir nxt = cur + pd;
                if(in_range(nxt) && board[nxt.row][nxt.col] < min_val) {
                    par = nxt;
                    min_val = board[nxt.row][nxt.col];
                }
            }

            parent[i][j] = find_parent(par);
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            dir par = find_parent(dir(i, j));
            cnt[par.row][par.col]++;
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << cnt[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}