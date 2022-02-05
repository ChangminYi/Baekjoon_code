#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct dir {
    int row, col;
    dir(const int r = 0, const int c = 0) : row(r), col(c) {}
    dir operator+(const dir& other) { return dir(row + other.row, col + other.col); }
};

struct pqn {
    dir direction;
    int dist;
    pqn(const dir dir, const int d) : direction(dir), dist(d) {}
    bool operator>(const pqn& other) { return dist > other.dist; }
};

const vector<dir> poss_dir{
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};
const int INF = INT32_MAX / 2;
const char WALL = '#';
const int FIRE = 'F';

int r, c;
dir start;
char board[1000][1000];
int dist[1000][1000], fire_reach[1000][1000];
priority_queue<pqn, vector<pqn>, greater<>> pq;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < r && 0 <= d.col && d.col < c;
}

bool can_exit(const dir& d) {
    return d.row == 0 || d.row == r - 1 || d.col == 0 || d.col == c - 1;
}

void init_fire_range() {
    while (!pq.empty()) {
        dir cur = pq.top().direction;
        int cur_dist = pq.top().dist;
        pq.pop();

        for (const dir& d : poss_dir) {
            dir nxt = cur + d;
            int new_dist = cur_dist + 1;
            if (in_range(nxt) && board[nxt.row][nxt.col] != WALL) {
                if (new_dist < fire_reach[nxt.row][nxt.col]) {
                    fire_reach[nxt.row][nxt.col] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }
}

string bfs() {
    dist[start.row][start.col] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        dir cur = pq.top().direction;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (can_exit(cur)) {
            return to_string(cur_dist + 1);
        }
        else {
            for (const dir& d : poss_dir) {
                dir nxt = cur + d;
                int new_dist = cur_dist + 1;
                if (in_range(nxt) && board[nxt.row][nxt.col] != WALL) {
                    if (new_dist < dist[nxt.row][nxt.col] && new_dist < fire_reach[nxt.row][nxt.col]) {
                        dist[nxt.row][nxt.col] = new_dist;
                        pq.push(pqn(nxt, new_dist));
                    }
                }
            }
        }
    }

    return "IMPOSSIBLE";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    /*
    * 불이 먼저 도달하는 시간을 계산한 후, 사람이 움직인다.
    * 가능한 움직임 중에서 최단거리를 찾아간다.
    * 첫 번째로 탈출 가능한 경우의 거리가 정답이 된다.
    */
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> board[i][j];
            dist[i][j] = INF;
            if (board[i][j] == FIRE) {
                pq.push(pqn(dir(i, j), 0));
                fire_reach[i][j] = 0;
            }
            else {
                fire_reach[i][j] = INF;
            }

            if (board[i][j] == 'J') {
                start = dir(i, j);
            }
        }
    }

    init_fire_range();
    cout << bfs();

    return 0;
}