#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int r = 0, const int c = 0) : row(r), col(c) {}
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};
const int INF = INT32_MAX / 2;
const char WALL = '#';

int w, h;
dir start_p, end_p;
char board[500][500];
int dist[500][500];
deque<dir> deq;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < h && 0 <= d.col && d.col < w;
}

bool is_adj_wall(const dir& d) {
    for(const dir& pd: poss_dir) {
        dir adj = d + pd;
        if(board[adj.row][adj.col] == WALL)
            return true;
    }
    return false;
}

int main() {
    /**
     * 특정 칸에서 인접한 벽의 수가 하나 '이상'이면 벽에 인접한 칸이다.
     * 다익스트라를 사용해도 되지만, 덱을 사용하여 구현하는 것이 더 빠르다.
     * 벽을 타고 이동할 경우에는 덱의 앞에 push, 아니면 뒤에 push하여 우선순위를 부여.
     * 이를 통해 최단거리를 구하여 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> h >> w;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            cin >> board[i][j];
            if(board[i][j] == 'S')
                start_p = dir(i, j);
            else if(board[i][j] == 'E')
                end_p = dir(i, j);
            dist[i][j] = INF;
        }
    }

    dist[start_p.row][start_p.col] = 0;
    deq.push_front(start_p);
    while(!deq.empty()) {
        dir cur = deq.front();
        deq.pop_front();

        for(const dir& pd: poss_dir) {
            dir nxt = cur + pd;
            if(in_range(nxt) && board[nxt.row][nxt.col] != WALL) {
                if(is_adj_wall(cur) && is_adj_wall(nxt)) {
                    if(dist[cur.row][cur.col] < dist[nxt.row][nxt.col]) {
                        dist[nxt.row][nxt.col] = dist[cur.row][cur.col];
                        deq.push_front(nxt);
                    }
                }
                else {
                    int new_dist = dist[cur.row][cur.col] + 1;
                    if(new_dist < dist[nxt.row][nxt.col]) {
                        dist[nxt.row][nxt.col] = new_dist;
                        deq.push_back(nxt);
                    }
                }
            }
        }
    }
    
    cout << dist[end_p.row][end_p.col];

    return 0;
}