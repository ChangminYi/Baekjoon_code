#include <iostream>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};
const int INF = 1000000;
const char START = '$';
const char WALL = '*';
const char DOOR = '#';
const char EMPTY = '.';

int t, h, w;
dir sp[3];
char board[102][102];
int dist[3][102][102];
deque<dir> deq;

void init() {
    for(int i = 0; i < 102; i++) {
        fill(board[i], board[i] + 102, EMPTY);
        for(int j = 0; j < 3; j++) fill(dist[j][i], dist[j][i] + 102, INF);
    }
    sp[0].row = 0, sp[0].col = 0, sp[1].row = INF, sp[2].row = INF;
}

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < h && 0 <= d.col && d.col < w;
}

int main() {
    /**
     * 특정 지역까지 움직일 때, 열어야 하는 문의 수를 거리로 설정한다.
     * 최단거리를 구하면 되기 때문에, 다익스트라 알고리즘도 사용이 가능하지만,
     * 빠른 실행시간을 위해서 deque를 사용한 0-1 bfs를 사용하였다.
     * 총 3명의 사람을 고려해야 하는데, 죄수 2명과 바깥에 있는 사람이다.
     * 각 사람마다 최단거리를 구한 다음, 문이 있는 칸은 거리에서 2를 뺀다.
     * 세 명 중 한 명이라도 문을 열면 계속 열린 상태로 존재하기 때문이다.
     * 그 후 모든 칸에 대하여 최단거리를 구하면 그 값이 최소로 열어야 하는 문의 수.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> t;
    do {
        init();

        cin >> h >> w;
        for(int i = 1; i <= h; i++) {
            for(int j = 1; j <= w; j++) {
                cin >> board[i][j];
                if(board[i][j] == START) {
                    (sp[1].row == INF ? sp[1] : sp[2]) = dir(i, j);
                    board[i][j] = EMPTY;
                }
            }
        }
        h += 2, w += 2;

        for(int i = 0; i < 3; i++) {
            dist[i][sp[i].row][sp[i].col] = 0;
            deq.push_back(sp[i]);
            while(!deq.empty()) {
                dir cur = deq.front();
                deq.pop_front();

                for(const dir& pd: poss_dir) {
                    dir nxt = cur + pd;
                    if(!in_range(nxt) || board[nxt.row][nxt.col] == WALL || dist[i][nxt.row][nxt.col] != INF) continue;
                    if(board[nxt.row][nxt.col] == DOOR) {
                        dist[i][nxt.row][nxt.col] = dist[i][cur.row][cur.col] + 1;
                        deq.push_back(nxt);
                    }
                    else {
                        dist[i][nxt.row][nxt.col] = dist[i][cur.row][cur.col];
                        deq.push_front(nxt);
                    }
                }
            }
        }

        int ans = INF;
        for(int i = 0, tmp_sum; i < h; i++) {
            for(int j = 0; j < w; j++) {
                if(board[i][j] == WALL) continue;
                tmp_sum = (board[i][j] == DOOR ? -2 : 0) + dist[0][i][j] + dist[1][i][j] + dist[2][i][j];
                ans = min(ans, tmp_sum);
            }
        }

        cout << ans << '\n';
    } while(--t);

    return 0;
}