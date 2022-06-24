#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

const vector<pint> poss_dir = {
    pint(1, 0), pint(-1, 0), pint(0, 1), pint(0, -1),
    pint(1, 1), pint(1, -1), pint(-1, 1), pint(-1, -1)
};

int n, m, k;
int board[10][10], arg[10][10], new_tree_cnt[10][10];
deque<int> t_list[10][10];
vector<pint> adj[10][10];

pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return 0 <= p.first && p.first < n && 0 <= p.second && p.second < n;
}

void do_spring_and_summer() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int iter = t_list[i][j].size(), accu = 0;
            for(int k = 0; k < iter; k++) {
                int tree = t_list[i][j].front();
                t_list[i][j].pop_front();

                if(board[i][j] < tree) {
                    accu += tree / 2;
                }
                else {
                    board[i][j] -= tree;
                    t_list[i][j].push_back(tree + 1);
                }
            }

            board[i][j] += accu;
        }
    }
}

void do_fall_and_winter() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(const int& tree : t_list[i][j]) {
                if(tree % 5 == 0) {
                    for(const pint& nxt : adj[i][j]) {
                        new_tree_cnt[nxt.first][nxt.second]++;
                    }
                }
            }
            board[i][j] += arg[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(; new_tree_cnt[i][j]; new_tree_cnt[i][j]--) {
                t_list[i][j].push_front(1);
            }
        }
    }
}

int main() {
    /**
     * 시간 제한이 0.3초로 매우 짧으므로, map이나 priority_queue 등의
     * 오버헤드가 큰 자료 구조들은 사용을 지양해야 한다. deque를 사용하여
     * 새로 생기는 나무들은 앞에 추가하는 식으로 오름차순을 유지하고,
     * 죽는 나무들은 바로 양분 추가량에 저장했다가 봄이 끝나면
     * 바로 땅에 양분을 저장하는 방식으로 구현하였다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> arg[i][j];
            board[i][j] = 5;

            pint cur = pint(i, j);
            for(const pint& pd: poss_dir) {
                pint nxt = cur + pd;
                if(in_range(nxt)) adj[i][j].push_back(nxt);
            }
        }
    }
    for(int i = 0, x, y, z; i < m; i++) {
        cin >> x >> y >> z;
        x--, y--;
        t_list[x][y].push_back(z);
    }

    do {
        do_spring_and_summer();
        do_fall_and_winter();
    } while(--k);

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ans += t_list[i][j].size();
        }
    }

    cout << ans;

    return 0;
}