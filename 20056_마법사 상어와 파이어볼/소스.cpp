#include <iostream>
#include <queue>

using namespace std;

struct dir {
    int x = 0, y = 0;
    dir() {}
    dir(int _x, int _y) : x(_x), y(_y) {}
};

struct fireball {
    int x = 0, y = 0, dir_idx = 0, mass = 0, speed = 0;
    fireball() {}
    fireball(int _x, int _y, int _di, int _m, int _s) {
        x = _x, y = _y, dir_idx = _di, mass = _m, speed = _s;
    }
};

const dir poss_dir[] = {
    dir(-1, 0), dir(-1, 1), dir(0, 1), dir(1, 1),
    dir(1, 0), dir(1, -1), dir(0, -1), dir(-1, -1)
};

int n, m, k;
queue<fireball> que;
int sum_mass[50][50], sum_speed[50][50];
vector<int> idx_set[50][50];

void init_var() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum_mass[i][j] = 0;
            sum_speed[i][j] = 0;
            idx_set[i][j].clear();
        }
    }
}

void update_fireball() {
    init_var();

    while (!que.empty()) {
        int x = que.front().x, y = que.front().y;
        int mass = que.front().mass, speed = que.front().speed;
        int dir_idx = que.front().dir_idx;
        que.pop();

        int new_x = x + speed * poss_dir[dir_idx].x;
        int new_y = y + speed * poss_dir[dir_idx].y + n;
        while (new_x < 0) {
            new_x += n;
        }
        while (new_y < 0) {
            new_y += n;
        }
        new_x %= n, new_y %= n;
        
        idx_set[new_x][new_y].push_back(dir_idx);
        sum_mass[new_x][new_y] += mass;
        sum_speed[new_x][new_y] += speed;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (idx_set[i][j].size() == 1) {
                que.push(fireball(i, j, idx_set[i][j][0], sum_mass[i][j], sum_speed[i][j]));
            }
            else if (idx_set[i][j].size() > 1) {
                int cnt = count_if(idx_set[i][j].begin(), idx_set[i][j].end(),
                    [](int i) {
                        return (i % 2) == 1;
                    });
                int new_mass = sum_mass[i][j] / 5;
                int new_speed = sum_speed[i][j] / idx_set[i][j].size();
                
                if (new_mass > 0) {
                    for (int idx = (cnt == 0 || cnt == idx_set[i][j].size()) ? 0 : 1; idx < 8; idx += 2) {
                        que.push(fireball(i, j, idx, new_mass, new_speed));
                    }
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 구현. 문제에서 요구하는 사항을 그대로 코딩하면 된다.
    * 다만, 판을 벗어나게 되면 반대편으로 돌아오게 되므로,
    * 좌표 계산만 잘 하면 된다.
    */
    cin >> n >> m >> k;
    for (int i = 0, x, y, di, mass, s; i < m; i++) {
        cin >> x >> y >> mass >> s >> di;
        que.push(fireball(--x, --y, di, mass, s));
    }

    for (int i = 0; i < k; i++) {
        update_fireball();
    }

    int sum = 0;
    while (!que.empty()) {
        sum += que.front().mass;
        que.pop();
    }

    cout << sum;

    return 0;
}