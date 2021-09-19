#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

const vector<pint> poss_dir = {
    pint(0, 1),
    pint(0, -1),
    pint(1, 0),
    pint(-1, 0)
};

int n, m;
vector<pint> zero_point, used;
vector<vector<pint>> parent;
vector<vector<bool>> board;
vector<vector<int>> set_size;
queue<pint> que;

pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

pint find_parent(const pint& p) {
    return parent[p.first][p.second] == p ? p : parent[p.first][p.second] = find_parent(parent[p.first][p.second]);
}

/*
* union-find
* union�� �� ��, ���� ������ ũ�⵵ ������
*/
void union_elem(const pint& x, const pint& y) {
    pint f_x = find_parent(x), f_y = find_parent(y);
    if (f_x > f_y) {
        swap(f_x, f_y);
    }

    set_size[f_x.first][f_x.second] += set_size[f_y.first][f_y.second];
    set_size[f_y.first][f_y.second] = 0;
    parent[f_y.first][f_y.second] = f_x;
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first < n) && (0 <= p.second && p.second < m);
}

void bfs(const pint& start) {
    que.push(start);

    while (!que.empty()) {
        pint cur = que.front();
        que.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            /*
            * visit �迭�� ���� ����� �ʿ� ����,
            * union-find�� �����ϸ� ��.
            * �湮�� �� �ִ� ����ε� parent ���� �ٸ��ٸ�
            * ���� �湮���� ���� ���̹Ƿ� union�ϰ� �湮
            */
            if (in_range(nxt) && board[nxt.first][nxt.second] && find_parent(cur) != find_parent(nxt)) {
                union_elem(cur, nxt);
                que.push(nxt);
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    parent.resize(n, vector<pint>(m));
    board.resize(n, vector<bool>(m, false));
    set_size.resize(n, vector<int>(m, 1));
    for (int i = 0, tmp; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> tmp;

            if (tmp == 0) {
                zero_point.push_back(pint(i, j));
            }
            board[i][j] = tmp == 1;
            parent[i][j] = pint(i, j);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pint cur = pint(i, j);

            if (board[i][j] && find_parent(cur) == cur) {
                bfs(cur);
            }
        }
    }

    /*
    * 0�� �κ��� 1�� �ٲٰ�, �̾����� ���յ��� ũ�⸦ ���ϸ�
    * ����� �ִ� ũ�⸦ ���� �� ����.
    * �̹� ����� ������ ��ǩ���� �����Ͽ� �ߺ� �����Ͽ���.
    */
    int max_size = 0;
    for (const pint& cur : zero_point) {
        used.clear();
        int tmp_size = 1;

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;
            
            if (in_range(nxt) && board[nxt.first][nxt.second]) {
                pint f_nxt = find_parent(nxt);

                if (find(used.begin(), used.end(), f_nxt) == used.end()) {
                    tmp_size += set_size[f_nxt.first][f_nxt.second];
                    used.push_back(f_nxt);
                }
            }
        }

        max_size = max(max_size, tmp_size);
    }

    cout << max_size;

    return 0;
}