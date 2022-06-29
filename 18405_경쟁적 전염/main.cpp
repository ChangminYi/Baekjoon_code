#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r, const int _c) : row(_r), col(_c) {}
    dir operator+(const dir& other) {
        return dir(row + other.row, col + other.col);
    }
};

const vector<dir> poss_dir = {
    dir(0, 1), dir(1, 0), dir(0, -1), dir(-1, 0)
};
const int NOT_VISIT = 0;

int n, k, s, x, y;
int board[201][201];
queue<dir> que[1001];

bool in_range(const dir& d) {
    return 1 <= d.row && d.row <= n && 1 <= d.col && d.col <= n;
}

int main() {
    /**
     * 작은 번호의 바이러스부터 번식을 시작한다.
     * 무한정 번식하는 것을 막기 위해 큐에 레벨링을 사용.
     * 이를 s번 반복한 후의 결과를 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> board[i][j];
            if(board[i][j])
                que[board[i][j]].push(dir(i, j));
        }
    }
    cin >> s >> x >> y;

    while(s--) {
        for(int j = 1, iter; j <= k; j++) {
            iter = que[j].size();
            while(iter--) {
                dir cur = que[j].front();
                que[j].pop();

                for(const dir& pd: poss_dir) {
                    dir nxt = cur + pd;
                    if(in_range(nxt) && board[nxt.row][nxt.col] == NOT_VISIT) {
                        board[nxt.row][nxt.col] = j;
                        que[j].push(nxt);
                    }
                }
            }
        }
    }

    cout << board[x][y];

    return 0;
}