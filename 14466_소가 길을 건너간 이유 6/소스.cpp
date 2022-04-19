#include <iostream>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) {
        return dir(this->row + other.row, this->col + other.col);
    }
    dir operator-(const dir& other) {
        return dir(this->row - other.row, this->col - other.col);
    }
    bool operator==(const dir& other) {
        return this->row == other.row && this->col == other.col;
    }
};

const dir poss_dir[4] = {
    dir(1, 0), dir(0, -1), dir(-1, 0), dir(0, 1)
};

int n, k, r;
int ans = 0;
bool not_usable[101][101][4];
bool visit[101][101], is_cow[101][101];
dir cow_dir[100];
queue<dir> que;

bool in_range(const dir& d) {
    return 1 <= d.row && d.row <= n && 1 <= d.col && d.col <= n;
}

void bfs(const int start_idx) {
    for (int i = 1; i <= n; i++) {
        fill(visit[i] + 1, visit[i] + n + 1, false);
    }

    visit[cow_dir[start_idx].row][cow_dir[start_idx].col] = true;
    que.push(cow_dir[start_idx]);
    while (!que.empty()) {
        dir cur = que.front();
        que.pop();

        for (int i = 0; i < 4; i++) {
            if (!not_usable[cur.row][cur.col][i]) {
                dir nxt = cur + poss_dir[i];
                if (in_range(nxt) && !visit[nxt.row][nxt.col]) {
                    visit[nxt.row][nxt.col] = true;
                    que.push(nxt);
                }
            }
        }
    }
}

int main() {
    /*
    * 길을 건너야 한다는 것은 직접 연결되지 않았다는 것을 의미.
    * 따라서 길이 있는 곳은 간선의 연결을 끊는다.
    * 그리고, 각 소의 위치에서 bfs를 실행하여 방문하지 않은 소의 수를 세면 된다.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k >> r;
    for (dir d1, d2, pos; r > 0; r--) {
        cin >> d1.row >> d1.col >> d2.row >> d2.col;
        pos = d2 - d1;
        for (int i = 0; i < 4; i++) {
            if (pos == poss_dir[i]) {
                not_usable[d1.row][d1.col][i] = true;
                not_usable[d2.row][d2.col][(i + 2) % 4] = true;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        cin >> cow_dir[i].row >> cow_dir[i].col;
        is_cow[cow_dir[i].row][cow_dir[i].col] = true;
    }

    for (int i = 0; i < k - 1; i++) {
        bfs(i);
        for (int j = i + 1; j < k; j++) {
            if (!visit[cow_dir[j].row][cow_dir[j].col]) {
                ans++;
            }
        }
    }

    cout << ans;

    return 0;
}