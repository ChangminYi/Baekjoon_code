#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef pair<int, int> pint;

const pint poss_dir[4] = {
    pint(0, -1), pint(-1, 0), pint(0, 1), pint(1, 0)
};

int row, col;
vector<pint> graph[52][52];
pint parent[52][52];
int set_size[52][52], edge[52][52];
vector<pair<pint, pint>> wall;

pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

pint find_par(const pint x) {
    return parent[x.first][x.second] == x ? x : parent[x.first][x.second] = find_par(parent[x.first][x.second]);
}

void union_elem(const pint x, const pint y) {
    pint p_x = find_par(x), p_y = find_par(y);
    if (p_x > p_y) {
        swap(p_x, p_y);
    }
    set_size[p_x.first][p_x.second] += set_size[p_y.first][p_y.second];
    set_size[p_y.first][p_y.second] = 0;
    parent[p_y.first][p_y.second] = p_x;
}

bool in_range(const pint p) {
    return (1 <= p.first && p.first <= row) && (1 <= p.second && p.second <= col);
}

void init_edge() {
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            pint cur = pint(i, j);
            for (int k = 0; k < 4; k++) {
                pint adj = cur + poss_dir[k];
                if ((edge[i][j] & (1 << k)) == 0) {
                    graph[i][j].push_back(adj);
                }
                else {
                    if (in_range(adj)) {
                        wall.push_back(make_pair(cur, adj));
                    }
                }
            }
        }
    }
}

void bfs() {
    queue<pint> que;

    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (parent[i][j].first == i && parent[i][j].second == j) {
                que.push(pint(i, j));

                while (!que.empty()) {
                    pint cur = que.front();
                    que.pop();

                    for (const pint& nxt : graph[cur.first][cur.second]) {
                        if (find_par(cur) != find_par(nxt)) {
                            que.push(nxt);
                            union_elem(cur, nxt);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * bfs와 union-find를 통해 parent의 수와 각 집합의 크기를 구한다.
    * 벽의 정보도 따로 저장하여, 방 분류가 끝난 후에
    * 벽을 공유하고 parent가 다른 두 방의 집합 크기 합의 최댓값을 구한다.
    */
    cin >> col >> row;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            parent[i][j].first = i, parent[i][j].second = j;
            set_size[i][j] = 1;
            cin >> edge[i][j];
        }
    }

    init_edge();
    bfs();

    int set_cnt = 0;
    int max_size = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (parent[i][j].first == i && parent[i][j].second == j) {
                set_cnt++;
                max_size = max(max_size, set_size[i][j]);
            }
        }
    }

    int max_sum = 0;
    for (const pair<pint, pint>& edge : wall) {
        pint p_x = find_par(edge.first), p_y = find_par(edge.second);
        if (p_x != p_y) {
            max_sum = max(max_sum, set_size[p_x.first][p_x.second] + set_size[p_y.first][p_y.second]);
        }
    }

    cout << set_cnt << '\n' << max_size << '\n' << max_sum;

    return 0;
}